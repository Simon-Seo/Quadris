#ifndef SQUARE_H
#define SQUARE_H
#include "tetromino.h"
#include "../Other/subject.h"
#include "../Other/state.h"
#include "../Other/info.h"

class Square final: public Subject {
  Tetromino *parentTetromino;
  int row, col;
  
public:
  Square(Tetromino *parent, int row, int col, State state = State{SquareType::Empty});
  ~Square();
  void changeSquare(SquareType squareType);
  void setParent(Tetromino *parent);
  void clearSquare();
  int getRow() const;
  int getCol() const;
  void setRow(int r);
  void setCol(int c);
  Tetromino *getParent() const;
  int getScore() const override;
  Info getInfo() const override;
};

#endif
