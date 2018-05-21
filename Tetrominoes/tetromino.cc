#include <algorithm>    // std::max
#include <iostream>
#include <utility>      // std::swap
#include "tetromino.h"
#include "square.h"
using namespace std;

Tetromino::Tetromino(int level, int width, int height, int numOrientations, int count, int currentRow, int currentCol): level{level}, width{width}, height{height}, numOrientations{numOrientations}, count{count}, currentRow{currentRow}, currentCol{currentCol} {
  
}

Tetromino::~Tetromino() {
  for (Square *square: squares) {
    delete square;
  }
  squares.clear();
}

void Tetromino::alignBottomLeft() {
  if (width > height) {
    for (Square *square: squares) {
      if (square->getRow() == currentRow) {
        return;
      }
    }
    d();          // To avoid making a separate wrapper function for d(),
    --currentRow; //   we're manually adjusting currentRow back here.
  }
  else {
    for (Square *square: squares) {
      if (square->getCol() == currentCol) {
        return;
      }
    }
    l();          // To avoid making a separate wrapper function for l(),
    ++currentCol; //   we're manually adjusting currentCol back here.
  }
}

void Tetromino::l() {
  for (Square *square: squares) {
    square->setCol(square->getCol() - 1);
  }
  --currentCol;
}

void Tetromino::r() {
  for (Square *square: squares) {
    square->setCol(square->getCol() + 1);
  }
  ++currentCol;
}

void Tetromino::d() {
  for (Square *square: squares) {
    square->setRow(square->getRow() + 1);
  }
  ++currentRow;
}

void Tetromino::cw() {
  for (Square *square: squares) {
    int row = square->getRow();
    int col = square->getCol();
    square->setRow(col + currentRow - max(height, width) + 1 - currentCol);
    square->setCol(currentRow - row + currentCol);
  }
  swap(width, height);
  alignBottomLeft();
}

void Tetromino::ccw() {
  for (Square *square: squares) {
    int row = square->getRow();
    int col = square->getCol();
    square->setRow(currentRow - col + currentCol);
    square->setCol(row - currentRow + currentCol + max(height, width) - 1);
  }
  swap(width, height);
  alignBottomLeft();
}

void Tetromino::drop(int dropDistance) {
  for (Square *square: squares) {
    square->setRow(square->getRow() + dropDistance);
  }
  currentRow += dropDistance;
}

int Tetromino::getLevel() const {
  return level;
}

int Tetromino::getWidth() const {
  return width;
}

int Tetromino::getHeight() const {
  return height;
}

int Tetromino::getCount() const {
  return count;
}

int Tetromino::getCurrentRow() const {
  return currentRow;
}

int Tetromino::getCurrentCol() const {
  return currentCol;
}

int Tetromino::getNumOrientations() const {
  return numOrientations;
}

bool Tetromino::isHeavy() const {
  return (level >= 3);
}

void Tetromino::decrementCount() {
  --count;
  if (count == 0) {
    notifyObservers();
  }
}

int Tetromino::getScore() const {
  return (level + 1) * (level + 1);
}

Info Tetromino::getInfo() const {
  return Info{0, 0, SubjectType::Tetromino};
}

const vector<Square *> &Tetromino::getSquares() const {
  return squares;
}
