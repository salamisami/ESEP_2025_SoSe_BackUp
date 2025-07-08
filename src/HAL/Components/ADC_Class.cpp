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
	if (adc_thread.joinable())
	adc_thread.join();
    //adc_thread.join();
}

void ADC_Class::calibrate() {
    if(adcStopped) {
        //TODO mögliches Event Hinzufügen
        std::cout << "E-Stopp gedrückt, Calibrierung nicht möglich " << "\n";
        return;
    }
    calibrate_mtx.lock();
    DEBUG("Calibrating Pieces 🛠️");
    ADC_Utilities::calibrateComponents(adc, tscadc, bandVoltage, &adcStopped );
    DEBUG("Calibrating Pieces done ✅");
    sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_CALIBRATION_DONE);
    calibrate_mtx.unlock();
}

void ADC_Class::measureClassifySend() {
    if(adcStopped) {
        //TODO mögliches Event Hinzufügen
        std::cout << "E-Stopp gedrückt, Messung nicht möglich " << "\n";
        return;
    }
    measure_mtx.lock();
    bool inTime = ADC_Utilities::expect_piece(adc,tscadc,bandVoltage, &adcStopped, ADC_TIMEOUT_TIME);// TODO: 200 Ms Zeit anpassen!!
    if(inTime){
    	sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_NEW_PIECE);
    	ADC_Enum name = ADC_Utilities::executeMeasurement(adc, tscadc, bandVoltage,&adcStopped);

    	sender->send_event((int8_t) Topic::ADC, (int) name);
    	if(name == ADC_Enum::ADC_INVALID_MESURE){
    		sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::ERROR_INVALID_MESURE);
    	}
    }else{
    	sender->send_event((int8_t) Topic::ADC,(int) ADC_Enum::ADC_TIMEOUT );
    }

    measure_mtx.unlock();
    //std::cout << "Erkanntes Event " << (int) name << "\n";
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
        case ADC_Enum::ADC_CALIBRATE: {
                std::thread calibrateThread(&ADC_Class::calibrate, this);
                calibrateThread.detach();
                break;
            }
        case ADC_Enum::ADC_MESURE: {
                std::thread measureThread(&ADC_Class::measureClassifySend, this);
                measureThread.detach();
                break;
            }
        case ADC_Enum::ADC_STOP:
            adc_estop();
            break;
            //async
        case ADC_Enum::ADC_RESET:
            adc_reset();
            break;
        default:
            break;
    }
}






