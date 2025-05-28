#include "Logic.h"

//================================================= contructors & destructors =================================================
Logic::Logic(I_Receiver* local_receiver, I_Sender* local_sender) {
    this->local_receiver = local_receiver;
    this->local_sender = local_sender;
    logicRunning = true;

    #ifdef MOCK
    #else
    //timer_sender = new PulseMsg::Sender(local_receiver->getchid());
    timer_sender = new Thread_COM::Sender(FBM_1_DISPATCHER);
    #endif
    logicThread = std::thread(&Logic::threadFunction, this);
}

// Logic::Logic(Mock_PM::Receiver* local_receiver, Mock_PM::Sender* local_sender, I_Sender* timer_sender) {
//     this->local_receiver = local_receiver;
//     this->local_sender = local_sender;
//     this->timer_sender = timer_sender;
//     logicRunning = true;
//     logicThread = std::thread(&Logic::threadFunction, this);
// }

Logic::~Logic() {
    logicRunning = false;
    if(logicThread.joinable()) {
        logicThread.join();
    }
    #ifdef MOCK
    #else
    delete timer_sender;
    #endif
}

//===================================================== private functions =====================================================

void Logic::threadFunction() {
    int eventNo = 0;
    ContextData data = ContextData(local_sender, local_receiver, timer_sender);
    Context<ModeHandler> fsm = Context<ModeHandler>(&data);
    while(logicRunning) {
        _pulse event;
        local_receiver->receive_event(&event);
        eventNo++;
        printf("Event Number: %d\n", eventNo);

        int8_t topic = event.code;
        if(topic == (int8_t) Topic::STOP_THREAD) {
            logicRunning = false;
        }
        fsm.handleEvent(event);
    }
    delete timer_sender;
}

//===================================================== public functions =====================================================

//void Logic::publicFunction(){}