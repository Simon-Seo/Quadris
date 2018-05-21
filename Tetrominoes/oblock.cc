#include "oblock.h"
#include "square.h"
#include "../Other/state.h"
using namespace std;

OBlock::OBlock(const OBlock *t): Tetromino{t->getLevel(), t->getWidth(), t->getHeight(), t->getNumOrientations(), t->getCount(), t->getCurrentRow(), t->getCurrentCol()} {
  for (Square *square: t->squares) {
    squares.push_back(new Square{nullptr, square->getRow(), square->getCol(), square->getState()});
  }
}

OBlock::OBlock(int level): Tetromino{level, 2, 2, 1} {
  State o = State{SquareType::O};
  squares.push_back(new Square{nullptr, 2, 0, o});
  squares.push_back(new Square{nullptr, 2, 1, o});
  squares.push_back(new Square{nullptr, 3, 0, o});
  squares.push_back(new Square{nullptr, 3, 1, o});
}

OBlock *OBlock::left() const {
  OBlock *copy = new OBlock{this};
  copy->l();
  return copy;
}

OBlock *OBlock::right() const {
  OBlock *copy = new OBlock{this};
  copy->r();
  return copy;
}

OBlock *OBlock::down() const {
  OBlock *copy = new OBlock{this};
  copy->d();
  return copy;
}

// OBlock doesn't need to rotate
OBlock *OBlock::clockwise() const {
  return new OBlock{this};
}

OBlock *OBlock::counterclockwise() const {
  return new OBlock{this};
}
