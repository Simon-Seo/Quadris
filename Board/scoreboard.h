#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <iostream>
#include "../Other/observer.h"
#include "../Other/subject.h"
#include "../Other/info.h"

class Subject;

class Scoreboard final: public Observer, public Subject {
  int score;
  int hiScore;
  int currentLevel;
  void updateHiScore();
public:
  Scoreboard(int startingLevel);
  void resetScore();
  void notify(Subject &whoNotified) override;
  void scoreRow(int rowsCleared);
  void setLevel(int newLevel);
  int getScore() const override;
  Info getInfo() const override;
  int getHiScore();
  int getCurrentLevel();
  friend std::ostream &operator<<(std::ostream &out, const Scoreboard &sb);
};

#endif

