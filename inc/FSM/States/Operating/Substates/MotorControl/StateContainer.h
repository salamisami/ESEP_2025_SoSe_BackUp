#include <vector>
#include <algorithm>
#include <stdexcept>

enum class MotorPieceState {
    FAST,
    SLOW,
    STOPPED
};

struct StateEntry {
    int id;
    MotorPieceState motorPieceState;
};

class StateContainer {
    std::vector<StateEntry> entries;
    
public:
    void add(int id, MotorPieceState motorPieceState) {
        if (std::any_of(entries.begin(), entries.end(), 
                       [id](const StateEntry& e) { return e.id == id; })) {
            throw std::runtime_error("ID already exists");
        }
        entries.push_back({id, motorPieceState});
    }
    
    void remove(int id) {
        entries.erase(std::remove_if(entries.begin(), entries.end(),
                      [id](const StateEntry& e) { return e.id == id; }),
                      entries.end());
    }
    
    void updateState(int id, MotorPieceState newState) {
        auto it = std::find_if(entries.begin(), entries.end(),
                              [id](const StateEntry& e) { return e.id == id; });
        if (it != entries.end()) {
            it->motorPieceState = newState;
        } else {
            throw std::runtime_error("ID not found");
        }
    }
    
    void updateStateAll(MotorPieceState newState) {
        for (auto& entry : entries) {
            entry.motorPieceState = newState;
        }
    }
    
    MotorPieceState getState(int id) const {
        auto it = std::find_if(entries.begin(), entries.end(),
                              [id](const StateEntry& e) { return e.id == id; });
        if (it != entries.end()) {
            return it->motorPieceState;
        }
        throw std::runtime_error("ID not found");
    }
    
    bool contains(int id) const {
        return std::any_of(entries.begin(), entries.end(),
                          [id](const StateEntry& e) { return e.id == id; });
    }
    
    std::vector<int> getAllIds() const {
        std::vector<int> ids;
        ids.reserve(entries.size());
        for (const auto& entry : entries) {
            ids.push_back(entry.id);
        }
        return ids;
    }
    
    size_t size() const {
        return entries.size();
    }
};
