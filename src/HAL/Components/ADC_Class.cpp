#include "ADC_Class.h"


//================================================= contructors & destructors ================================================
ADC_Class::ADC_Class(Mailbox<_pulse>* mailbox, I_Sender* sender)
    : tscadc(),
    adc(tscadc),
    sender(sender),
    mailbox(mailbox),
    running(false) {
    ADCThread = std::thread(&ADC_Class::eventLoop, this);
    ThreadCtl(_NTO_TCTL_IO, 0);
    bandVoltage = ADC_Utilities::define_band_voltage(adc, tscadc);
    std::cout << "Bandvoltage :" << bandVoltage << std::endl;
}

ADC_Class::~ADC_Class() {
    running = false;
    ADCThread.join();
}

void ADC_Class::calibrate() {
    ADC_Utilities::calibrateComponents(adc, tscadc, bandVoltage);
    sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_CALIBRATION_DONE);
}

void ADC_Class::measureClassifySend() {
    ADC_Enum name = ADC_Utilities::executeMeasurement(adc, tscadc, bandVoltage);
    sender->send_event((int8_t) Topic::ADC, (int) name);
    std::cout << "Erkanntes Event " << (int) name << "\n";
}

void ADC_Class::adc_prepare(){
    ADC_Utilities::expect_piece(adc, tscadc, bandVoltage);
    sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_NEW_PIECE);
}

//===================================================== public functions ===============================================

void ADC_Class::adc_estop(){
    //TODO implement adc estop. Do not stop the eventLoop. Please see this function in .h file.
    std::cout << "Estop erhalten. Stoppe die ADC gerade 🛑" << std::endl;
}

void ADC_Class::eventLoop() {
    running = true;
    while(running) {
        _pulse pulse = mailbox->take();
        Topic code = static_cast<Topic>(pulse.code);
        ADC_Enum value = static_cast<ADC_Enum>(pulse.value.sival_int);

        if(code == Topic::STOP_THREAD) {
            //this is for destructor, we would not use this in end product.
            running = false;
            break;
        } else if(code != Topic::ADC) {
            THROW("unexpected topic");
        }

        switch(value) {
            case ADC_Enum::ADC_CALIBRATE:
                DEBUG("Calibrating Pieces 🛠️");
                calibrate();
                DEBUG("Calibrating Pieces done ✅");
                break;
            case ADC_Enum::ADC_MESURE:
                measureClassifySend();
                break;
            case ADC_Enum::ADC_PREPARE:
                adc_prepare();
                break;
            case ADC_Enum::ADC_STOP:
                adc_estop();
                break;
            default:
                THROW("unexpected event value");
        }
    }
}






