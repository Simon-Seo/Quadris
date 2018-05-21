#include <string>
#include "level2.h"
#include "../Other/state.h"
#include "../Tetrominoes/iblock.h"
#include "../Tetrominoes/jblock.h"
#include "../Tetrominoes/lblock.h"
#include "../Tetrominoes/oblock.h"
#include "../Tetrominoes/sblock.h"
#include "../Tetrominoes/tblock.h"
#include "../Tetrominoes/zblock.h"
#include "../Tetrominoes/tetromino.h"
using namespace std;

Level2::Level2(int seed): Level{2, 7} {
  srand(seed);
}

// Level2 creates each block with equal probability
Tetromino *Level2::createNextBlock() {
  int randNum = rand() % getDenominator() + 1;
  Tetromino *nextBlock = nullptr;
  
  if (randNum <= 1) {
    nextBlock = createBlock("I");
  }
  else if (randNum <= 2) {
    nextBlock = createBlock("J");
  }
  else if (randNum <= 3) {
    nextBlock = createBlock("L");
  }
  else if (randNum <= 4) {
    nextBlock = createBlock("O");
  }
  else if (randNum <= 5) {
    nextBlock = createBlock("T");
  }
  else if (randNum <= 6) {
    nextBlock = createBlock("S");
  }
  else if (randNum <= 7) {
    nextBlock = createBlock("Z");
  }
  
  return nextBlock;
}

// Level 2 does not have an external constructive force
Tetromino *Level2::createSingleBlock() {
  return nullptr;
}

void Level2::norandom(string fileName) {
  // Level2 is entirely random
}

void Level2::random() {

}

void Level2::resetBlocksPlaced() {
  // Level 2 does not keep track of the blocks placed
}
