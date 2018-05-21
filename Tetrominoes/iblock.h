#ifndef IBLOCK_H
#define IBLOCK_H
#include "tetromino.h"

class IBlock final: public Tetromino {
  IBlock(const IBlock *t);
public:
  IBlock(int level);
  IBlock *left() const override;
  IBlock *right() const override;
  IBlock *down() const override;
  IBlock *clockwise() const override;
  IBlock *counterclockwise() const override;
};

#endif
