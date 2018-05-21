#ifndef LEVEL0_H
#define LEVEL0_H
#include <string>
#include "level.h"

class Level0 final: public Level {
  std::string scriptFile;
  
public:
  Level0(std::string scriptFile);
  Tetromino *createNextBlock() override;
  Tetromino *createSingleBlock() override;
  void norandom(std::string fileName) override;
  void random() override;
  void resetBlocksPlaced() override;
};

#endif
