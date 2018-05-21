#include "tblock.h"
#include "square.h"
#include "../Other/state.h"
using namespace std;

TBlock::TBlock(const TBlock *t): Tetromino{t->getLevel(), t->getWidth(), t->getHeight(), t->getNumOrientations(), t->getCount(), t->getCurrentRow(), t->getCurrentCol()} {
  for (Square *square: t->squares) {
    squares.push_back(new Square{nullptr, square->getRow(), square->getCol(), square->getState()});
  }
}

TBlock::TBlock(int level): Tetromino{level, 3, 2, 4} {
  State t = State{SquareType::T};
  squares.push_back(new Square{nullptr, 2, 0, t});
  squares.push_back(new Square{nullptr, 2, 1, t});
  squares.push_back(new Square{nullptr, 2, 2, t});
  squares.push_back(new Square{nullptr, 3, 1, t});
}

TBlock *TBlock::left() const {
  TBlock *copy = new TBlock{this};
  copy->l();
  return copy;
}

TBlock *TBlock::right() const {
  TBlock *copy = new TBlock{this};
  copy->r();
  return copy;
}

TBlock *TBlock::down() const {
  TBlock *copy = new TBlock{this};
  copy->d();
  return copy;
}

TBlock *TBlock::clockwise() const {
  TBlock *copy = new TBlock{this};
  copy->cw();
  return copy;
}

TBlock *TBlock::counterclockwise() const {
  TBlock *copy = new TBlock{this};
  copy->ccw();
  return copy;
}
