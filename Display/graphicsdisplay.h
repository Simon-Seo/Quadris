#ifndef GRAPHICS_DISPLAY_H
#define GRAPHICS_DISPLAY_H
#include <iostream>
#include <vector>
#include "window.h"
#include "../Other/state.h"
#include "../Other/observer.h"

class Tetromino;

class Scoreboard;

const int textColour = Xwindow::Black;
const int backgroundColour = Xwindow::White;

class GraphicsDisplay: public Observer {
  const int rows, cols, width, height, scoreboardHeight, padding, squareSize;
  Tetromino *nextBlock;
  Scoreboard *scoreboard;
  Xwindow xw;
  
  void init();
  void colourSquare(int x, int y, SquareType type);
  void eraseScoreboard();
  void drawScoreboard();
  void drawNextBlocks();
  
public:
  GraphicsDisplay(const int rows, const int cols, Tetromino *nextBlock, Scoreboard *scoreboard, const int width = 350, const int height = 800);
  void setNextBlock(Tetromino *nextBlock);    // Sets nextBlock to given Tetromino
  void gameOver();                            // Called when game ends (i.e. player dies)
  int getCols();
  void notify(Subject &whoNotified) override;
};
#endif
