#include <iostream>
#include <string>
#include "level.h"
#include "../Other/info.h"
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

Level::Level(int theLevel, int denominator, string fileName): theLevel{theLevel}, denominator{denominator}, sequenceFileStream{fileName} {
  
}

// Creates a specific Tetromino of the given blockType
Tetromino *Level::createBlock(string blockType) {  
  Tetromino *block = nullptr;
  
  if (blockType == "I") {
    block = new IBlock{theLevel};
  }
  else if (blockType == "J") {
    block = new JBlock{theLevel};
  }
  else if (blockType == "L") {
    block = new LBlock{theLevel};
  }
  else if (blockType == "O") {
    block = new OBlock{theLevel};
  }
  else if (blockType == "T") {
    block = new TBlock{theLevel};
  }
  else if (blockType == "S") {
    block = new SBlock{theLevel};
  }
  else if (blockType == "Z") {
    block = new ZBlock{theLevel};
  }
  else if (blockType == "Single") {
    block = new SingleBlock{theLevel};
  }
  
  return block;
}

void Level::setRandomness(bool randomness) {
  isRandom = randomness;
}

bool Level::getRandomness() const {
  return isRandom;
}

int Level::getLevel() const {
  return theLevel;
}

int Level::getDenominator() const {
  return denominator;
}

int Level::getScore() const {
  return 0;
}

Info Level::getInfo() const {
  return Info{0, 0, SubjectType::Level};
}


