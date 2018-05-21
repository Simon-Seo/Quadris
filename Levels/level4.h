#ifndef LEVEL4_H
#define LEVEL4_H
#include <string>
#include "level.h"

const int singleBlockInterval = 5;

class Level4 final: public Level {
  int blocksPlaced;
  
public:
  Level4(int seed);
  Tetromino *createNextBlock() override;
  Tetromino *createSingleBlock() override;
  void norandom(std::string fileName) override;
  void random() override;
  void resetBlocksPlaced() override;
};

#endif
