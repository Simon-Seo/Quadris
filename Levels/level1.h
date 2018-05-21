#ifndef LEVEL1_H
#define LEVEL1_H
#include <string>
#include "level.h"

class Level1 final: public Level {
public:
  Level1(int seed);
  Tetromino *createNextBlock() override;
  Tetromino *createSingleBlock() override;
  void norandom(std::string fileName) override;
  void random() override;
  void resetBlocksPlaced() override;
};

#endif
