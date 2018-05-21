#include <iostream>
#include "window.h"
#include "graphicsdisplay.h"
#include "../Other/info.h"
#include "../Other/state.h"
#include "../Other/subject.h"
#include "../Board/scoreboard.h"
#include "../Tetrominoes/square.h"
#include "../Tetrominoes/tetromino.h"
using namespace std;

const int leftIndent = 10;
const int topPadding = 22;
const int lineSpacing = 30;
const int numberIndent = 200;

GraphicsDisplay::GraphicsDisplay(const int rows, const int cols, Tetromino *nextBlock, Scoreboard *scoreboard, const int width, const int height): rows{rows}, cols{cols}, width{width}, height{height}, scoreboardHeight{120}, padding{10}, squareSize{width / cols}, nextBlock{nextBlock}, scoreboard{scoreboard} {
  init();
}

void GraphicsDisplay::init() {
  xw.fillRectangle(0, 0, width, height, backgroundColour);
}

void GraphicsDisplay::colourSquare(int x, int y, SquareType type) {
  switch(type) {
    case SquareType::I:
      xw.fillRectangle(x, y, squareSize, squareSize, Xwindow::Cyan);
      break;
    case SquareType::J:
      xw.fillRectangle(x, y, squareSize, squareSize, Xwindow::Blue);
      break;
    case SquareType::L:
      xw.fillRectangle(x, y, squareSize, squareSize, Xwindow::Orange);
      break;
    case SquareType::O:
      xw.fillRectangle(x, y, squareSize, squareSize, Xwindow::Yellow);
      break;
    case SquareType::S:
      xw.fillRectangle(x, y, squareSize, squareSize, Xwindow::Green);
      break;
    case SquareType::Z:
      xw.fillRectangle(x, y, squareSize, squareSize, Xwindow::Red);
      break;
    case SquareType::T:
      xw.fillRectangle(x, y, squareSize, squareSize, Xwindow::Magenta);
      break;
    case SquareType::Hint:
      xw.fillRectangle(x, y, squareSize, squareSize, textColour);
      break;
    case SquareType::Single:
      xw.fillRectangle(x, y, squareSize, squareSize, Xwindow::Brown);
      break;
    default:
      xw.fillRectangle(x, y, squareSize, squareSize, backgroundColour);
  }
}

void GraphicsDisplay::eraseScoreboard() {
  xw.fillRectangle(0, 0, width, scoreboardHeight, backgroundColour);
}

void GraphicsDisplay::drawScoreboard() {
  xw.drawBigString(leftIndent, topPadding, "Level: ", textColour);
  xw.drawBigString(numberIndent, topPadding, to_string(scoreboard->getCurrentLevel()), textColour);
  xw.drawBigString(leftIndent, topPadding + lineSpacing, "Score: ", textColour);
  xw.drawBigString(numberIndent, topPadding + lineSpacing, to_string(scoreboard->getScore()), textColour);
  xw.drawBigString(leftIndent, topPadding + (lineSpacing * 2), "Hi Score: ", textColour);
  xw.drawBigString(numberIndent, topPadding + (lineSpacing * 2), to_string(scoreboard->getHiScore()), textColour);
}

void GraphicsDisplay::drawNextBlocks() {
  const int nextBlockRows = 2;
  const int nextBlockCols = 4;
  xw.drawBigString( 5, scoreboardHeight + padding + ((rows + 1) * squareSize), "Next:", textColour);
  vector<Square *> nextBlockSquares = nextBlock->getSquares();
  vector<vector<SquareType>> nextBlockGrid(2, vector<SquareType>(4, SquareType::Empty));
  for (int i = 0; i < 4; ++i) {
    Square *square = nextBlockSquares.at(i);
    State theState = square->getState();
    nextBlockGrid.at(square->getRow() - 2).at(square->getCol()) = theState.type;
  }
  for (int i = 0; i < nextBlockRows; ++i) {
    for (int j = 0; j < nextBlockCols; ++j) {
      colourSquare(j * squareSize, (i * squareSize) + scoreboardHeight + padding + ((rows + 1) * squareSize) + padding, nextBlockGrid.at(i).at(j));
    }
  }

  // (j * squareSize) + scoreboardHeight + padding + (rows * squareSize) + padding
}

void GraphicsDisplay::setNextBlock(Tetromino *nextBlock) {
  this->nextBlock = nextBlock;
}

// When the game ends, QuadrisBoard calls this and we display a final message
void GraphicsDisplay::gameOver() {
  init();                                 // Clear the screen
  xw.drawVeryBigString(leftIndent, height / 2, "GAME OVER", textColour);
  xw.drawVeryBigString(leftIndent, (height / 2) + lineSpacing, "Your score is: ", textColour);
  xw.drawVeryBigString(numberIndent + 50, (height / 2) + lineSpacing, to_string(scoreboard->getScore()), textColour);
  xw.drawVeryBigString(leftIndent, (height / 2) + (lineSpacing * 2), "Your hi Score is: ", textColour);
  xw.drawVeryBigString(numberIndent + 50, (height / 2) + (lineSpacing * 2), to_string(scoreboard->getHiScore()), textColour);
}

int GraphicsDisplay::getCols() {
  return cols;
}

void GraphicsDisplay::notify(Subject &whoNotified) {
  State theState = whoNotified.getState();
  Info theInfo = whoNotified.getInfo();

  if (theInfo.subject == SubjectType::Square) {
    int row = theInfo.row;
    int col = theInfo.col;

    drawScoreboard();

    colourSquare(col * squareSize, row * squareSize + scoreboardHeight, theState.type);
    drawNextBlocks();
  }
  else if (theInfo.subject == SubjectType::Scoreboard) {
    eraseScoreboard();
    drawScoreboard();
  }
}
