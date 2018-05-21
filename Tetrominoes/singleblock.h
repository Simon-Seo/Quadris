#ifndef SINGLE_BLOCK_H
#define SINGLE_BLOCK_H
#include "tetromino.h"

class SingleBlock final: public Tetromino {
public:
  SingleBlock(int level);
  SingleBlock *left() const override;
  SingleBlock *right() const override;
  SingleBlock *down() const override;
  SingleBlock *clockwise() const override;
  SingleBlock *counterclockwise() const override;
};

#endif
