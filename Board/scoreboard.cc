#include <iostream>
#include <iomanip>
#include "scoreboard.h"
#include "../Other/subject.h"
using namespace std;

Scoreboard::Scoreboard(int startingLevel) : score{0}, hiScore{0}, currentLevel{startingLevel} {
  
}

void Scoreboard::updateHiScore() {
  hiScore = (score > hiScore) ? score : hiScore;
  notifyObservers();
}

void Scoreboard::resetScore() {
  score = 0;
}

void Scoreboard::notify(Subject &whoNotified) {
  score += whoNotified.getScore();
  updateHiScore();
}

void Scoreboard::scoreRow(int rowsCleared) {
  score += ((currentLevel + rowsCleared) * (currentLevel + rowsCleared));
  updateHiScore();
}

int Scoreboard::getScore() const {
  return score;
}

Info Scoreboard::getInfo() const {
  return Info{0, 0, SubjectType::Scoreboard};
}

int Scoreboard::getHiScore() {
  return hiScore;
}

int Scoreboard::getCurrentLevel() {
  return currentLevel;
}

void Scoreboard::setLevel(int newLevel) {
  currentLevel = (newLevel >= 0) ? newLevel : 0;
  notifyObservers();
}

ostream &operator<<(ostream &out, const Scoreboard &sb) {
  const int levelPadding = 9;
  const int scorePadding = 9;
  const int hiScorePadding = 6;
  out << "Level:" << setw(levelPadding) << sb.currentLevel << endl;
  out << "Score:" << setw(scorePadding) << sb.score << endl;
  out << "Hi Score:" << setw(hiScorePadding) << sb.hiScore << endl;
  return out;
}

