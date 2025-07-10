#include "ADC_Utilities.h"


//================================================= contructors & destructors =================================================


//===================================================== private functions =====================================================

//void ADC_Calibration::privateFunction(){}

//===================================================== public functions =====================================================

void ADC_Utilities::saveProfile(const Profil& p) {
    std::ofstream file(PROFIL_DATEI, std::ios::app);
    if (!file.is_open() || file.fail()) {
        THROW("[Fehler] Datei konnte nicht geöffnet werden: " + std::string(PROFIL_DATEI));
        return;
    }

    file << p.name << ","
         << static_cast<int32_t>(p.eventValue) << ","
         << (p.hatLoch ? 1 : 0) << ","
         << p.avg << ","
         << p.minV << ","
         << p.stddev << ","
         << p.range << ","
         << p.lochMin << ","
         << p.lochStartIndex << ","
         << p.lochEndIndex << "\n";

    std::cout << "Profil erfolgreich gespeichert: " << p.name << "\n";
}

void ADC_Utilities::calibrateComponents(ADC& adc, TSCADC& tscadc, float bandVoltage, bool* adcStopped) {
    struct timespec delay = {0, SAMPLE_DELAY_NS};

    std::vector<Bauteil> bauteile = {
        { "WF", ADC_Enum::ADC_WF_DETECT, false },
        { "W_B", ADC_Enum::ADC_W_B_DETECT, true },
        { "W_BB", ADC_Enum::ADC_W_B_DETECT, true },
        { "W_BM", ADC_Enum::ADC_W_B_DETECT, true }
    };

    std::ofstream clear(PROFIL_DATEI, std::ios::trunc);
    clear.close();

    for (const auto& bauteil : bauteile) {
        std::string name = bauteil.name;
        bool hatLoch = bauteil.hatLoch;
        ADC_Enum eventValue = bauteil.eventValue;

        std::cout << "\nBitte platziere das Bauteil: " << name << "\n";
        std::vector<float> werte;
        bool bauteilErkannt = false;

        while (!*adcStopped) {
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
                if (sensorVoltage > bandVoltage - TRIGGER_SCHRITT) {
                    break;
                }
            }
            nanosleep(&delay, NULL);
        }

        if (werte.empty()) {
            std::cerr << "Keine Messwerte für " << name << ", überspringe.\n";
            continue;
        }

        // Feature-Berechnung
        float sum = 0.0f, sumSquares = 0.0f, minV = werte[0], maxV = werte[0];
        int minIdx = 0;
        for (size_t i = 0; i < werte.size(); ++i) {
            sum += werte[i];
            sumSquares += werte[i] * werte[i];
            if (werte[i] < minV) { minV = werte[i]; minIdx = i; }
            if (werte[i] > maxV) maxV = werte[i];
        }
        float avg = sum / werte.size();
        float stddev = std::sqrt(sumSquares / werte.size() - avg * avg);
        float range = maxV - minV;

        float lochMin = 0;
        int start = 0, ende = 0;
        if (hatLoch) {
            int safeStart = std::min<int>(10, werte.size() - 1);
            lochMin = werte[safeStart];
            int minIdx = safeStart;
            for (size_t i = 0; i < werte.size(); ++i) {
                if (werte[i] < lochMin) { lochMin = werte[i]; minIdx = i; }
            }
            float lochSchwelle = lochMin + 0.05f;
            start = -1; ende = -1;
            for (size_t i = 0; i < werte.size(); ++i) {
                if (werte[i] <= lochSchwelle) {
                    if (start == -1) start = i;
                    ende = i;
                }
            }
            if (start == -1) { start = minIdx; ende = minIdx; }
        }

        Profil p;
        p.name = name;
        p.hatLoch = hatLoch;
        p.eventValue = eventValue;
        p.avg = avg;
        p.minV = minV;
        p.stddev = stddev;
        p.range = range;

        if (hatLoch) {
            p.lochMin = lochMin;
            p.lochStartIndex = start;
            p.lochEndIndex = ende;
        } else {
            p.lochMin = 0.0f;
            p.lochStartIndex = 0;
            p.lochEndIndex = 0;
        }

        saveProfile(p);
    }
}


//std::vector<Profil> ADC_Utilities::loadProfile() {
//	if (!FILE_EXISTS(PROFIL_DATEI)) {
//		//Event: noch keine Datei erstellt
//	}
//    std::ifstream file(PROFIL_DATEI);
//    std::vector<Profil> result;
//    std::string line;
//    while(std::getline(file, line)) {
//        std::istringstream ss(line);
//        Profil p;
//        std::getline(ss, p.name, ',');
//
//        int codeInt;
//        ss >> codeInt; ss.ignore();
//        p.eventValue = static_cast<ADC_Enum>(codeInt);
//
//        ss >> p.hatLoch; ss.ignore();
//        ss >> p.avg; ss.ignore();
//        ss >> p.lochMin; ss.ignore();
//        ss >> p.lochStartIndex; ss.ignore();
//        ss >> p.lochEndIndex; ss.ignore();
//        result.push_back(p);
//    }
//    return result;
//}

std::vector<Profil> ADC_Utilities::loadProfile() {
    std::vector<Profil> result;

    if (!FILE_EXISTS(PROFIL_DATEI)) {
        //Event: noch keine Datei erstellt
        return result;
    }

    std::ifstream file(PROFIL_DATEI);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Überspringe leere Zeilen/Kommentare

        std::istringstream ss(line);
        Profil p;
        std::string token;

        // Reihenfolge muss zu Speicherfunktion passen!
        std::getline(ss, p.name, ',');

        int codeInt = 0;
        std::getline(ss, token, ',');
        codeInt = std::stoi(token);
        p.eventValue = static_cast<ADC_Enum>(codeInt);

        std::getline(ss, token, ',');
        p.hatLoch = (std::stoi(token) != 0);

        std::getline(ss, token, ',');
        p.avg = std::stof(token);

        std::getline(ss, token, ',');
        p.minV = std::stof(token);

        std::getline(ss, token, ',');
        p.stddev = std::stof(token);

        std::getline(ss, token, ',');
        p.range = std::stof(token);

        std::getline(ss, token, ',');
        p.lochMin = std::stof(token);

        std::getline(ss, token, ',');
        p.lochStartIndex = std::stoi(token);

        std::getline(ss, token, ',');
        p.lochEndIndex = std::stoi(token);

        result.push_back(p);
    }
    return result;
}

ADC_Enum ADC_Utilities::classify(const std::vector<float>& value, const std::vector<Profil>& profile) {
    if (value.empty()) return ADC_Enum::ADC_W_NOT_DETECT;

    // --- Feature-Berechnung für die aktuelle Messung ---
    float sum = 0, sumSquares = 0, minV = value[0], maxV = value[0];
    int minIndex = 0;
    for (size_t i = 0; i < value.size(); ++i) {
        float v = value[i];
        sum += v;
        sumSquares += v * v;
        if (v < minV) { minV = v; minIndex = i; }
        if (v > maxV) { maxV = v; }
    }
    float avg = sum / value.size();
    float stddev = std::sqrt(sumSquares / value.size() - avg * avg);
    float range = maxV - minV;

    // --- Loch-Check: Prüfen, ob ein ausgeprägtes Loch im Signal ist ---
    // Definiere, wie tief und breit das "Loch" sein muss (anpassbar!)
    constexpr float LOCH_TIEFE_MIN = 0.25f;    // min. Abstand avg - minV für echtes Loch
    constexpr int   LOCH_BREITE_MIN = 3;       // min. wie viele Werte "nahe Minimum" für echtes Loch
    constexpr float LOCH_NAEHE = 0.05f;        // Toleranz um minV herum für Loch-Breite

    // Zähle, wie viele Werte nahe dem Minimum liegen (für "Loch-Breite")
    int lochBreite = 0;
    for (float v : value) {
        if (std::fabs(v - minV) < LOCH_NAEHE) lochBreite++;
    }
    bool hatEchtesLoch = ((avg - minV) > LOCH_TIEFE_MIN) && (lochBreite >= LOCH_BREITE_MIN);

    // --- Debug-Ausgabe ---
    std::cout << "avg: " << avg << ", minV: " << minV << ", stddev: " << stddev << ", range: " << range << "\n";
    std::cout << "Loch erkannt? " << (hatEchtesLoch ? "JA" : "NEIN") << ", LochBreite: " << lochBreite << "\n";

    // --- Zuerst Profile OHNE Loch prüfen, wenn kein echtes Loch vorliegt ---
    if (!hatEchtesLoch) {
        for (const auto& p : profile) {
            if (!p.hatLoch) {
                if (std::fabs(avg - p.avg) < 0.2f && std::fabs(minV - p.minV) < 0.2f) {
                    std::cout << "Profil erkannt: " << p.name << " (ohne Loch)\n";
                    return p.eventValue;
                }
            }
        }
    }

    // --- Profile MIT Loch prüfen, wenn ein Loch erkannt wurde ---
    if (hatEchtesLoch) {
        for (const auto& p : profile) {
            if (p.hatLoch) {
                // Loch-Match: Mindesttiefe, Position & Bereichsvergleich
//                bool tiefeOK = std::fabs(minV - p.lochMin) < 0.3f;
//                bool indexOK = (minIndex >= p.lochStartIndex - 2 && minIndex <= p.lochEndIndex + 2);
                bool avgOK = std::fabs(avg - p.avg) < 0.3f;
                if (avgOK) {
                    std::cout << "Profil erkannt✅: " << p.name << " (mit Loch)\n";
                    return p.eventValue;
                }
            }
        }
    }

    // --- Fallback: Profil mit höchstem Score (optional) ---
    int bestScore = -1;
    ADC_Enum bestEvent = ADC_Enum::ADC_W_NOT_DETECT;
    for (const auto& p : profile) {
			int score = 0;
			if (std::fabs(avg - p.avg) < 0.2f) score++;
			if (std::fabs(minV - p.minV) < 0.2f) score++;
			if (std::fabs(stddev - p.stddev) < 0.1f) score++;
			if (std::fabs(range - p.range) < 0.2f) score++;
			if (score > bestScore) {
				bestScore = score;
				bestEvent = p.eventValue;
				//std::cout << "Profil: " << p.name  << "Score:" << bestScore << "\n";
//				if (bestScore >= 2) {
//					std::cout << "Profil erkannt ✅: " << p.name  << "\n";
//					return bestEvent;
			}
				if (bestScore >= 2) {
					std::cout << "Profil erkannt ✅: " << p.name << "Score:" << bestScore << "\n";
					return bestEvent;
        }
    }


    std::cout << "❌ Kein Profil erkannt! erreichter Score:" << bestScore << "\n";
    return ADC_Enum::ADC_W_NOT_DETECT;
}


bool ADC_Utilities::expect_piece(ADC& adc, TSCADC& tscadc, float bandVoltage, bool* adcStopped, int timeout_ms) {
    std::vector<float> werte;
    struct timespec delay = { 0, SAMPLE_DELAY_NS };
    bool erkannt = false;

    auto start_time = std::chrono::steady_clock::now();

    while (!*adcStopped) {
        adc.sample();
        usleep(1000);
        uint32_t raw = tscadc.fifoADCDataRead(Fifo::FIFO_0);
        float voltage = (raw / 4095.0f) * REF_VOLTAGE;
        float sensorVoltage = voltage * VOLTAGE_DIVIDER_FACTOR;

        if (!erkannt && sensorVoltage < bandVoltage - TRIGGER_SCHRITT) {
            erkannt = true;
            return true;
        }

        // Timeout prüfen
        auto now = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
        if (elapsed_ms > timeout_ms) {

            return false;
        }

        nanosleep(&delay, NULL);
    }
    return false;
}

ADC_Enum ADC_Utilities::executeMeasurement(ADC& adc, TSCADC& tscadc, float bandVoltage, bool* adcStopped) {
    std::vector<float> werte;
    struct timespec delay = { 0, SAMPLE_DELAY_NS };
    while(!*adcStopped) {
        adc.sample();
        usleep(1000);
        uint32_t raw = tscadc.fifoADCDataRead(Fifo::FIFO_0);
        float voltage = (raw / 4095.0f) * REF_VOLTAGE;
        float sensorVoltage = voltage * VOLTAGE_DIVIDER_FACTOR;

        werte.push_back(sensorVoltage);
        if(sensorVoltage > bandVoltage - TRIGGER_SCHRITT) {
            break;
        }
        if(werte.size() >= MAX_WERT) {
            //Error Event Ergänzen
            return ADC_Enum::ADC_INVALID_MESURE;
        }
        
        nanosleep(&delay, NULL);
    }

    auto profile = loadProfile();
    return classify(werte, profile);
}

float ADC_Utilities::define_band_voltage(ADC& adc, TSCADC& tscadc) {
    float sum = 0;
    for(int i = 0; i < SAMPLE_COUNT; ++i) {
        adc.sample();
        usleep(1000);
        uint32_t raw = tscadc.fifoADCDataRead(Fifo::FIFO_0);
        float voltage = (raw / 4095.0f) * REF_VOLTAGE;
        sum += voltage * VOLTAGE_DIVIDER_FACTOR;
    }
    return sum / SAMPLE_COUNT;
}
