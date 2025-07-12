#include "COM.h"

COM::COM(I_Receiver *server, const char *clientSendName,
         I_Receiver *dispatcherRec, I_Sender *dispatcherSen)
    : _server(server), _clientSendName(clientSendName), _client(nullptr),
      _dispatcherRec(dispatcherRec), _dispatcherSen(dispatcherSen),
      lastHeartbeat(std::chrono::steady_clock::now()), running(false),
      udpWatchdogRunning(false), udpWatchdogLost(false) {}

COM::~COM() { stop(); }

void COM::start() {
  if (running)
    return;

  running = true;

  auto set_priority = [](int priority) {
    struct sched_param param;
    param.sched_priority = priority;
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
  };

  dispatcherThread = std::thread([this, set_priority] {
    set_priority(10);
    runDispatcher();
  });

  clientThread = std::thread([this, set_priority] {
    set_priority(10);
    runClient();
  });

  serverThread = std::thread([this, set_priority] {
    set_priority(5);
    runServer();
  });

  // UDP-Watchdog starten
  udpWatchdogRunning = true;
  udpWatchdogThread = std::thread([this] { runUdpWatchdog(); });
}

void COM::stop() {
  if (!running)
    return;

  running = false;
  queueCV.notify_all();

  if (clientThread.joinable())
    clientThread.join();
  if (serverThread.joinable())
    serverThread.join();
  if (dispatcherThread.joinable())
    dispatcherThread.join();

  // UDP-Watchdog stoppen
  udpWatchdogRunning = false;
  if (udpWatchdogThread.joinable())
    udpWatchdogThread.join();

  // Clean up Client COID (falls noch offen)
  std::lock_guard<std::mutex> lock(_clientMutex);
  if (_client) {
    name_close(_client->getcoid());
  }
}

void COM::runDispatcher() {
  while (running) {
    _pulse dispatcherMsg;
    if (_dispatcherRec->receive_event(&dispatcherMsg) == 0) {
      Topic originalTopic = static_cast<Topic>(dispatcherMsg.code);
      int originalValue = dispatcherMsg.value.sival_int;

      {
        std::lock_guard<std::mutex> lock(queueMutex);
        switch (originalTopic) {
        case Topic::INTERRUPT:
          handleInterruptTopic(originalValue, dispatcherMsg);
          break;
        case Topic::INTERNAL:
          handleInternalTopic(originalValue, dispatcherMsg);
          break;
        case Topic::COM:
          handleComTopic(originalValue, dispatcherMsg);
          break;
        case Topic::REM_CON:
          handleRemConTopic(originalValue, dispatcherMsg);
          break;
        case Topic::ID:
          lowPriorityQueue.push_back(dispatcherMsg);
          break;
        case Topic::ERROR:
          if (originalValue == (int)Error_Enum::ERROR_C_LOST_MQTT) {
            mqttConnected = false;
            dispatcherMsg.code = static_cast<int>(Topic::COM);
            dispatcherMsg.value.sival_int =
                static_cast<int>(COM_Enum::COM_MQTT_DISCONNECTED);
            highPriorityQueue.push_front(dispatcherMsg);
          }
          break;
        default:
          break;
        }
      }
      queueCV.notify_one();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

void COM::runClient() {
  const int RETRY_DELAY_MS = 1000;
  while (running) {
    while (disconnected || _client->getcoid() <= 1) {
      std::lock_guard<std::mutex> lock(_clientMutex);
      try {
        _client = make_unique<Thread_COM::Sender>(_clientSendName);
        if (_client->getcoid() >= 0) {
          COUT("Connection established successfully");
          break;
        }
      } catch (...) {
        std::cerr << "Error creating Sender in run client com.cpp" << std::endl;
      }
      continue;
    }
    if (_client->getcoid() != -1) {
      checkQueues();
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }
}

void COM::checkQueues() {
  const size_t MAX_BATCH = 10;

  while (running) {
    std::deque<_pulse> highPrioBatch;
    std::deque<_pulse> lowPrioBatch;

    { // Locked scope
      std::unique_lock<std::mutex> lock(queueMutex);

      auto move_batch = [](std::deque<_pulse> &src, std::deque<_pulse> &dest,
                           size_t max) {
        auto end = src.size() > max ? src.begin() + max : src.end();
        dest.insert(dest.end(), std::make_move_iterator(src.begin()),
                    std::make_move_iterator(end));
        src.erase(src.begin(), end);
      };

      if (!highPriorityQueue.empty()) {
        move_batch(highPriorityQueue, highPrioBatch, MAX_BATCH);
      } else if (!lowPriorityQueue.empty()) {
        move_batch(lowPriorityQueue, lowPrioBatch, MAX_BATCH);
      } else {
        break;
      }
    }

    // High Priority zuerst
    for (auto &msg : highPrioBatch) {
      if (sendToServer(msg, (int)EventPriority::FIRST_PRIO) == -1) {
        std::lock_guard<std::mutex> lock(queueMutex);
        highPriorityQueue.push_front(std::move(msg));
      }
    }

    // Dann Low Priority
    for (auto &msg : lowPrioBatch) {
      if (sendToServer(msg) == -1) {
        std::lock_guard<std::mutex> lock(queueMutex);
        lowPriorityQueue.push_front(std::move(msg));
      }
    }

    std::this_thread::yield();
  }

  // Heartbeat nur wenn Idle
  if (highPriorityQueue.empty() && lowPriorityQueue.empty()) {
    sendHeartbeat();
  }
}

void COM::sendHeartbeat() {
  auto now = std::chrono::steady_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
      now - lastHeartbeat);

  if (elapsed.count() >= HEARTBEAT_INTERVAL) {
    std::lock_guard<std::mutex> lock(_clientMutex);
    if (_client->getcoid() != -1) {
      _client->send_event((int8_t)Topic::COM, (int)COM_Enum::HEARTBEAT);
    }
    updateHeartbeat();
  }
}

int COM::sendToServer(const _pulse &msg, int priority) {
  int send_event_status = 0;
  std::lock_guard<std::mutex> lock(_clientMutex);
  if (_client->getcoid() >= 0) {
    send_event_status = _client->send_event_com(
        (int8_t)msg.code, (int)msg.value.sival_int, (int)priority);
  }
  updateHeartbeat();
  return send_event_status;
}

void COM::runServer() {
  std::cout << "COM server started." << std::endl;
  disconnected = true;
  while (running) {
    struct _pulse event;
    int rcvid = MsgReceive(_server->getchid(), &event, sizeof(event), NULL);

    if (rcvid == 0) {
      /* if (disconnected)
      {
          disconnected = false;
          _pulse reconnectEvent;
          reconnectEvent.code = static_cast<int8_t>(Topic::COM);
          reconnectEvent.value.sival_int =
      static_cast<int>(COM_Enum::COM_CONNECTED);
          sendToDispatcher(reconnectEvent,
      static_cast<int>(EventPriority::FIRST_PRIO));
      } */
      if ((_PULSE_CODE_MINAVAIL <= event.code) &&
          (event.code <= _PULSE_CODE_MAXAVAIL)) {
        updateHeartbeat();
        processMessage(event);
      } else {
        if (event.code == _PULSE_CODE_DISCONNECT ||
            event.code == _PULSE_CODE_COIDDEATH) {
          ConnectDetach(event.scoid);
          std::cout << "Server: Disconnect oder COIDDEATH erkannt und detach "
                       "ausgeführt."
                    << std::endl;
        }
        continue;
      }
      } else {
        std::cerr << "MsgReceive error: " << strerror(errno) << std::endl;
      }
    }
  }


void COM::updateHeartbeat() {
  lastHeartbeat = std::chrono::steady_clock::now();
}

// ================ UDP-Watchdog ================
void COM::runUdpWatchdog() {
  std::cerr << "[UDP-Watchdog] Sende und empfange..." << std::endl;

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    std::cerr << "UDP-Watchdog: socket error" << std::endl;
    return;
  }

  sockaddr_in localAddr = {};
  localAddr.sin_family = AF_INET;
  localAddr.sin_port = htons(UDP_WATCHDOG_PORT);
  localAddr.sin_addr.s_addr = inet_addr(LOCAL_UDP_IP);

  if (bind(sockfd, (sockaddr *)&localAddr, sizeof(localAddr)) < 0) {
    std::cerr << "UDP-Watchdog: bind error" << std::endl;
    close(sockfd);
    return;
  }

  sockaddr_in peerAddr = {};
  peerAddr.sin_family = AF_INET;
  peerAddr.sin_port = htons(UDP_WATCHDOG_PORT);
  peerAddr.sin_addr.s_addr = inet_addr(PEER_UDP_IP);

  char msg[] = "ALIVE";
  char buf[16];

  fd_set readfds;
  struct timeval tv;

  auto lastReceived = std::chrono::steady_clock::now();
  udpWatchdogLost = false;

  while (udpWatchdogRunning) {
    sendto(sockfd, msg, sizeof(msg), 0, (sockaddr *)&peerAddr,
           sizeof(peerAddr));

    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);
    tv.tv_sec = UDP_WATCHDOG_TIMEOUT;
    tv.tv_usec = 0; // 100 * 1000; // 100 ms

    int rv = select(sockfd + 1, &readfds, NULL, NULL, &tv);
    if (rv > 0 && FD_ISSET(sockfd, &readfds)) {
      sockaddr_in fromAddr = {};
      socklen_t fromLen = sizeof(fromAddr);
      int n = recvfrom(sockfd, buf, sizeof(buf), 0, (sockaddr *)&fromAddr,
                       &fromLen);
      if (n > 0) {
        lastReceived = std::chrono::steady_clock::now();
        if (udpWatchdogLost) {
          notifyUdpRestored();
          udpWatchdogLost = false;
        }
      }
    }

    auto now = std::chrono::steady_clock::now();
    auto ms_since = std::chrono::duration_cast<std::chrono::milliseconds>(
                        now - lastReceived)
                        .count();
    if (ms_since > UDP_WATCHDOG_TIMEOUT_MS && !udpWatchdogLost) {
      udpWatchdogLost = true;
      notifyUdpLost();
    }

    std::this_thread::sleep_for(
        std::chrono::milliseconds(UDP_WATCHDOG_PERIOD_MS));
  }

  close(sockfd);
}

void COM::notifyUdpLost() {
  std::cerr << "[UDP-Watchdog] Verbindung zur Gegenseite verloren!"
            << std::endl;
  disconnected = true;
  _pulse lostComEvent;
  lostComEvent.code = static_cast<int8_t>(Topic::ERROR);
  lostComEvent.value.sival_int = static_cast<int>(Error_Enum::ERROR_C_LOST_COM);
  sendToDispatcher(lostComEvent, static_cast<int>(EventPriority::FIRST_PRIO));
}

void COM::notifyUdpRestored() {

  disconnected = false;

  std::cout << "[UDP-Watchdog] Verbindung zur Gegenseite wiederhergestellt!"
            << std::endl;
  _pulse reconnectEvent;
  reconnectEvent.code = static_cast<int8_t>(Topic::COM);
  reconnectEvent.value.sival_int = static_cast<int>(COM_Enum::COM_CONNECTED);
  sendToDispatcher(reconnectEvent, static_cast<int>(EventPriority::FIRST_PRIO));

  // Prepare status events
  _pulse rampEvent;
  rampEvent.code = static_cast<int8_t>(Topic::COM);
  rampEvent.value.sival_int = rampfull
                                  ? static_cast<int>(COM_Enum::RAMP_FULL)
                                  : static_cast<int>(COM_Enum::RAMP_NOT_FULL);
  _pulse mqttEvent;
  mqttEvent.code = static_cast<int8_t>(Topic::COM);
  mqttEvent.value.sival_int =
      mqttConnected ? static_cast<int>(COM_Enum::COM_MQTT_CONNECTED)
                    : static_cast<int>(COM_Enum::COM_MQTT_DISCONNECTED);
  {
    std::lock_guard<std::mutex> lock(queueMutex);
    lowPriorityQueue.push_front(rampEvent);
    lowPriorityQueue.push_front(mqttEvent);
  }
}
// ==============================================

// ========== Alle nötigen Handler aus deinem alten Code ==========

void COM::handleInterruptTopic(int originalValue, _pulse &dispatcherMsg) {
  InterruptEnum interruptEvent = static_cast<InterruptEnum>(originalValue);
  switch (interruptEvent) {
  case InterruptEnum::BUTTON_ESTOP_PRESSED:
    dispatcherMsg.code = static_cast<int>(Topic::COM);
    dispatcherMsg.value.sival_int =
        static_cast<int>(COM_Enum::BUTTON_ESTOP_PRESSED);
    highPriorityQueue.push_front(dispatcherMsg);
    break;
  case InterruptEnum::BUTTON_ESTOP_RELEASED:
    dispatcherMsg.code = static_cast<int>(Topic::COM);
    dispatcherMsg.value.sival_int =
        static_cast<int>(COM_Enum::BUTTON_ESTOP_RELEASED);
    highPriorityQueue.push_front(dispatcherMsg);
    break;
  case InterruptEnum::BUTTON_RESET_PRESSED:
    dispatcherMsg.code = static_cast<int>(Topic::COM);
    dispatcherMsg.value.sival_int =
        static_cast<int>(COM_Enum::BUTTON_RESET_PRESSED);
    highPriorityQueue.push_front(dispatcherMsg);
    break;
  default:
    break;
  }
}

void COM::handleInternalTopic(int originalValue, _pulse &dispatcherMsg) {
  Internal_Enum internalEvent = static_cast<Internal_Enum>(originalValue);
  switch (internalEvent) {
  case Internal_Enum::RESET_TO_FLAT:
    dispatcherMsg.code = static_cast<int>(Topic::COM);
    dispatcherMsg.value.sival_int = static_cast<int>(COM_Enum::RESET_TO_FLAT);
    lowPriorityQueue.push_back(dispatcherMsg);
    break;
  case Internal_Enum::RESET_TO_TALL:
    dispatcherMsg.code = static_cast<int>(Topic::COM);
    dispatcherMsg.value.sival_int = static_cast<int>(COM_Enum::RESET_TO_TALL);
    lowPriorityQueue.push_back(dispatcherMsg);
    break;
  case Internal_Enum::RESET_TO_TALL_W_METAL:
    dispatcherMsg.code = static_cast<int>(Topic::COM);
    dispatcherMsg.value.sival_int =
        static_cast<int>(COM_Enum::RESET_TO_TALL_W_METAL);
    lowPriorityQueue.push_back(dispatcherMsg);
    break;
  case Internal_Enum::RAMP_NOT_FULL:
    dispatcherMsg.code = static_cast<int>(Topic::COM);
    dispatcherMsg.value.sival_int = static_cast<int>(COM_Enum::RAMP_NOT_FULL);
    lowPriorityQueue.push_back(dispatcherMsg);
    rampfull = false;
    break;
  case Internal_Enum::RAMP_FULL:
    dispatcherMsg.code = static_cast<int>(Topic::COM);
    dispatcherMsg.value.sival_int = static_cast<int>(COM_Enum::RAMP_FULL);
    lowPriorityQueue.push_back(dispatcherMsg);
    rampfull = true;
    break;
  default:
    break;
  }
}

void COM::handleComTopic(int originalValue, _pulse &dispatcherMsg) {
  if (originalValue == static_cast<int>(COM_Enum::TIMEOUT_COM) ||
      originalValue == static_cast<int>(COM_Enum::COM_CONNECTED) ||
      originalValue == static_cast<int>(COM_Enum::HEARTBEAT) ||
      originalValue == static_cast<int>(COM_Enum::RAMP_FULL) ||
      originalValue == static_cast<int>(COM_Enum::RAMP_NOT_FULL) ||
      originalValue == static_cast<int>(COM_Enum::RESET_TO_FLAT) ||
      originalValue == static_cast<int>(COM_Enum::RESET_TO_TALL) ||
      originalValue == static_cast<int>(COM_Enum::RESET_TO_TALL_W_METAL) ||
      originalValue == static_cast<int>(COM_Enum::BUTTON_ESTOP_PRESSED) ||
      originalValue == static_cast<int>(COM_Enum::BUTTON_ESTOP_RELEASED) ||
      originalValue == static_cast<int>(COM_Enum::BUTTON_RESET_PRESSED)) {
    return;
  }
  if (FBM == 1) {
    if ((originalValue == static_cast<int>(COM_Enum::FBM_2_BUSY) ||
         originalValue == static_cast<int>(COM_Enum::FBM_2_READY)) ||
        originalValue == static_cast<int>(COM_Enum::TRANSFER_FAILED) ||
        originalValue == static_cast<int>(COM_Enum::TRANSFER_DONE))
      return;
  }
  if (FBM == 2) {
    if (originalValue == static_cast<int>(COM_Enum::TRANSFER_START_TALL) ||
        originalValue == static_cast<int>(COM_Enum::TRANSFER_START_FLAT) ||
        originalValue == static_cast<int>(COM_Enum::TRANSFER_START_OTHER) ||
        originalValue ==
            static_cast<int>(COM_Enum::TRANSFER_START_TALL_W_METAL) ||
        originalValue ==
            static_cast<int>(COM_Enum::TRANSFER_START_TALL_SORT_OUT) ||
        originalValue ==
            static_cast<int>(COM_Enum::TRANSFER_START_FLAT_SORT_OUT) ||
        originalValue ==
            static_cast<int>(COM_Enum::TRANSFER_START_TALL_W_METAL_SORT_OUT) ||
        originalValue == static_cast<int>(COM_Enum::REQUEST_TRANSFER) ||
        originalValue == static_cast<int>(COM_Enum::REQUEST_TRANSFER_SORT))
      return;
  }
  lowPriorityQueue.push_back(dispatcherMsg);
}

void COM::handleRemConTopic(int originalValue, _pulse &dispatcherMsg) {
  switch (originalValue) {
  case static_cast<int>(RemoteControlEnum::MQTT_CONNECTED):
    mqttConnected = true;
    dispatcherMsg.code = static_cast<int>(Topic::COM);
    dispatcherMsg.value.sival_int =
        static_cast<int>(COM_Enum::COM_MQTT_CONNECTED);
    lowPriorityQueue.push_back(dispatcherMsg);
    break;
  default:
    break;
  }
}

void COM::processMessage(const _pulse &msg) {
  if (msg.code == ((int)Topic::COM)) {
    if (msg.value.sival_int == ((int)COM_Enum::BUTTON_ESTOP_PRESSED ||
                                (int)COM_Enum::BUTTON_ESTOP_RELEASED)) {
      sendToDispatcher(msg, (int)EventPriority::FIRST_PRIO);
    } else if (msg.value.sival_int !=
               (((int)COM_Enum::TIMEOUT_COM) || ((int)COM_Enum::HEARTBEAT))) {
      sendToDispatcher(msg);
    }
  } else if (msg.code == (int)Topic::ID) {
    sendToDispatcher(msg);
  } else {
    printf("Received non COM Topic & non id Topic from other machine: Event "
           "Code: %d, Event Value: %d\n",
           msg.code, msg.value.sival_int);
  }
}

void COM::sendToDispatcher(const _pulse &msg, int priority) {
  _dispatcherSen->send_event(msg.code, (int)msg.value.sival_int, priority);
}
