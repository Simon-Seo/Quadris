#ifndef OBLOCK_H
#define OBLOCK_H
#include "tetromino.h"

class OBlock final: public Tetromino {
  OBlock(const OBlock *t);
public:
  OBlock(int level);
  OBlock *left() const override;
  OBlock *right() const override;
  OBlock *down() const override;
  OBlock *clockwise() const override;
  OBlock *counterclockwise() const override;
};

#endif
