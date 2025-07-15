#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <stdexcept>
#include <unordered_map>
#include <vector>

enum class MotorPieceState { FAST = 0, SLOW, STOPPED, DELETE_W_MOTOR };

class StateContainer {
  std::unordered_map<int, MotorPieceState> container;

public:
  void add(int id, MotorPieceState motorPieceState) {
    if (!container.emplace(id, motorPieceState).second) {
#ifdef TEST_MOTOR_THROW
      throw std::runtime_error("id already exists");
#endif
    }
  }

  void remove(int id) { container.erase(id); }

  void updateState(int id, MotorPieceState newState) {
    auto it = container.find(id);
    if (it != container.end()) {
      it->second = newState;
    } else {
#ifdef TEST_MOTOR_THROW
      throw std::runtime_error("ID not found");
#endif
    }
  }

  void updateStateAll(MotorPieceState newState) {
    for (auto &pair : container) {
      pair.second = newState;
    }
  }

  MotorPieceState getState(int id) const {
    auto it = container.find(id);
    if (it != container.end()) {
      return it->second;
    }
#ifdef TEST_MOTOR_THROW
    throw std::runtime_error("ID not found");
#endif
    return (MotorPieceState)-1;
  }

  bool contains(int id) const { return container.find(id) != container.end(); }

  std::vector<int> getAllIds() const {
    std::vector<int> ids;
    ids.reserve(container.size());
    for (const auto &pair : container) {
      ids.push_back(pair.first);
    }
    return ids;
  }

  size_t size() const { return container.size(); }

  bool isEmpty() const { return container.empty(); }

  // Helper function to update both motor states based on all workpieces
  void updateDataMotorFlags(StateContainer &workpieceList, bool &motor_stopped,
                            bool &motor_slowed, MotorPieceState requestedState,
                            int8_t pieceId) {
    motor_stopped = false;
    motor_slowed = false;
    if (requestedState != MotorPieceState::DELETE_W_MOTOR) {
      if (!workpieceList.contains(pieceId)) {
        workpieceList.add(pieceId, requestedState);
      }
      workpieceList.updateState(pieceId, requestedState);
    } else {
      if (workpieceList.contains(pieceId)) {
        workpieceList.remove(pieceId);
      }
      {
      }
    }
    // Get all IDs and check their states
    auto ids = workpieceList.getAllIds();
    for (int id : ids) {
      MotorPieceState state = workpieceList.getState(id);

      if (state == MotorPieceState::STOPPED) {
        motor_stopped = true;
      } else if (state == MotorPieceState::SLOW) {
        motor_slowed = true;
      }
    }
  }

  void clean(){
    auto id_list = getAllIds();
    for(int& id: id_list){
      remove(id);
    }
  }

  
};

#endif // STATECONTAINER_H
