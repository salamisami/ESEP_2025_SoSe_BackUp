#include "PendingTransferRequestNotAtEnd.h"

//================================================= constructors & destructors =================================================
PendingTransferRequestNotAtEnd::PendingTransferRequestNotAtEnd(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
  //substate = new SubState(data);
}

PendingTransferRequestNotAtEnd::~PendingTransferRequestNotAtEnd() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PendingTransferRequestNotAtEnd::entry() {
  PRINT_STATE;
  data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::REQUEST_TRANSFER);
}

void PendingTransferRequestNotAtEnd::exit() {
  PRINT_STATE;
}

State* PendingTransferRequestNotAtEnd::clone() {
  return new PendingTransferRequestNotAtEnd(data, localdata_);
}

State* PendingTransferRequestNotAtEnd::fbm_2_busy() {
  data->timer->start_timer(500, TIMER_ID::PENDINGTRANSFERREQUESTNOTATEND);
  return nullptr;
}

State* PendingTransferRequestNotAtEnd::fbm_2_ready() {
  return new MovingToEnd_PT1(data, localdata_);
}



State* PendingTransferRequestNotAtEnd::timer(TIMER_ID id) {
  if(id != TIMER_ID::PENDINGTRANSFERREQUESTNOTATEND){
    return new PendingTransferRequestNotAtEnd(data, localdata_);
  }
  return nullptr;
