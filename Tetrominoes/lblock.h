#ifndef LBLOCK_H
#define LBLOCK_H
#include "tetromino.h"

class LBlock final: public Tetromino {
  LBlock(const LBlock *t);
public:
  LBlock(int level);
  LBlock *left() const override;
  LBlock *right() const override;
  LBlock *down() const override;
  LBlock *clockwise() const override;
  LBlock *counterclockwise() const override;
};

#endif
