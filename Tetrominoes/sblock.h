#ifndef SBLOCK_H
#define SBLOCK_H
#include "tetromino.h"

class SBlock final: public Tetromino {
  SBlock(const SBlock *t);
public:
  SBlock(int level);
  SBlock *left() const override;
  SBlock *right() const override;
  SBlock *down() const override;
  SBlock *clockwise() const override;
  SBlock *counterclockwise() const override;
};

#endif
