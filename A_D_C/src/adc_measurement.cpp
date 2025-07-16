// adc_measurement.cpp
// Führt eine Messung durch und klassifiziert anhand von gespeicherten Profilen

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <unistd.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <time.h>
#include <sstream>
#include "TSCADC.h"
#include "ADC.h"

#define REF_VOLTAGE 1.8f
#define SAMPLE_DELAY_NS 5000000L
#define TRIGGER_SCHRITT 0.3f
#define R25 1000.0f
#define R26 4700.0f
#define VOLTAGE_DIVIDER_FACTOR ((R25 + R26) / R25)
#define PROFIL_DATEI "ESEP-Team-1-1_25/profile_calibration.csv"
#define MESS_TOLERANZ  0.1f
#define MAX_WERT 400


struct Profil {
    std::string name;
    bool hatLoch;
    float avg;
    float lochMin;
    int lochStartIndex;
    int lochEndIndex;
};

std::vector<Profil> ladeProfile() {
    std::ifstream file(PROFIL_DATEI);
    std::vector<Profil> result;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        Profil p;
        std::getline(ss, p.name, ',');
        ss >> p.hatLoch; ss.ignore();
        ss >> p.avg; ss.ignore();
        ss >> p.lochMin; ss.ignore();
        ss >> p.lochStartIndex; ss.ignore();
        ss >> p.lochEndIndex; ss.ignore();
        result.push_back(p);
    }
    return result;
}

std::string klassifizieren(const std::vector<float>& werte, const std::vector<Profil>& profile) {
    if (werte.empty()) return "Fehler: keine Messwerte";

    float sum = 0;
    float minV = werte[0];
    int minIndex = 0;

    for (int i = 0; i < werte.size(); ++i) {
        float v = werte[i];
        sum += v;
        if (v < minV) {
            minV = v;
            minIndex = i;
        }
    }

    float avg = sum / werte.size();

    std::cout << "\n--- Klassifikation Debug ---\n";
    std::cout << "Mittelwert: " << avg << " V\n";
    std::cout << "Minimum:    " << minV << " V an Index " << minIndex << "\n";

    for (const auto& p : profile) {
        std::cout << "\nVergleiche mit Profil: " << p.name << "\n";
        std::cout << "  Soll-Avg: " << p.avg << " ±" << MESS_TOLERANZ << "\n";

        if (std::fabs(avg - p.avg) > MESS_TOLERANZ) {
            std::cout << "  → ❌ Mittelwert außerhalb Toleranz\n";
            continue;
        }

        if (!p.hatLoch) {
            std::cout << "  → ✅ Kein Loch erforderlich – passt\n";
            return p.name;
        }

        std::cout << "  Loch-Soll: " << p.lochMin << " ±" << MESS_TOLERANZ
                  << ", Index-Bereich: [" << p.lochStartIndex << " – " << p.lochEndIndex << "]\n";

        if (minV <= p.lochMin + MESS_TOLERANZ &&
            minIndex >= p.lochStartIndex &&
            minIndex <= p.lochEndIndex) {
            std::cout << "  → ✅ Loch passt\n";
            return p.name;
        } else {
            std::cout << "  → ❌ Lochbedingung nicht erfüllt\n";
            break;
            //SIgnal Aussenden !
        }
    }

    std::cout << "\n→ ❌ Kein passendes Profil gefunden\n";
    return "unbekannt";
}


std::string fuehreMessungAus(ADC& adc, TSCADC& tscadc, float bandVoltage) {
    std::vector<float> werte;
    struct timespec delay = {0, SAMPLE_DELAY_NS};
    bool erkannt = false;

    while (true) {
        adc.sample();
        usleep(1000);
        uint32_t raw = tscadc.fifoADCDataRead(Fifo::FIFO_0);
        float voltage = (raw / 4095.0f) * REF_VOLTAGE;
        float sensorVoltage = voltage * VOLTAGE_DIVIDER_FACTOR;

        if (!erkannt && sensorVoltage < bandVoltage - TRIGGER_SCHRITT) {
            erkannt = true;
            std::cout << "Bauteil erkannt – Messung startet\n";
        }
        if (erkannt) {
            werte.push_back(sensorVoltage);
            if (sensorVoltage > bandVoltage - TRIGGER_SCHRITT)
                break;
        }
        if (werte.size() >= MAX_WERT){
        	std::cout << "Ungültige Messanzahl, Bitte Laufband Kontrollieren\n";
        }
      }
        nanosleep(&delay, NULL);
    }

    auto profile = ladeProfile();
    return klassifizieren(werte, profile);
}
