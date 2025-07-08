#include "Boot.h"

//================================================= constructors & destructors =================================================
Boot::Boot(ContextData* data) : State(data) {}

Boot::~Boot() {}

//===================================================== private functions =====================================================

//void Boot::privateFunction(){}

//===================================================== public functions =====================================================

void Boot::entry() {
    PRINT_STATE;
    //check if the config file exits
    bool time_config = false;
    if(FILE_EXISTS(SAVE_LOCATION_TIMEPROFILE)) {
        try {
            TimeProfileManager::load_profile(&data->timeprofile, SAVE_LOCATION_TIMEPROFILE);
            time_config = true;
        } catch(const std::runtime_error& e) {
            std::cerr << "Time config does not exist: " << e.what() << std::endl;
            time_config = false;
        }
    }

    bool adc_config = false;
    if (FILE_EXISTS(PROFIL_DATEI) ){
        adc_config = true;
    } else {
        std::cerr << "ADC config does not exist: " << std::endl;
    }

    data->config = (time_config && adc_config);
}

void Boot::exit() {
    PRINT_STATE;
}

State* Boot::is_pusher() {
    data->is_switch = false;
    DEBUG("Machine is Pusher Type");
    return new Modehandler(data);
}

State* Boot::is_switch() {
    data->is_switch = true;
    DEBUG("Machine is Switch Type");
    return new Modehandler(data);
}

State* Boot::clone() {
    return new Boot(data);
}