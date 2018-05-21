#ifndef JBLOCK_H
#define JBLOCK_H
#include "tetromino.h"

class JBlock final: public Tetromino {
  JBlock(const JBlock *t);
public:
  JBlock(int level);
  JBlock *left() const override;
  JBlock *right() const override;
  JBlock *down() const override;
  JBlock *clockwise() const override;
  JBlock *counterclockwise() const override;
};

#endif
