#ifndef QUADRIS_BOARD_H
#define QUADRIS_BOARD_H
#include <iostream>
#include <string>
#include <vector>
#include "../Other/observer.h"
#include "../Tetrominoes/hintblock.h"

class Scoreboard;

class GraphicsDisplay;

class TextDisplay;

class Tetromino;

class Square;

class Level;

// The dimensions for our Quadris board
const int numRows = 18;
const int numCols = 11;

class QuadrisBoard final: public Observer {

  /**
   * NOTE:
   *   - Subjects:  Tetromino, Square, Level
   *   - Observers: QuadrisBoard, Scoreboard, GraphicsDisplay, TextDisplay
   *
   *   - Tetromino's subscribers: QuadrisBoard; to erase the Tetromino, Scoreboard; to update score
   *   - Square's subscribers:    TextDisplay and GraphicsDisplay; for their corresponding display purposes
   *   - Level's subscribers:     QuadrisBoard; to ask for singleBlock if necessary
   */

  bool textOnly;          // If set to true, only initialize textDisplay
  int seed;               // Seed for Levels
  std::string scriptFile; // File to be used for Level0
  int currentLevel;       // The current level
  bool gameOver;          // If set to true, game is over

  std::vector<std::vector<Square>> theBoard; // The implementation of the Quadris board
  std::vector<Tetromino *> activeBlocks;     // Vector of Tetrominoes placed on theBoard
  Scoreboard *scoreboard;                    // Scoreboard is not owned by QuadrisBoard
  GraphicsDisplay *graphicsDisplay;          // Pointer to the graphicsDisplay
  TextDisplay *textDisplay;                  // Pointer to the textDisplay
  Tetromino *currentBlock;                   // Stores the currently controlled Tetromino
  Tetromino *nextBlock;                      // Stores the upcoming Tetromino, shared by textDisplay
  HintBlock *hintBlock;                      // Stores the HintBlock created by the hint command
  Level *level;                              // Stores the pointer to the Level
  
  void init();                                             // Initializes the QuadrisBoard
  void setLevel(int updatedLevel);                         // Updates the level pointer to updatedLevel
  void drop(Tetromino *t);                                 // Hard drops t onto theBoard
  void lift(Tetromino *t);                                 // Temporarily removes t from theBoard
  void placeBlock(Tetromino *t);                           // Places t onto theBoard
  void checkLineClears();                                  // Checks if any lines are full
  void shiftLinesDown(int bottomRow);                      // Shifts all lines down starting from bottomRow
  void tryTransformation(Tetromino *transformedTetromino); // Tries to place transformedT onto theBoard
  void prepareNextBlock();                                 // Called after drop() is executed
  bool checkCollision(const Tetromino *t);                 // Checks if t collides with theBoard
  bool isTetrominoEmpty(Tetromino *t);                     // Checks if t is no longer on the board
  bool isRowEmpty(int row);
  bool hintDrop(const HintBlock &hint, int &squaresBelow, int &row);
  
public:
  QuadrisBoard(bool textOnly, int seed, std::string scriptFile, int startingLevel, Scoreboard *scoreboard);
  ~QuadrisBoard();
  void left();                                // Moves the currentBlock one column left
  void right();                               // Moves the currentBlock one column right
  void down();                                // Moves the currentBlock one row down
  void clockwise();                           // Rotates the currentBlock clockwise once
  void counterclockwise();                    // Rotates the currentBlock counterclockwise once
  void drop();                                // Hard drops the currentBlock onto theBoard
  void levelup();                             // Increases the game's level if possible
  void leveldown();                           // Decreases the game's level if possible
  void norandom(std::string fileName);        // Sets the current level to take inputs from fileName
  void random();                              // Restores randomness in the current level
  void replaceCurrent(std::string blockType); // Replaces currentBlock with given blockType
  void restart();                             // Restarts the game of Quadris
  void hint();                                // Displays a hint for the currentBlock's placement
  void destroyHint();                         // Destroys hintBlock, if it exists
  void gravity();                             // Moves the currentBlock down if it isHeavy
  bool isGameOver();                          // Returns true if game is over
  void notify(Subject &whoNotified) override; // Notified by either Tetromino or Level
  friend std::ostream &operator<<(std::ostream &out, const QuadrisBoard &qb);
};

#endif
