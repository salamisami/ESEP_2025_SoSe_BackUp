#include "Logic.h"

//================================================= constructors & destructors =================================================

Logic::Logic(I_Receiver* local_receiver, I_Sender* local_sender, I_Sender* to_self_sender)
    : local_receiver(local_receiver)
    , local_sender(local_sender)
    , to_self_sender(to_self_sender) {
    init();
}

Logic::Logic(I_Receiver* local_receiver, I_Sender* local_sender)
    : local_receiver(local_receiver)
    , local_sender(local_sender)
    , to_self_sender(local_sender) {
    init();
}

void Logic::init() {
    data = new ContextData(local_sender, to_self_sender);
    fsm = new Context<Boot>(data);
    logicRunning = true;
    logicThread = std::thread(&Logic::threadFunction, this);
}


Logic::~Logic() {
    logicRunning = false;
    if(logicThread.joinable()) {
        logicThread.join();
    }
    delete fsm;
    delete data;
}

//===================================================== private functions =====================================================

void Logic::threadFunction() {
    int eventNo = 0;
    while(logicRunning) {
        _pulse event;
        int status = local_receiver->receive_event(&event);
        if(status == 0) {
            eventNo++;
            printf("Event Number: %d\n", eventNo);

            int8_t topic = event.code;
            if(topic == (int8_t) Topic::STOP_THREAD) {
                logicRunning = false;
            }
            fsm->handleEvent(event);
        }
    }
}

//===================================================== public functions =====================================================

std::string Logic::show_state() {
    return fsm->show_state();
}