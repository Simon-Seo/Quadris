#ifndef TBLOCK_H
#define TBLOCK_H
#include "tetromino.h"

class TBlock final: public Tetromino {
  TBlock(const TBlock *t);
public:
  TBlock(int level);
  TBlock *left() const override;
  TBlock *right() const override;
  TBlock *down() const override;
  TBlock *clockwise() const override;
  TBlock *counterclockwise() const override;
};

#endif
