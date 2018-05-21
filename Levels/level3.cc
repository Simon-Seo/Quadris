#include <string>
#include "level3.h"
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

Level3::Level3(int seed): Level{3, 9} {
  srand(seed);
}

// Level3 creates S and Z blocks with 2/9 probability and every other block with 1/9 probability
Tetromino *Level3::createNextBlock() {
  Tetromino *nextBlock = nullptr;

  if (getRandomness()) {
    int randNum = rand() % getDenominator() + 1;
    
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
    else if (randNum <= 7) {
      nextBlock = createBlock("S");
    }
    else if (randNum <= 9) {
      nextBlock = createBlock("Z");
    }
  }
  else {
    string nextBlockType;
    sequenceFileStream >> nextBlockType;
    
    nextBlock = createBlock(nextBlockType);
  }
  
  return nextBlock;
}

// Level 3 does not have an external constructive force
Tetromino *Level3::createSingleBlock() {
  return nullptr;
}

// Deactivate/Activate randomness in Tetromino generation
void Level3::norandom(string fileName) {
  setRandomness(false);
  sequenceFileStream.open(fileName);
}

void Level3::random() {
  setRandomness(true);
}

void Level3::resetBlocksPlaced() {
  // Level 3 does not keep track of the blocks placed
}
