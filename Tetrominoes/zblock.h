#ifndef ZBLOCK_H
#define ZBLOCK_H
#include "tetromino.h"

class ZBlock final: public Tetromino {
  ZBlock(const ZBlock *t);
public:
  ZBlock(int level);
  ZBlock *left() const override;
  ZBlock *right() const override;
  ZBlock *down() const override;
  ZBlock *clockwise() const override;
  ZBlock *counterclockwise() const override;
};

#endif
