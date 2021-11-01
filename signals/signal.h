#ifndef SIGNAL_H
#define SIGNAL_H

#include <functional>
#include <map>

// A signal object may call multiple slots with the
// same signature. You can connect functions to the signal
// which will be called when the emit() method on the
// signal object is invoked. Any argument passed to emit()
// will be passed to the given functions.


// Beispiele:
/*
 *
 *
class Button {
 public:
  Signal<> on_click;
};

class Message {
 public:
  void display() const {
    std::cout << "Hello World!" << std::endl;
  }
};

int main() {
  Button  button;
  Message message;

  button.on_click.connect_member(&message, &Message::display);
  button.on_click.emit();

  return 0;
}




#include "Signal.hpp"
#include <iostream>

int main() {

  // create new signal
  Signal<std::string, int> signal;

  // attach a slot
  signal.connect([](std::string arg1, int arg2) {
    std::cout << arg1 << " " << arg2 << std::endl;
  });

  signal.emit("The answer:", 42);

  return 0;
}




#include "Signal.hpp"
#include <iostream>

class Person {
public:
  Person(std::string const &name) : name_(name) {}

  Signal<std::string const&> say;

  void listen(std::string const& message) {
    std::cout << name_ << " received: " << message << std::endl;
  }

private:
  std::string name_;
};

int main() {
  Person alice("Alice"), bob("Bob");

  alice.say.connect_member(&bob, &Person::listen);
  bob.say.connect_member(&alice, &Person::listen);

  alice.say.emit("Have a nice day!");
  bob.say.emit("Thank you!");

  return 0;
}


*/




template <typename... Args>
class Signal {

 public:
  Signal()  = default;
  ~Signal() = default;

  // Copy constructor and assignment create a new signal.
  Signal(Signal const& /*unused*/) {}

  Signal& operator=(Signal const& other) {
    if (this != &other) {
      disconnect_all();
    }
    return *this;
  }

  // Move constructor and assignment operator work as expected.
  Signal(Signal&& other) noexcept:
    _slots(std::move(other._slots)),
    _current_id(other._current_id) {}

  Signal& operator=(Signal&& other) noexcept {
    if (this != &other) {
      _slots     = std::move(other._slots);
      _current_id = other._current_id;
    }

    return *this;
  }


  // Connects a std::function to the signal. The returned
  // value can be used to disconnect the function again.
  int connect(std::function<void(Args...)> const& slot) const {
    _slots.insert(std::make_pair(++_current_id, slot));
    return _current_id;
  }

   // Convenience method to connect a member function of an
   // object to this Signal.
  template <typename T>
  int connect_member(T *inst, void (T::*func)(Args...)) {
    return connect([=](Args... args) {
      (inst->*func)(args...);
    });
  }

  // Convenience method to connect a const member function
  // of an object to this Signal.
  template <typename T>
  int connect_member(T *inst, void (T::*func)(Args...) const) {
    return connect([=](Args... args) {
      (inst->*func)(args...);
    });
  }

  // Disconnects a previously connected function.
  void disconnect(int id) const {
    _slots.erase(id);
  }

  // Disconnects all previously connected functions.
  void disconnect_all() const {
    _slots.clear();
  }

  // Calls all connected functions.
  void emit(Args... p) {
    for (auto const& it : _slots) {
      it.second(p...);
    }
  }

  // Calls all connected functions except for one.
  void emit_for_all_but_one(int excludedConnectionID, Args... p) {
    for (auto const& it : _slots) {
      if (it.first != excludedConnectionID) {
        it.second(p...);
      }
    }
  }

  // Calls only one connected function.
  void emit_for(int connectionID, Args... p) {
    auto const& it = _slots.find(connectionID);
    if (it != _slots.end()) {
      it->second(p...);
    }
  }

 private:
  mutable std::map<int, std::function<void(Args...)>> _slots;
  mutable int                                         _current_id{0};
};

#endif /* SIGNAL_HPP */
