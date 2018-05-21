#ifndef TETROMINO_H
#define TETROMINO_H
#include <vector>
#include "../Other/subject.h"
#include "../Other/state.h"
#include "../Other/info.h"

class Square;

class Tetromino: public Subject {
  // These fields are common for all Blocks except SingleBlock,
  //   currentRow/Col are the bottom left co-ordinates of a Block
  int level, width, height, numOrientations, count = 4, currentRow = 3, currentCol = 0;

protected:
  std::vector<Square *> squares;
  void alignBottomLeft();
  void l();
  void r();
  void d();
  void cw();
  void ccw();
  
public:
  Tetromino(int level, int width, int height, int numOrientations, int count = 4, int currentRow = 3, int currentCol = 0);
  virtual ~Tetromino();
  virtual Tetromino *left() const = 0;
  virtual Tetromino *right() const = 0;
  virtual Tetromino *down() const = 0;
  virtual Tetromino *clockwise() const = 0;
  virtual Tetromino *counterclockwise() const = 0;
  void drop(int dropDistance);
  int getLevel() const;
  int getWidth() const;
  int getHeight() const;
  int getCount() const;
  int getCurrentRow() const;
  int getCurrentCol() const;
  int getNumOrientations() const;
  bool isHeavy() const;
  void decrementCount();
  int getScore() const override;
  Info getInfo() const override;
  const std::vector<Square *> &getSquares() const;
};

#endif
