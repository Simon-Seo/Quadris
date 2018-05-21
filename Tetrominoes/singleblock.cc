#include "singleblock.h"
#include "square.h"
#include "../Other/state.h"
using namespace std;

SingleBlock::SingleBlock(int level): Tetromino{level, 1, 1, 1, 1, 3, 5} {
  squares.push_back(new Square{nullptr, 3, 5, State{SquareType::Single}});
}

SingleBlock *SingleBlock::left() const {
  return nullptr;
}

SingleBlock *SingleBlock::right() const {
  return nullptr;
}

SingleBlock *SingleBlock::down() const {
  return nullptr;
}

// SingleBlock cannot use the below transformations
SingleBlock *SingleBlock::clockwise() const {
  return nullptr;
}

SingleBlock *SingleBlock::counterclockwise() const {
  return nullptr;
}
