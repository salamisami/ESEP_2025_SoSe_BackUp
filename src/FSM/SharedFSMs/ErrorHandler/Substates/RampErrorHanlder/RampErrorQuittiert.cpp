#include "RampErrorQuittiert.h"

RampErrorQuittiert::RampErrorQuittiert(ContextData *data) : State(data) {}

RampErrorQuittiert::~RampErrorQuittiert() {}

void RampErrorQuittiert::entry() {
  PRINT_STATE;

  data->sender->send_event((int8_t)Topic::ACTUATOR,
                           (int)ActuatorEnum::TRAFFIC_RED_ON);
}

void RampErrorQuittiert::exit() { PRINT_STATE; }

State *RampErrorQuittiert::ramp_not_full() {
  data->is_ramp_full_local = false;
  if (!data->is_ramp_full_local && !data->is_ramp_full_com) {
    return new RampErrorResolved(data);
  }
  return nullptr;
}

State *RampErrorQuittiert::com_ramp_not_full() {
  data->is_ramp_full_com = false;
  if (!data->is_ramp_full_local && !data->is_ramp_full_com) {
    return new RampErrorResolved(data);
  }
  return nullptr;
}

State *RampErrorQuittiert::clone() { return new RampErrorQuittiert(data); }
