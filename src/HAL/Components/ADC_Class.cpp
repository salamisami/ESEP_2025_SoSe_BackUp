#include "ADC_Class.h"


//================================================= contructors & destructors ================================================
ADC_Class::ADC_Class(Mailbox<_pulse>* mailbox, I_Sender* sender)
    : tscadc(),
	  adc(tscadc),
	  sender(sender),
	  mailbox(mailbox),
	  running(false)
	{
	ADCThread = std::thread(&ADC_Class::eventLoop, this);
    ThreadCtl(_NTO_TCTL_IO, 0);
    bandVoltage = ADC_Utilities::define_band_voltage(adc, tscadc);
    std::cout << "Bandvoltage :" << bandVoltage;
}

ADC_Class::~ADC_Class() {
	ADCThread.join();
	running = false;
}

void ADC_Class::calibrate() {
	ADC_Utilities::calibrateComponents(adc, tscadc, bandVoltage);
}

void ADC_Class::measureClassifySend() {
	ADC_Enum name = ADC_Utilities::executeMeasurement(adc, tscadc, bandVoltage);
    sender->send_event((int8_t)Topic::ADC,(int)name);
    std::cout << "Erkanntes Event " << (int)name <<"\n";
}

//===================================================== public functions ===============================================
void ADC_Class::eventLoop() {
	running = true;

    while (running) {
        _pulse pulse = mailbox->take();
        Topic code = static_cast<Topic>(pulse.code);
        ADC_Enum value = static_cast<ADC_Enum>(pulse.value.sival_int);

        if (code != Topic::ADC) {
            THROW("unexpectet topic");
        }

        switch (value) {
            case ADC_Enum::ADC_CALIBRATE:
            	calibrate();
                break;

            case ADC_Enum::ADC_MESURE:
            	measureClassifySend();
                break;

//            case ActuatorEnum::STOP:
//                running = false;
//                break;

            default:
                std::cerr << "Unbekannter Aktor-Befehl\n";
        }
    }
}






