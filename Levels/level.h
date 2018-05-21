#ifndef LEVEL_H
#define LEVEL_H
#include <fstream>
#include <string>
#include "../Other/subject.h"
#include "../Other/info.h"

class Tetromino;

class Level: public Subject {
  bool isRandom = true;
  const int theLevel;
  const int denominator;
  
protected:
  std::ifstream sequenceFileStream;
  
public:
  Level(int theLevel, int denominator, std::string fileName = "sequence.txt");
  virtual ~Level() = default;
  virtual Tetromino *createNextBlock() = 0;
  virtual Tetromino *createSingleBlock() = 0;
  Tetromino *createBlock(std::string blockType);
  virtual void norandom(std::string fileName) = 0;
  virtual void random() = 0;
  virtual void resetBlocksPlaced() = 0;
  void setRandomness(bool randomness);
  bool getRandomness() const;
  int getLevel() const;
  int getDenominator() const;
  int getScore() const override;
  Info getInfo() const override;
};

#endif
