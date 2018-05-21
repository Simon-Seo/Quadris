#ifndef HINT_BLOCK_H
#define HINT_BLOCK_H
#include "tetromino.h"

class QuadrisBoard;

class HintBlock final: public Tetromino {
  
  // These methods are for QuadrisBoard::hint() purposes
  void moveLeft();
  void moveRight();
  void moveDown();
  void rotateClockwise();
  void rotateCounterclockwise();
  
public:
  HintBlock(const HintBlock &other);
  HintBlock(const Tetromino *t);
  HintBlock *left() const override;
  HintBlock *right() const override;
  HintBlock *down() const override;
  HintBlock *clockwise() const override;
  HintBlock *counterclockwise() const override;
  friend QuadrisBoard;
};

#endif
