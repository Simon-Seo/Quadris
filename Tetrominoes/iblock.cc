#include "iblock.h"
#include "square.h"
#include "../Other/state.h"
using namespace std;

IBlock::IBlock(const IBlock *t): Tetromino{t->getLevel(), t->getWidth(), t->getHeight(), t->getNumOrientations(), t->getCount(), t->getCurrentRow(), t->getCurrentCol()} {
  for (Square *square: t->squares) {
    squares.push_back(new Square{nullptr, square->getRow(), square->getCol(), square->getState()});
  }
}

IBlock::IBlock(int level): Tetromino{level, 4, 1, 2} {
  State i = State{SquareType::I};
  squares.push_back(new Square{nullptr, 3, 0, i});
  squares.push_back(new Square{nullptr, 3, 1, i});
  squares.push_back(new Square{nullptr, 3, 2, i});
  squares.push_back(new Square{nullptr, 3, 3, i});
}

IBlock *IBlock::left() const {
  IBlock *copy = new IBlock{this};
  copy->l();
  return copy;
}

IBlock *IBlock::right() const {
  IBlock *copy = new IBlock{this};
  copy->r();
  return copy;
}

IBlock *IBlock::down() const {
  IBlock *copy = new IBlock{this};
  copy->d();
  return copy;
}

IBlock *IBlock::clockwise() const {
  IBlock *copy = new IBlock{this};
  // This ensures that we don't ever need to align an IBlock
  if (getWidth() == 4) {
    copy->cw();
  }
  else {
    copy->ccw();
  }
  return copy;
}

IBlock *IBlock::counterclockwise() const {
  // counterclockwise is the same as clockwise for IBlock
  return clockwise();
}
