#ifndef LEVEL2_H
#define LEVEL2_H
#include <string>
#include "level.h"

class Level2 final: public Level {
public:
  Level2(int seed);
  Tetromino *createNextBlock() override;
  Tetromino *createSingleBlock() override;
  void norandom(std::string fileName) override;
  void random() override;
  void resetBlocksPlaced() override;
};

#endif
