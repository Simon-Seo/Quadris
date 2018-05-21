#include <algorithm>
#include <iostream>
#include <string>
#include "quadrisboard.h"
#include "scoreboard.h"
#include "../Display/graphicsdisplay.h"
#include "../Display/textdisplay.h"
#include "../Tetrominoes/tetromino.h"
#include "../Tetrominoes/hintblock.h"
#include "../Tetrominoes/square.h"
#include "../Levels/level.h"
#include "../Levels/level0.h"
#include "../Levels/level1.h"
#include "../Levels/level2.h"
#include "../Levels/level3.h"
#include "../Levels/level4.h"
#include "../Other/state.h"
#include "../Other/info.h"
using namespace std;

// Constructor
QuadrisBoard::QuadrisBoard(bool textOnly, int seed, string scriptFile, int startingLevel, Scoreboard *scoreboard): textOnly{textOnly}, seed{seed}, scriptFile{scriptFile}, currentLevel{startingLevel}, scoreboard{scoreboard} {
  init();
}

// Destructor
QuadrisBoard::~QuadrisBoard() {
  theBoard.clear();

  for (auto &tetromino: activeBlocks) {
    delete tetromino;
  }
  activeBlocks.clear();

  delete graphicsDisplay;
  delete textDisplay;
  delete currentBlock;
  delete nextBlock;
  delete level;
  destroyHint();
}

// Initializes the QuadrisBoard; called upon construction and when restart() is called
void QuadrisBoard::init() {
  level = nullptr;
  setLevel(currentLevel);
  currentBlock = level->createNextBlock();
  nextBlock = level->createNextBlock();
  hintBlock = nullptr;
  level->resetBlocksPlaced();
  gameOver = false;

  if (!textOnly) {
    graphicsDisplay = new GraphicsDisplay{numRows, numCols, nextBlock, scoreboard};
    scoreboard->attach(graphicsDisplay);
  }
  else {
    graphicsDisplay = nullptr;
  }
  textDisplay = new TextDisplay{nextBlock, scoreboard};

  // Initialize our board; which is a vector of vectors of Squares
  for (int i = 0; i < numRows; ++i) {
    vector<Square> rowOfSquares;
    for (int j = 0; j < numCols; ++j) {
      Square newSquare{nullptr, i, j};
      newSquare.attach(textDisplay);
      if (!textOnly) {
        newSquare.attach(graphicsDisplay);
      }
      rowOfSquares.emplace_back(newSquare);
    }
    theBoard.emplace_back(rowOfSquares);
  }

  placeBlock(currentBlock);
}

// Sets the level pointer to the updatedLevel
void QuadrisBoard::setLevel(int updatedLevel) {
  if (updatedLevel < 0 || updatedLevel > 4) {
    return;
  }
  else {
    delete level;
    switch (updatedLevel) {
      case 0:
        level = new Level0{scriptFile};
        break;
      case 1:
        level = new Level1{seed};
        break;
      case 2:
        level = new Level2{seed};
        break;
      case 3:
        level = new Level3{seed};
        break;
      case 4:
        level = new Level4{seed};
        break;
      default:
        break;
    }

    // Subscribe to get notifications to createSingleBlock
    level->attach(this);
    currentLevel = updatedLevel;
    scoreboard->setLevel(currentLevel);
  }
}

// This drop does not clear lines
void QuadrisBoard::drop(Tetromino *t) {
  lift(t);
  
  int dropDistance = numRows - t->getCurrentRow() - 1;
  for (Square *square: t->getSquares()) {
    int row = square->getRow();
    int col = square->getCol();
    for (int i = row; i < numRows; ++i) {
      if (theBoard.at(i).at(col).getState().type != SquareType::Empty) {
        dropDistance = (i - row - 1) < dropDistance ? (i - row - 1) : dropDistance;
        break;
      }
    }
  }

  t->drop(dropDistance);
}

// Lift; temporarily remove the given Tetromino from theBoard
void QuadrisBoard::lift(Tetromino *t) {
  for (auto &square: t->getSquares()) {
    int row = square->getRow();
    int col = square->getCol();
    theBoard.at(row).at(col).changeSquare(SquareType::Empty);
    theBoard.at(row).at(col).setParent(nullptr);
  }
}

// Place; place the given Tetromino onto theBoard
void QuadrisBoard::placeBlock(Tetromino *t) {
  for (Square *square: t->getSquares()) {
    int row = square->getRow();
    int col = square->getCol();
    SquareType squareType = square->getState().type;
    theBoard.at(row).at(col).changeSquare(squareType);
    theBoard.at(row).at(col).setParent(t);
  }
}

// Check for any full rows and call scoreboard->scoreRow(numRowsCleared)
void QuadrisBoard::checkLineClears() {
  int minRow = (numRows - 1), maxRow = 3;
  int numRowsCleared = 0;

  // Find out the range of our search for line clears
  for (auto &square: currentBlock->getSquares()) {
    int row = square->getRow();
    if (row < minRow) {
      minRow = row;
    }
    if (row > maxRow) {
      maxRow = row;
    }
  }

  // Go through each possibly-cleared row and check if the entire row is full
  for (int i = minRow; i <= maxRow; ++i) {
    int numFilledSquares = 0;
    for (auto &square: theBoard.at(i)) {
      if (square.getState().type == SquareType::Empty) {
        break;
      }
      else {
        ++numFilledSquares;
      }
    }

    // If this row is indeed full,
    if (numFilledSquares == numCols) {
      ++numRowsCleared;

      // We set all of the squares to be empty
      for (auto &square: theBoard.at(i)) {
        square.clearSquare();
        square.setParent(nullptr);
      }

      shiftLinesDown(i);
    }
  }

  /**
   * If any rows were cleared as a result of dropping the currentBlock,
   *   - Update the scoreboard
   *   - Shift all necessary lines down
   */
  if (numRowsCleared > 0) {
    scoreboard->scoreRow(numRowsCleared);
    level->resetBlocksPlaced();
  }
}

// Shift all rows above the clearedRow down
void QuadrisBoard::shiftLinesDown(int clearedRow) {
  int startRow = clearedRow - 1;
  while (!(isRowEmpty(startRow))) {
    --startRow;
  }

  for (int i = clearedRow; i > startRow; --i) {
    for (int j = 0; j < numCols; ++j) {
      Square *thisSquare = &(theBoard.at(i).at(j));
      Square *squareAbove = &(theBoard.at(i - 1).at(j));
      thisSquare->changeSquare(squareAbove->getState().type);
      thisSquare->setParent(squareAbove->getParent());
    }
  }

  // The first playable row should always be empty after a line clear
  for (auto &square: theBoard.at(3)) {
    square.changeSquare(SquareType::Empty);
    square.setParent(nullptr);
  }
}

/**
 * Try to place the transformedTetromino onto theBoard
 *   Success: make the transformedTetromino the new currentBlock
 *   Failure: place the currentBlock back where it originated from
 */
void QuadrisBoard::tryTransformation(Tetromino *transformedTetromino) {
  lift(currentBlock);
  if(checkCollision(transformedTetromino)) {
    placeBlock(currentBlock);
    delete transformedTetromino;
  }
  else {
    placeBlock(transformedTetromino);
    delete currentBlock;
    currentBlock = transformedTetromino;
    transformedTetromino = nullptr;
  }
}


/**
 * Do the following:
 *   - Assign currentBlock's address to currentBlockCopy
 *   - Assign nextBlock's address to currentBlock
 *   - Assign a new nextBlock generated by Level to nextBlock
 *   - Emplace_back the currentBlockCopy onto activeBlocks
 *   - Check if the new currentBlock can be placed
 */
void QuadrisBoard::prepareNextBlock() {
  Tetromino *currentBlockCopy = currentBlock;
  currentBlock = nextBlock;
  nextBlock = level->createNextBlock();
  textDisplay->setNextBlock(nextBlock);
  
  if (!textOnly) {
    graphicsDisplay->setNextBlock(nextBlock);
  }
  
  currentBlockCopy->attach(this);
  currentBlockCopy->attach(scoreboard);
  activeBlocks.push_back(currentBlockCopy);

  if (checkCollision(currentBlock)) {
    textDisplay->gameOver();
    if (!textOnly) {
      graphicsDisplay->gameOver();
    }
  }
  else {
    placeBlock(currentBlock);
  }
}

// Check if t collides with any of the blocks already on theBoard
bool QuadrisBoard::checkCollision(const Tetromino *t) {
  for (auto &square: t->getSquares()) {
    int row = square->getRow();
    int col = square->getCol();
    if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
      return true;
    }

    State state = theBoard.at(row).at(col).getState();
    if (state.type != SquareType::Empty) {
      return true;
    }
  }
  return false;
}

// Predicate for QuadrisBoard's notify() method
bool QuadrisBoard::isTetrominoEmpty(Tetromino *t) {
  return (t->getCount() == 0);

}

// Returns true if the row at given index is empty
bool QuadrisBoard::isRowEmpty(int row) {
  for (Square square: theBoard.at(row)) {
    if (square.getState().type != SquareType::Empty) {
      return false;
    }
  }

  return true;
}

// Transformation methods for the currentBlock
void QuadrisBoard::left() {
  Tetromino *transformedCurrentBlock = currentBlock->left();
  tryTransformation(transformedCurrentBlock);
}

void QuadrisBoard::right() {
  Tetromino *transformedCurrentBlock = currentBlock->right();
  tryTransformation(transformedCurrentBlock);
}

void QuadrisBoard::down() {
  Tetromino *transformedCurrentBlock = currentBlock->down();
  tryTransformation(transformedCurrentBlock);
}

void QuadrisBoard::clockwise() {
  Tetromino *transformedCurrentBlock = currentBlock->clockwise();
  tryTransformation(transformedCurrentBlock);
}

void QuadrisBoard::counterclockwise() {
  Tetromino *transformedCurrentBlock = currentBlock->counterclockwise();
  tryTransformation(transformedCurrentBlock);
}

// This drop clears lines, if possible
void QuadrisBoard::drop() {
  drop(currentBlock);
  placeBlock(currentBlock);
  checkLineClears();
  prepareNextBlock();
}

// Controls the current Level of the game
void QuadrisBoard::levelup() {
  setLevel(currentLevel + 1);
}

void QuadrisBoard::leveldown() {
  setLevel(currentLevel - 1);
}

// Controls the randomness of the Level
void QuadrisBoard::norandom(string fileName) {
  level->norandom(fileName);
}

void QuadrisBoard::random() {
  level->random();
}

// Replaces the currentBlock with the given blockType
void QuadrisBoard::replaceCurrent(string blockType) {
  lift(currentBlock);
  delete currentBlock;
  currentBlock = level->createBlock(blockType);
  placeBlock(currentBlock);
}

/**
 * Clears the board and restarts the game of Quadris
 *   - Reset the current score
 *   - Release theBoard, activeBlocks, graphics/textDisplay, current/nextBlock, level
 *   - Init the QuadrisBoard
 */
void QuadrisBoard::restart() {
  scoreboard->resetScore();
  scoreboard->clearObservers();
  theBoard.clear();

  for (auto &tetromino: activeBlocks) {
    delete tetromino;
  }
  activeBlocks.clear();

  delete graphicsDisplay;
  delete textDisplay;
  delete currentBlock;
  delete nextBlock;
  delete level;

  destroyHint();
  init();
}

/**
 * Hint Criteria
 *   - Most number of nonempty squares below hintBlock
 *   - Lowest
 *
 * Hint Algorithm
 *   - Every possible row position
 *   - Every unique rotation
 *   - Worst case: 44 drops
 *
 * This hint algorithm is based on the behaviour of Sprint/Line Race
 *   (40 lines as fast as possible) players who only hard drop
 */
void QuadrisBoard::hint() {
  lift(currentBlock);
  
  if (hintBlock) {
    delete hintBlock;
  }
  hintBlock = new HintBlock{currentBlock};
  int squaresBelowHint = 0;
  int hintRow = 0;
  HintBlock hintBlockLeft{hintBlock};
  HintBlock hintBlockRight{hintBlock};
  int numOrientations = hintBlockLeft.getNumOrientations();
  bool goRight = false;
  
  while (!checkCollision(&hintBlockLeft) || goRight) {
    // Make a copy before gravity, since the user can move left many
    //   times and only be affected by gravity once.
    HintBlock hintBlockGravity{goRight ? hintBlockRight : hintBlockLeft};
    hintBlockLeft.moveLeft();
    if (goRight) {
      hintBlockRight.moveRight();
      if (checkCollision(&hintBlockRight)) {
        break;
      }
    }
    else if (checkCollision(&hintBlockLeft)) {
      goRight = true;
    }
    
    if (hintBlock->isHeavy()) {
      HintBlock tempHintBlockGravity{hintBlockGravity};
      tempHintBlockGravity.moveDown();
      if (!(checkCollision(&tempHintBlockGravity))) {
        hintBlockGravity.moveDown();
      }
    }

    if (hintDrop(hintBlockGravity, squaresBelowHint, hintRow)) {
      break;
    }
    if (numOrientations > 1) {
      HintBlock hintBlockCW{hintBlockGravity};
      hintBlockCW.rotateClockwise();
      if (!checkCollision(&hintBlockCW) && hintDrop(hintBlockCW, squaresBelowHint, hintRow)) {
        break;
      }
    }
    if (numOrientations > 2) {
      HintBlock hintBlockCCW{hintBlockGravity};
      hintBlockCCW.rotateCounterclockwise();
      if (!checkCollision(&hintBlockCCW)) {
        if (hintDrop(hintBlockCCW, squaresBelowHint, hintRow)) {
          break;
        }
      }
      HintBlock hintBlock180Rotate{hintBlockGravity};
      hintBlock180Rotate.rotateClockwise();
      hintBlock180Rotate.rotateClockwise();
      if (!checkCollision(&hintBlock180Rotate)) {
        if (hintDrop(hintBlock180Rotate, squaresBelowHint, hintRow)) {
          break;
        }
      }
    }
  }
  
  placeBlock(currentBlock);
  placeBlock(hintBlock);
}

// Drops the hint and replaces hintBlock if it's a better position. Also
//    returns true if all possible blocks are touching the bottom of the board.
bool QuadrisBoard::hintDrop(const HintBlock &hint, int &squaresBelow, int &row) {
  HintBlock hintCopy{hint};
  drop(&hintCopy);

  int newSquaresBelow = 0;
  for (Square *square: hintCopy.getSquares()) {
    if (square->getRow() + 1 == numRows) {
      ++newSquaresBelow;
    }
    else {
      SquareType squareType = theBoard.at(square->getRow() + 1).at(square->getCol()).getState().type;
      if (squareType != SquareType::Empty) {
        ++newSquaresBelow;
      }
    }
  }

  if (squaresBelow < newSquaresBelow || (squaresBelow == newSquaresBelow && row < hintCopy.getCurrentRow())) {
    delete hintBlock;
    hintBlock = new HintBlock{hintCopy};
    squaresBelow = newSquaresBelow;
    row = hintCopy.getCurrentRow();
  }
  if (newSquaresBelow == max(hint.getWidth(), hint.getHeight()) && row == numRows - 1) {
    return true;
  }
  return false;
}

// Destroys hintBlock, if it exists
void QuadrisBoard::destroyHint() {
  if (hintBlock) {
    lift(hintBlock);
    delete hintBlock;
    hintBlock = nullptr;
  }
}
// Move the currentBlock down if it's heavy; called only by main.cc
void QuadrisBoard::gravity() {
  if (currentBlock->isHeavy()) {
    down();
  }
}

// Returns true if the game is over
bool QuadrisBoard::isGameOver() {
  return gameOver;
}


/**
 * Tetrominoes notify the QuadrisBoard, and then QuadrisBoard removes any empty Tetrominoes
 * Level also notifies the QuadrisBoard only if it is ready to generate a SingleBlock
 */
void QuadrisBoard::notify(Subject &whoNotified) {
  if (whoNotified.getInfo().subject == SubjectType::Tetromino) {
    // If the Subject is a Tetromino, check to see if any active Tetromino is empty
    activeBlocks.erase(remove_if(activeBlocks.begin(),
                                 activeBlocks.end(),
                                 [](Tetromino *t){return (t->getCount() == 0);}),
                       activeBlocks.end() );
  }
  else if (whoNotified.getInfo().subject == SubjectType::Level) {
    // If the Subject is a Level, ask for a SingleBlock and place it if possible
    Tetromino *singleBlock = level->createSingleBlock();
    if (checkCollision(singleBlock)) {
      textDisplay->gameOver();
    }
    else {
      drop(singleBlock);
      placeBlock(singleBlock);
      activeBlocks.emplace_back(singleBlock);
    }
  }
}

// Let textDisplay do all the text formatting
ostream &operator<<(ostream &out, const QuadrisBoard &qb) {
  out << *(qb.textDisplay);
  return out;
}
