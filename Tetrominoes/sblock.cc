#include "sblock.h"
#include "square.h"
#include "../Other/state.h"
using namespace std;

SBlock::SBlock(const SBlock *t): Tetromino{t->getLevel(), t->getWidth(), t->getHeight(), t->getNumOrientations(), t->getCount(), t->getCurrentRow(), t->getCurrentCol()} {
  for (Square *square: t->squares) {
    squares.push_back(new Square{nullptr, square->getRow(), square->getCol(), square->getState()});
  }
}

SBlock::SBlock(int level): Tetromino{level, 3, 2, 2} { 
  State s = State{SquareType::S};
  squares.push_back(new Square{nullptr, 2, 1, s});
  squares.push_back(new Square{nullptr, 2, 2, s});
  squares.push_back(new Square{nullptr, 3, 0, s});
  squares.push_back(new Square{nullptr, 3, 1, s});
}

SBlock *SBlock::left() const {
  SBlock *copy = new SBlock{this};
  copy->l();
  return copy;
}

SBlock *SBlock::right() const {
  SBlock *copy = new SBlock{this};
  copy->r();
  return copy;
}

SBlock *SBlock::down() const {
  SBlock *copy = new SBlock{this};
  copy->d();
  return copy;
}

SBlock *SBlock::clockwise() const {
  SBlock *copy = new SBlock{this};
  // This ensures that we don't ever need to align an SBlock
  if (getWidth() == 3) {
    copy->cw();
  }
  else {
    copy->ccw();
  }
  return copy;
}

SBlock *SBlock::counterclockwise() const {
  // counterclockwise is the same as clockwise for SBlock
  return clockwise();
}
