#include "square.h"
using namespace std;

Square::Square(Tetromino *parent, int row, int col, State state): parentTetromino{parent}, row{row}, col{col} {
  setState(state);
}

Square::~Square() {

}

// Changes this square to the given SquareType
void Square::changeSquare(SquareType squareType) {
  State newState{squareType};
  setState(newState);
  notifyObservers();
}

void Square::setParent(Tetromino *parent) {
  parentTetromino = parent;
}

void Square::clearSquare() {
  if (parentTetromino) {
    parentTetromino->decrementCount();
  }
  setState(State{SquareType::Empty});
}

int Square::getRow() const {
  return row;
}

int Square::getCol() const {
  return col;
}

void Square::setRow(int r) {
  row = r;
}

void Square::setCol(int c) {
  col = c;
}

Tetromino *Square::getParent() const {
  return parentTetromino;
}

int Square::getScore() const {
  return 0;
}

Info Square::getInfo() const {
  return Info{row, col, SubjectType::Square};
}
