#ifndef LEVEL3_H
#define LEVEL3_H
#include <string>
#include "level.h"

class Level3 final: public Level {
public:
  Level3(int seed);
  Tetromino *createNextBlock() override;
  Tetromino *createSingleBlock() override;
  void norandom(std::string fileName) override;
  void random() override;
  void resetBlocksPlaced() override;
};

#endif
