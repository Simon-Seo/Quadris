#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <vector>
#include <iostream>
#include "../Other/observer.h"
#include "../Other/state.h"

class Scoreboard;

class Tetromino;

class TextDisplay: public Observer {
  const int rows;                             // 18 rows in the board
  const int cols;                             // 11 cols in the board
  bool isGameOver;                            // Set to True when the game is over
  std::vector<std::vector<char>> displayGrid; // The text representation of the Quadris board
  Tetromino *nextBlock;                       // TextDisplay has a Tetromino; shared by QuadrisBoard
  Scoreboard *scoreboard;                     // TextDisplay has a Scoreboard; shared by QuadrisBoard

  char enumToChar(SquareType type) const;     // Converts the given SquareType to the corresponding char

public:
  TextDisplay(Tetromino *nextBlock, Scoreboard *scoreboard); // Constructor
  void setNextBlock(Tetromino *nextBlock);                   // Sets nextBlock to given Tetromino
  void gameOver();                                           // Called when game ends (i.e. player dies)
  void notify(Subject &whoNotified) override;                // Squares call this when their State changes
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
