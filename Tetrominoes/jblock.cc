#include "jblock.h"
#include "square.h"
#include "../Other/state.h"
using namespace std;

JBlock::JBlock(const JBlock *t): Tetromino{t->getLevel(), t->getWidth(), t->getHeight(), t->getNumOrientations(), t->getCount(), t->getCurrentRow(), t->getCurrentCol()} {
  for (Square *square: t->squares) {
    squares.push_back(new Square{nullptr, square->getRow(), square->getCol(), square->getState()});
  }
}

JBlock::JBlock(int level): Tetromino{level, 3, 2, 4} {
  State j = State{SquareType::J};
  squares.push_back(new Square{nullptr, 2, 0, j});
  squares.push_back(new Square{nullptr, 3, 0, j});
  squares.push_back(new Square{nullptr, 3, 1, j});
  squares.push_back(new Square{nullptr, 3, 2, j});
}

JBlock *JBlock::left() const {
  JBlock *copy = new JBlock{this};
  copy->l();
  return copy;
}

JBlock *JBlock::right() const {
  JBlock *copy = new JBlock{this};
  copy->r();
  return copy;
}

JBlock *JBlock::down() const {
  JBlock *copy = new JBlock{this};
  copy->d();
  return copy;
}

JBlock *JBlock::clockwise() const {
  JBlock *copy = new JBlock{this};
  copy->cw();
  return copy;
}

JBlock *JBlock::counterclockwise() const {
  JBlock *copy = new JBlock{this};
  copy->ccw();
  return copy;
}
