// main.cpp
// Startpunkt des Programms: Entscheidet anhand eines Puls- oder Kommandozeilenparameters, ob kalibriert oder gemessen wird

#include <iostream>
#include <string>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include "TSCADC.h"
#include "ADC.h"

extern void kalibriereBauteile(ADC& adc, TSCADC& tscadc, float bandVoltage);
extern std::string fuehreMessungAus(ADC& adc, TSCADC& tscadc, float bandVoltage);

#define SAMPLE_COUNT 100
#define REF_VOLTAGE 1.8f
#define R25 1000.0f
#define R26 4700.0f
#define VOLTAGE_DIVIDER_FACTOR ((R25 + R26) / R25)

float ermittleBandspannung(ADC& adc, TSCADC& tscadc) {
    float sum = 0;
    for (int i = 0; i < SAMPLE_COUNT; ++i) {
        adc.sample();
        usleep(1000);
        uint32_t raw = tscadc.fifoADCDataRead(Fifo::FIFO_0);
        float voltage = (raw / 4095.0f) * REF_VOLTAGE;
        sum += voltage * VOLTAGE_DIVIDER_FACTOR;
    }
    return sum / SAMPLE_COUNT;
}

int main(int argc, char* argv[]) {
    ThreadCtl(_NTO_TCTL_IO, 0);
    TSCADC tscadc;
    ADC adc(tscadc);

    float bandVoltage = ermittleBandspannung(adc, tscadc);
    std::cout << "Ermittelte Bandspannung: " << bandVoltage << " V\n";

    //std::string mode = (argc > 1) ? argv[1] : "measure";
    int mode = 0;

    if (mode) {
        kalibriereBauteile(adc, tscadc, bandVoltage);
    } else {
        std::string result = fuehreMessungAus(adc, tscadc, bandVoltage);
        std::cout << "Erkanntes Bauteil: " << result << "\n";
    }
    return 0;
}
