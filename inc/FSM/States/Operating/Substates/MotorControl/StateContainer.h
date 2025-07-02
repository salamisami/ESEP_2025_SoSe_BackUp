#include <vector>
#include <algorithm>
#include <stdexcept>

enum class State {
    FAST,
    SLOW,
    STOPPED
};

struct StateEntry {
    int id;
    State state;
};

class StateContainer {
    std::vector<StateEntry> entries;
    
public:
    void add(int id, State state) {
        if (std::any_of(entries.begin(), entries.end(), 
                       [id](const StateEntry& e) { return e.id == id; })) {
            throw std::runtime_error("ID already exists");
        }
        entries.push_back({id, state});
    }
    
    void remove(int id) {
        entries.erase(std::remove_if(entries.begin(), entries.end(),
                      [id](const StateEntry& e) { return e.id == id; }),
                      entries.end());
    }
    
    void updateState(int id, State newState) {
        auto it = std::find_if(entries.begin(), entries.end(),
                              [id](const StateEntry& e) { return e.id == id; });
        if (it != entries.end()) {
            it->state = newState;
        } else {
            throw std::runtime_error("ID not found");
        }
    }
    
    State getState(int id) const {
        auto it = std::find_if(entries.begin(), entries.end(),
                              [id](const StateEntry& e) { return e.id == id; });
        if (it != entries.end()) {
            return it->state;
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
