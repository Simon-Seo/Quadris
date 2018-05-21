#include <string>
#include "level4.h"
#include "../Other/state.h"
#include "../Tetrominoes/iblock.h"
#include "../Tetrominoes/jblock.h"
#include "../Tetrominoes/lblock.h"
#include "../Tetrominoes/oblock.h"
#include "../Tetrominoes/sblock.h"
#include "../Tetrominoes/tblock.h"
#include "../Tetrominoes/zblock.h"
#include "../Tetrominoes/tetromino.h"
#include "../Tetrominoes/singleblock.h"
using namespace std;

Level4::Level4(int seed): Level{4, 9} {
  srand(seed);
}

// Level4 creates S and Z blocks with 2/9 probability and every other block with 1/9 probability
Tetromino *Level4::createNextBlock() {
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
  
  // If we have placed at least 5 blocks (in multiples of 5), notify our Observer
  ++blocksPlaced;
  if ((blocksPlaced > 0) && (blocksPlaced % singleBlockInterval == 0)) {
    notifyObservers();
  }
  return nextBlock;
}

// Every 5th block generated without clearing at least one row comes with a SingleBlock
// This method is called in QuadrisBoard's notify() method
Tetromino *Level4::createSingleBlock() {
  return createBlock("Single");
}

// Deactivate/Activate randomness in Tetromino generation
void Level4::norandom(string fileName) {
  setRandomness(false);
  sequenceFileStream.open(fileName);
}

void Level4::random() {
  setRandomness(true);
}

// This method is called when a line is cleared in QuadrisBoard
void Level4::resetBlocksPlaced() {
  blocksPlaced = 0;
}
