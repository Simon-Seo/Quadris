#include "lblock.h"
#include "square.h"
#include "../Other/state.h"
using namespace std;

LBlock::LBlock(const LBlock *t): Tetromino{t->getLevel(), t->getWidth(), t->getHeight(), t->getNumOrientations(), t->getCount(), t->getCurrentRow(), t->getCurrentCol()} {
  for (Square *square: t->squares) {
    squares.push_back(new Square{nullptr, square->getRow(), square->getCol(), square->getState()});
  }
}

LBlock::LBlock(int level): Tetromino{level, 3, 2, 4} {
  State l = State{SquareType::L};
  squares.push_back(new Square{nullptr, 2, 2, l});
  squares.push_back(new Square{nullptr, 3, 0, l});
  squares.push_back(new Square{nullptr, 3, 1, l});
  squares.push_back(new Square{nullptr, 3, 2, l});
}

LBlock *LBlock::left() const {
  LBlock *copy = new LBlock{this};
  copy->l();
  return copy;
}

LBlock *LBlock::right() const {
  LBlock *copy = new LBlock{this};
  copy->r();
  return copy;
}

LBlock *LBlock::down() const {
  LBlock *copy = new LBlock{this};
  copy->d();
  return copy;
}

LBlock *LBlock::clockwise() const {
  LBlock *copy = new LBlock{this};
  copy->cw();
  return copy;
}

LBlock *LBlock::counterclockwise() const {
  LBlock *copy = new LBlock{this};
  copy->ccw();
  return copy;
}
