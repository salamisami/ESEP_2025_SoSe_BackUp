// main.cpp
// Startpunkt des Programms: Entscheidet anhand eines Puls- oder Kommandozeilenparameters, ob kalibriert oder gemessen wird


#include "TSCADC.h"
#include "ADC.h"
#include "ADC_Utilities.h"

#include <iostream>
#include <string>
#include <hw/inout.h>
#include <sys/neutrino.h>



int main(int argc, char* argv[]) {
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
    return 0;
}
