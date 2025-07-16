// adc_calibration.cpp
// Modul zur Kalibrierung von Bauteilen am ADC

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <unistd.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <time.h>
#include "TSCADC.h"
#include "ADC.h"

#define REF_VOLTAGE 1.8f
#define SAMPLE_DELAY_NS 5000000L
#define TRIGGER_SCHRITT 0.3f
#define SAMPLE_COUNT 100
#define R25 1000.0f
#define R26 4700.0f
#define VOLTAGE_DIVIDER_FACTOR ((R25 + R26) / R25)
#define PROFIL_DATEI "ESEP-Team-1-1_25/profile_calibration.csv"
#define MESS_TOLERANZ  0.1f

struct Profil {
    std::string name;
    bool hatLoch;
    float avg;
    float lochMin;
    int lochStartIndex;
    int lochEndIndex;
};

void speichereProfil(const Profil& p) {

	std::ofstream file(PROFIL_DATEI, std::ios::app);
    if (!file.is_open() || file.fail()) {
        std::cerr << "[Fehler] Datei konnte nicht geöffnet werden: " << PROFIL_DATEI << "\n";
        return;
    }

    file << p.name << ","
    	 << p.hatLoch << ","
         << p.avg << ","
         << p.lochMin << ","
         << p.lochStartIndex << ","
         << p.lochEndIndex << "\n";


    std::cout << "Profil erfolgreich gespeichert: " << p.name << "\n";
}

void kalibriereBauteile(ADC& adc, TSCADC& tscadc, float bandVoltage) {
    struct timespec delay = {0, SAMPLE_DELAY_NS};


    // Liste der Bauteile und ob sie ein Loch besitzen
        std::vector<std::pair<std::string, bool>> bauteile = {
            {"WH", false},
            {"WF", false},
            {"W_B", true},
            {"W_BB", true},
            {"W_BM", true},
            {"W_BC", true},
			{"WH_Harz", false}
        };

    // Alte Datei löschen
    std::ofstream clear(PROFIL_DATEI, std::ios::trunc);
    clear.close();

    for (const auto& bauteil : bauteile) {
    	std::string name = bauteil.first;
    	bool hatLoch = bauteil.second;

        std::cout << "\nBitte platziere das Bauteil: " << name << "\n";
        std::vector<float> werte;
        bool bauteilErkannt = false;

        while (true) {
            adc.sample();
            usleep(1000);
            uint32_t raw = tscadc.fifoADCDataRead(Fifo::FIFO_0);
            float voltage = (raw / 4095.0f) * REF_VOLTAGE;
            float sensorVoltage = voltage * VOLTAGE_DIVIDER_FACTOR;

            if (!bauteilErkannt && sensorVoltage < bandVoltage - TRIGGER_SCHRITT) {
                bauteilErkannt = true;
                std::cout << "Bauteil erkannt – Messung startet\n";
            }

            if (bauteilErkannt) {
                werte.push_back(sensorVoltage);
                if (sensorVoltage > bandVoltage - TRIGGER_SCHRITT) break;
            }

            nanosleep(&delay, NULL);
        }

        if (werte.empty()) {
            std::cerr << "Keine Messwerte für " << name << ", überspringe.\n";
            continue;
        }

        // Auswertung: Mittelwert, Minimum und Indexbereich
        float sum = 0.0f;
        float lochMin = werte[0];
        int minIdx = 0;

        for (int i = 0; i < werte.size(); ++i) {
            sum += werte[i];
            if (werte[i] < lochMin) {
            	lochMin = werte[i];
                minIdx = i;
            }
        }

        float avg = sum / werte.size();
        Profil p;
                p.name = name;
                p.hatLoch = hatLoch;
                p.avg = avg;

                if (hatLoch) {
                    p.lochMin = lochMin;
                    p.lochStartIndex = std::max(0, minIdx - 5);
                    p.lochEndIndex = std::min(int(werte.size()) - 1, minIdx + 5);
                } else {
                    p.lochMin = 0.0f;
                    p.lochStartIndex = 0;
                    p.lochEndIndex = 0;
                }

                speichereProfil(p);
    }
}

