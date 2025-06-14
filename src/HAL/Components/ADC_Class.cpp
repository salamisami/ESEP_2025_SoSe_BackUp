#include "ADC_Class.h"


//================================================= contructors & destructors ================================================
ADC_Class::ADC_Class(I_Sender* sender)
    : tscadc(),
    adc(tscadc),
    sender(sender),
    adcStopped(false),
    running(false) {
    ThreadCtl(_NTO_TCTL_IO, 0);
    bandVoltage = ADC_Utilities::define_band_voltage(adc, tscadc);
    std::cout << "Bandvoltage :" << bandVoltage << std::endl;
}

ADC_Class::~ADC_Class() {
    adcStopped = false;
    running = false;
    //adc_thread.join();
}

void ADC_Class::calibrate() {
    if(adcStopped) {
        //TODO mögliches Event Hinzufügen
        std::cout << "E-Stopp gedrückt, Calibrierung nicht möglich " << "\n";
        return;
    }

    ADC_Utilities::calibrateComponents(adc, tscadc, bandVoltage);
    sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_CALIBRATION_DONE);
}

void ADC_Class::measureClassifySend() {
    if(adcStopped) {
        //TODO mögliches Event Hinzufügen
        std::cout << "E-Stopp gedrückt, Messung nicht möglich " << "\n";
        return;
    }

    ADC_Enum name = ADC_Utilities::executeMeasurement(adc, tscadc, bandVoltage);
    sender->send_event((int8_t) Topic::ADC, (int) name);
    std::cout << "Erkanntes Event " << (int) name << "\n";
}

void ADC_Class::adc_prepare() {
    if(adcStopped) {
        //TODO mögliches Event Hinzufügen
        std::cout << "E-Stopp gedrückt, Vorbereitung nicht mögllich" << "\n";
        return;
    }

    ADC_Utilities::expect_piece(adc, tscadc, bandVoltage, &adcStopped);
    sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_NEW_PIECE);
}

//===================================================== public functions ===============================================

void ADC_Class::adc_estop() {
    adcStopped = true;
    std::cout << "Estop erhalten. Stoppe die ADC gerade 🛑" << std::endl;
}

void ADC_Class::adc_reset() {
    adcStopped = false;
    std::cout << "Reset Erhalten. ADC funktionen wieder verfügbar ✅" << std::endl;
}

//TODO the event handling must be asynchronous
void ADC_Class::handle_event(_pulse event) {
    ADC_Enum value = static_cast<ADC_Enum>(event.value.sival_int);
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
        case ADC_Enum::ADC_RESET:
            adc_reset();
            break;
        default:
            break;
    }
}






