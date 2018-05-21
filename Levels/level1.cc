#include <string>
#include "level1.h"
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

Level1::Level1(int seed): Level{1, 12} {
  srand(seed);
}

// Level1 creates S and Z blocks with 1/12 probability and every other block with 1/6 probability
Tetromino *Level1::createNextBlock() {
  int randNum = rand() % getDenominator() + 1;
  Tetromino *nextBlock = nullptr;

  if (randNum <= 2) {
    nextBlock = createBlock("I");
  }
  else if (randNum <= 4) {
    nextBlock = createBlock("J");
  }
  else if (randNum <= 6) {
    nextBlock = createBlock("L");
  }
  else if (randNum <= 8) {
    nextBlock = createBlock("O");
  }
  else if (randNum <= 10) {
    nextBlock = createBlock("T");
  }
  else if (randNum <= 11) {
    nextBlock = createBlock("S");
  }
  else if (randNum <= 12) {
    nextBlock = createBlock("Z");
  }
  
  return nextBlock;
}

// Level 1 does not have an external constructive force
Tetromino *Level1::createSingleBlock() {
  return nullptr;
}

void Level1::norandom(string fileName) {
  // Level1 is entirely random
}

void Level1::random() {
  
}

void Level1::resetBlocksPlaced() {
  // Level 1 does not keep track of the blocks placed
}
