#include "hintblock.h"
#include "square.h"
#include "../Other/state.h"
using namespace std;

HintBlock::HintBlock(const HintBlock &other): Tetromino{other.getLevel(), other.getWidth(), other.getHeight(), other.getNumOrientations(), other.getCount(), other.getCurrentRow(), other.getCurrentCol()} {
  for (auto &square: other.getSquares()) {
    squares.push_back(new Square{nullptr, square->getRow(), square->getCol(), State{SquareType::Hint}});
  }
}

HintBlock::HintBlock(const Tetromino *t): Tetromino{t->getLevel(), t->getWidth(), t->getHeight(), t->getNumOrientations(), t->getCount(), t->getCurrentRow(), t->getCurrentCol()} {
  for (auto &square: t->getSquares()) {
    squares.push_back(new Square{nullptr, square->getRow(), square->getCol(), State{SquareType::Hint}});
  }
}

void HintBlock::moveLeft() {
  l();
}

void HintBlock::moveRight() {
  r();
}

void HintBlock::moveDown() {
  d();
}

void HintBlock::rotateClockwise() {
  cw();
}

void HintBlock::rotateCounterclockwise() {
  ccw();
}

HintBlock *HintBlock::left() const {
  HintBlock *copy = new HintBlock{this};
  copy->l();
  return copy;
}

HintBlock *HintBlock::right() const {
  HintBlock *copy = new HintBlock{this};
  copy->r();
  return copy;
}

HintBlock *HintBlock::down() const {
  HintBlock *copy = new HintBlock{this};
  copy->d();
  return copy;
}

HintBlock *HintBlock::clockwise() const {
  HintBlock *copy = new HintBlock{this};
  copy->cw();
  return copy;
}

HintBlock *HintBlock::counterclockwise() const {
  HintBlock *copy = new HintBlock{this};
  copy->ccw();
  return copy;
}
