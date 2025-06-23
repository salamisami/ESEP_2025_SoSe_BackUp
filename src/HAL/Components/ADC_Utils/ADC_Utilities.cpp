#include "ADC_Utilities.h"


//================================================= contructors & destructors =================================================


//===================================================== private functions =====================================================

//void ADC_Calibration::privateFunction(){}

//===================================================== public functions =====================================================

void ADC_Utilities::saveProfile(const Profil& p) {
    std::ofstream file(PROFIL_DATEI, std::ios::app);
    if(!file.is_open() || file.fail()) {
        THROW("[Fehler] Datei konnte nicht geöffnet werden: " + std::string(PROFIL_DATEI));
        return;
    }

    file << p.name << ","
        << static_cast<int32_t>(p.eventValue) << ","
        << p.hatLoch << ","
        << p.avg << ","
        << p.lochMin << ","
        << p.lochStartIndex << ","
        << p.lochEndIndex << "\n";


    std::cout << "Profil erfolgreich gespeichert: " << p.name << "\n";
}


void ADC_Utilities::calibrateComponents(ADC& adc, TSCADC& tscadc, float bandVoltage) {
    struct timespec delay = { 0, SAMPLE_DELAY_NS };

    // Liste der Bauteile und ob sie ein Loch besitzen
    std::vector<Bauteil> bauteile = {
        //TODO don't forget that this is commented out
        { "WH", ADC_Enum::ADC_WH_DETECT, false },
        { "WF", ADC_Enum::ADC_WF_DETECT, false },
        { "W_B", ADC_Enum::ADC_W_B_DETECT, true },
        { "W_BB", ADC_Enum::ADC_W_B_DETECT, true } //,
        // { "W_BM", ADC_Enum::ADC_W_NOT_DETECT, true },
        // { "W_BC", ADC_Enum::ADC_W_NOT_DETECT, true },
        // { "WH_Harz", ADC_Enum::ADC_W_NOT_DETECT, false }
    };

    // Alte Datei löschen
    std::ofstream clear(PROFIL_DATEI, std::ios::trunc);
    clear.close();

    for(const auto& bauteil : bauteile) {
        std::string name = bauteil.name;
        bool hatLoch = bauteil.hatLoch;
        ADC_Enum eventValue = bauteil.eventValue;

        std::cout << "\nBitte platziere das Bauteil: " << name << "\n";
        std::vector<float> werte;
        bool bauteilErkannt = false;

        while(true) {
            adc.sample();
            usleep(1000);
            uint32_t raw = tscadc.fifoADCDataRead(Fifo::FIFO_0);
            float voltage = (raw / 4095.0f) * REF_VOLTAGE;
            float sensorVoltage = voltage * VOLTAGE_DIVIDER_FACTOR;

            if(!bauteilErkannt && sensorVoltage < bandVoltage - TRIGGER_SCHRITT) {
                bauteilErkannt = true;
                std::cout << "Bauteil erkannt – Messung startet\n";
            }

            if(bauteilErkannt) {
                werte.push_back(sensorVoltage);
                if(sensorVoltage > bandVoltage - TRIGGER_SCHRITT) {
                    break;
                }
            }

            nanosleep(&delay, NULL);
        }

        if(werte.empty()) {
            std::cerr << "Keine Messwerte für " << name << ", überspringe.\n";
            continue;
        }

        // Auswertung: Mittelwert, Minimum und Indexbereich
        float sum = 0.0f;
        int safeStart = std::min<int>(10, werte.size() - 1);
        float lochMin = werte[safeStart];
        int minIdx = safeStart;

        for(size_t i = 0; i < werte.size(); ++i) {
            sum += werte[i];
            if(werte[i] < lochMin) {
                lochMin = werte[i];
                minIdx = i;
            }
        }

        float lochSchwelle = lochMin + 0.05f;
        int start = -1, ende = -1;

        for(size_t i = 0; i < werte.size(); ++i) {
            if(werte[i] <= lochSchwelle) {
                if(start == -1) start = i;
                ende = i;
            }
        }

        float avg = sum / werte.size();
        Profil p;
        p.name = name;
        p.hatLoch = hatLoch;
        p.eventValue = eventValue;
        p.avg = avg;

        if(hatLoch) {
            p.lochMin = lochMin;
            if(start != -1 && ende != -1) {
                p.lochStartIndex = start;
                p.lochEndIndex = ende;
            } else {
                // Kein klarer Lochbereich gefunden – als Fallback:
                p.lochStartIndex = minIdx;
                p.lochEndIndex = minIdx;
            }
        } else {
            p.lochMin = 0.0f;
            p.lochStartIndex = 0;
            p.lochEndIndex = 0;
        }

        saveProfile(p);
    }
}

std::vector<Profil> ADC_Utilities::loadProfile() {
    std::ifstream file(PROFIL_DATEI);
    std::vector<Profil> result;
    std::string line;
    while(std::getline(file, line)) {
        std::istringstream ss(line);
        Profil p;
        std::getline(ss, p.name, ',');

        int codeInt;
        ss >> codeInt; ss.ignore();
        p.eventValue = static_cast<ADC_Enum>(codeInt);

        ss >> p.hatLoch; ss.ignore();
        ss >> p.avg; ss.ignore();
        ss >> p.lochMin; ss.ignore();
        ss >> p.lochStartIndex; ss.ignore();
        ss >> p.lochEndIndex; ss.ignore();
        result.push_back(p);
    }
    return result;
}

ADC_Enum ADC_Utilities::classify(const std::vector<float>& value, const std::vector<Profil>& profile) {
    if(value.empty()) return ADC_Enum::ADC_W_NOT_DETECT; //TODO Fehler hinzufügen

    float sum = 0;
    float minV = value[0];
    int minIndex = 0;

    for(size_t i = 0; i < value.size(); ++i) {
        float v = value[i];
        sum += v;
        if(v < minV) {
            minV = v;
            minIndex = i;
        }
    }

    float avg = sum / value.size();

    std::cout << "\n--- Klassifikation Debug ---\n";
    std::cout << "Mittelwert: " << avg << " V\n";
    std::cout << "Minimum:    " << minV << " V an Index " << minIndex << "\n";
    std::cout << "Größe Messbereich: " << value.size() << "\n";

    for(const auto& p : profile) {
        std::cout << "\nVergleiche mit Profil: " << p.name << "\n";
        std::cout << "  Soll-Avg: " << p.avg << " ±" << MESS_TOLERANZ << "\n";

        if(std::fabs(avg - p.avg) > MESS_TOLERANZ) {
            std::cout << "  → ❌ Mittelwert außerhalb Toleranz\n";
            std::cout << "Aktuell:" << avg << "gespeichert:" << p.avg << "\n";
            continue;
        }

        if(!p.hatLoch) {
            std::cout << "  → ✅ Kein Loch erforderlich – passt\n";
            return p.eventValue;
        }

        std::cout << "  Loch-Soll: " << p.lochMin << " ±" << MESS_TOLERANZ
            << ", Index-Bereich: [" << p.lochStartIndex << " – " << p.lochEndIndex << "]\n";

        if(minV <= p.lochMin + MESS_TOLERANZ &&
            minIndex >= p.lochStartIndex &&
            minIndex <= p.lochEndIndex) {
            std::cout << "  → ✅ Loch passt\n";
            //TODO Spezifizieren!!!
            return p.eventValue;
        } else {
            std::cout << "  → ❌ Lochbedingung nicht erfüllt\n";
            break;
            //SIgnal Aussenden Error  !
        }
    }

    std::cout << "\n→ ❌ Kein passendes Profil gefunden\n";
    return ADC_Enum::ADC_W_NOT_DETECT;
}

void ADC_Utilities::expect_piece(ADC& adc, TSCADC& tscadc, float bandVoltage, bool* adcStopped) {
    std::vector<float> werte;
    struct timespec delay = { 0, SAMPLE_DELAY_NS };
    bool erkannt = false;
    while(!*adcStopped) {
        adc.sample();
        //TODO Magic number
        usleep(1000);
        uint32_t raw = tscadc.fifoADCDataRead(Fifo::FIFO_0);
        float voltage = (raw / 4095.0f) * REF_VOLTAGE;
        float sensorVoltage = voltage * VOLTAGE_DIVIDER_FACTOR;

        if(!erkannt && sensorVoltage < bandVoltage - TRIGGER_SCHRITT) {
            erkannt = true;
            return;
        }
        nanosleep(&delay, NULL);
    }
}

ADC_Enum ADC_Utilities::executeMeasurement(ADC& adc, TSCADC& tscadc, float bandVoltage) {
    std::vector<float> werte;
    struct timespec delay = { 0, SAMPLE_DELAY_NS };
    while(true) {
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


// ADC_Enum ADC_Utilities::executeMeasurement(ADC& adc, TSCADC& tscadc, float bandVoltage) {
//     std::vector<float> werte;
//     struct timespec delay = { 0, SAMPLE_DELAY_NS };
//     bool erkannt = false;

//     while(true) {
//         adc.sample();
//         usleep(1000);
//         uint32_t raw = tscadc.fifoADCDataRead(Fifo::FIFO_0);
//         float voltage = (raw / 4095.0f) * REF_VOLTAGE;
//         float sensorVoltage = voltage * VOLTAGE_DIVIDER_FACTOR;

//         if(!erkannt && sensorVoltage < bandVoltage - TRIGGER_SCHRITT) {
//             erkannt = true;
//             //TODO adc should send adc new piece event to logic here below
//             //sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_NEW_PIECE);
//             std::cout << "Bauteil erkannt – Messung startet\n";
//         }
//         if(erkannt) {
//             werte.push_back(sensorVoltage);
//             if(sensorVoltage > bandVoltage - TRIGGER_SCHRITT) {
//                 break;
//             }
//             if(werte.size() >= MAX_WERT) {
//                 //Error Event Ergänzen
//                 std::cout << "Ungültige Messanzahl, Bitte Laufband Kontrollieren\n";
//                 break;
//             }
//         }
//         nanosleep(&delay, NULL);
//     }
// }

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
