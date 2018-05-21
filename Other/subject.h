#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "state.h"
#include "info.h"

class Observer;

class Subject {
  std::vector<Observer *> observers;
  State state;
  
protected:
  void setState(State newState);
public:
  void attach(Observer *ob);
  void notifyObservers();
  void clearObservers();
  State getState() const;
  virtual int getScore() const = 0;
  virtual Info getInfo() const = 0;
};

#endif
