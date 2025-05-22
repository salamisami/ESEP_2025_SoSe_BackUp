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

//=====================================================  private functions  ===================================================
//float ADC_Class::bandVoltage() {
//    float sum = 0;
//    for (int i = 0; i < SAMPLE_COUNT; ++i) {
//        adc.sample();
//        usleep(1000);
//        uint32_t raw = tscadc.fifoADCDataRead(Fifo::FIFO_0);
//        float voltage = (raw / 4095.0f) * REF_VOLTAGE;
//        sum += voltage * VOLTAGE_DIVIDER_FACTOR;
//    }
//    return sum / SAMPLE_COUNT;
//}

void ADC_Class::clibrate() {
	ADC_Utilities::calibrateComponents(adc, tscadc, bandVoltage);
}

void ADC_Class::messureClassfySend() {
	ADC_Enum name = ADC_Utilities::executeMeasurement(adc, tscadc, bandVoltage);
    //std::vector<Profil> profile = ladeProfile();
    //std::string name = klassifizieren(werte, profile);

    // Ergebnis per Pulse senden
    //TODO ergebnis noch in hex code wandeln
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
            	clibrate();
                break;

            case ADC_Enum::ADC_MESURE:
            	messureClassfySend();
                break;

//            case ActuatorEnum::STOP:
//                running = false;
//                break;

            default:
                std::cerr << "Unbekannter Aktor-Befehl\n";
        }
    }
}






