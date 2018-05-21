#include <iostream>
#include <vector>
#include "observer.h"
#include "subject.h"
#include "state.h"
using namespace std;

// Let the Observer subscribe to this Subject
void Subject::attach(Observer *ob) {
  observers.emplace_back(ob);
}

// Notify every Observer subscribed to this Subject
void Subject::notifyObservers() {
  for (auto &ob: observers) {
    ob->notify(*this);
  }
}

// Clear all observers subscribed to this Subject
void Subject::clearObservers() {
  observers.clear();
}

// Set a new State for this Subject
void Subject::setState(State newState) {
  state = newState;
}

// Return the state of this Subject
State Subject::getState() const {
  return state;
}
