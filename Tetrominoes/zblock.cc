#include "zblock.h"
#include "square.h"
#include "../Other/state.h"
using namespace std;

ZBlock::ZBlock(const ZBlock *t): Tetromino{t->getLevel(), t->getWidth(), t->getHeight(), t->getNumOrientations(), t->getCount(), t->getCurrentRow(), t->getCurrentCol()} {
  for (Square *square: t->squares) {
    squares.push_back(new Square{nullptr, square->getRow(), square->getCol(), square->getState()});
  }
}

ZBlock::ZBlock(int level): Tetromino{level, 3, 2, 2} {
  State z = State{SquareType::Z};
  squares.push_back(new Square{nullptr, 2, 0, z});
  squares.push_back(new Square{nullptr, 2, 1, z});
  squares.push_back(new Square{nullptr, 3, 1, z});
  squares.push_back(new Square{nullptr, 3, 2, z});
}

ZBlock *ZBlock::left() const {
  ZBlock *copy = new ZBlock{this};
  copy->l();
  return copy;
}

ZBlock *ZBlock::right() const {
  ZBlock *copy = new ZBlock{this};
  copy->r();
  return copy;
}

ZBlock *ZBlock::down() const {
  ZBlock *copy = new ZBlock{this};
  copy->d();
  return copy;
}

ZBlock *ZBlock::clockwise() const {
  ZBlock *copy = new ZBlock{this};
  // This ensures that we don't ever need to align a ZBlock
  if (getWidth() == 3) {
    copy->cw(); 
  }
  else {
    copy->ccw();
  }
  return copy;
}

ZBlock *ZBlock::counterclockwise() const {
  // counterclockwise is the same as clockwise for ZBlock
  return clockwise();
}
