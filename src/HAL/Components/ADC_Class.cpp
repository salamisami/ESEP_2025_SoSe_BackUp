#include "ADC_Class.h"

//================================================= contructors & destructors =================================================
ADC_Class::ADC_Class(int dispatcher_rcvid, name_attach_t* mailbox ) {
    ThreadCtl(_NTO_TCTL_IO, 0);
    TSCADC tscadc;
    ADC adc(tscadc);

    float bandVoltage = ADC_Utilities::define_band_voltage(adc, tscadc);
    std::cout << "Ermittelte Bandspannung: " << bandVoltage << " V\n";

    //std::string mode = (argc > 1) ? argv[1] : "measure";
    int mode = 0;

    if(mode) {
        ADC_Utilities::calibrateComponents(adc, tscadc, bandVoltage);
    } else {
        std::string result = ADC_Utilities::executeMeasurement(adc, tscadc, bandVoltage);
        //std::cout << "Erkanntes Bauteil: " << result << "\n";
    }
}

ADC_Class::~ADC_Class() {}

//===================================================== private functions =====================================================

//void ADC_Class::privateFunction(){}

//===================================================== public functions =====================================================

//void ADC_Class::publicFunction(){}