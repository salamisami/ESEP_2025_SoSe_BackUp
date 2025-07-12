#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <stdexcept>
#include <unordered_map>
#include <vector>

enum class MotorPieceState { FAST, SLOW, STOPPED, DELETE_W_MOTOR };

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

  void remove(int id) {
    if (container.erase(id) == 0) {
#ifdef TEST_MOTOR_THROW
      throw std::runtime_error("ID not found");
#endif
    }
  }

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
};

#endif // STATECONTAINER_H
