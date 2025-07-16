#include <iostream>
#include <time.h>
#include <unistd.h>
#include "TSCADC.h"
#include "ADC.h"

#define SAMPLE_COUNT 100
#define SAMPLE_DELAY_NS 5000000L // 5ms = 200 Hz
#define REF_VOLTAGE 1.8f

////int main() {
//
////	for (int i = 0; i < 10; ++i) {
//		// Initialisierung
//		TSCADC tscadc;
//		ADC adc(tscadc);
//
//		// Spannungsteiler: R25 = 1k, R26 = 4.7k
//		const float R25 = 1000.0f;
//		const float R26 = 4700.0f;
//		const float VOLTAGE_DIVIDER_FACTOR = (R25 + R26) / R25;
//
//		struct timespec delay = {0, SAMPLE_DELAY_NS};
//
//		float sum = 0.0f;
//		//std::cout << "Starte synchronisierte Messung mit 200 Hz auf AIN0 (" << SAMPLE_COUNT << " Samples)...\n";
//
//		for (int i = 0; i < SAMPLE_COUNT; ++i) {
//			adc.sample(); // eine One-Shot-Messung triggern
//
//			// kleinen Delay geben, damit FIFO befüllt ist
//			usleep(1000);
//
//			// Rohwert auslesen
//			unsigned int raw = tscadc.fifoADCDataRead(Fifo::FIFO_0);
//
//			float voltage = (raw / 4095.0f) * REF_VOLTAGE;
//			float sensorVoltage = voltage * VOLTAGE_DIVIDER_FACTOR;
//
//			sum += sensorVoltage;
//
//			nanosleep(&delay, NULL);
//		}
//
//		float average = sum / SAMPLE_COUNT;
//		std::cout <<  average << "\r\n";
//
//	}
//	return 0;
////}
