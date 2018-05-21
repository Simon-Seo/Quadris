#include <vector>
#include <iostream>
#include "textdisplay.h"
#include "../Board/scoreboard.h"
#include "../Other/observer.h"
#include "../Other/info.h"
#include "../Other/state.h"
#include "../Tetrominoes/square.h"
using namespace std;

// Converts the given SquareType to its char equivalent for display purposes
char TextDisplay::enumToChar(SquareType type) const {
  char displayChar = ' ';
  if (type == SquareType::I) {
    displayChar = 'I';
  }
  else if (type == SquareType::J) {
    displayChar = 'J';
  }
  else if (type == SquareType::L) {
    displayChar = 'L';
  }
  else if (type == SquareType::O) {
    displayChar = 'O';
  }
  else if (type == SquareType::S) {
    displayChar = 'S';
  }
  else if (type == SquareType::Z) {
    displayChar = 'Z';
  }
  else if (type == SquareType::T) {
    displayChar = 'T';
  }
  else if (type == SquareType::Empty) {
    displayChar = ' ';
  }
  else if (type == SquareType::Hint) {
    displayChar = '?';
  }
  else if (type == SquareType::Single) {
    displayChar = '*';
  }

  return displayChar;
}

// Constructor
TextDisplay::TextDisplay(Tetromino *nextBlock, Scoreboard *scoreboard): rows{18}, cols{11}, isGameOver{false}, displayGrid(18, vector<char>(11, ' ')), nextBlock{nextBlock}, scoreboard{scoreboard} {

}

void TextDisplay::setNextBlock(Tetromino *nextBlock) {
  this->nextBlock = nextBlock;
}

// When the game ends, QuadrisBoard calls this and we display a final message
void TextDisplay::gameOver() {
  isGameOver = true;
}

// Squares call this when their States change
void TextDisplay::notify(Subject &whoNotified) {
  State theState = whoNotified.getState();
  Info theInfo = whoNotified.getInfo();
  if (theInfo.subject == SubjectType::Square) {
    displayGrid.at(theInfo.row).at(theInfo.col) = enumToChar(theState.type);
  }
}

// Print out the scoreboard, the Quadris board, and the "Next" section
ostream &operator<<(ostream &out, const TextDisplay &td) {
  const int nextBlockRows = 2;
  const int nextBlockCols = 4;
  const vector<Square *> nextBlockSquares = td.nextBlock->getSquares();
  vector<vector<char>> nextBlockGrid(nextBlockRows, vector<char>(nextBlockCols, ' '));

  // The nextBlock square coordinates start from row 2 by design.
  // Each Tetromino consists of 4 squares; thus, the vector of squares has 4 elements
  // We subtract 2 from the row value to account for this offset.
  for (int i = 0; i < 4; ++i) {
    const Square *square = nextBlockSquares.at(i);
    State theState = square->getState();
    nextBlockGrid.at(square->getRow() - 2).at(square->getCol()) = td.enumToChar(theState.type);
  }

  if (td.isGameOver) {
    // Print game over message
    out << "Game Over!" << endl;
    out << "Your score is: " << td.scoreboard->getScore() << endl;
    out << "Your hi score is: " << td.scoreboard->getHiScore() << endl;
    out << "Please type \"restart\" to restart the game." << endl;
  }
  else {
    // Output the scoreboard
    out << *(td.scoreboard);
    for (int i = 0; i < td.cols; ++i) {
      out << '-';
    }
    out << endl;
    
    // Output the text representation of the Quadris board
    for (int i = 0; i < td.rows; ++i) {
      for (int j = 0; j < td.cols; ++j) {
        out << td.displayGrid.at(i).at(j);
      }
      out << endl;
    }
    for (int i = 0; i < td.cols; ++i) {
      out << '-';
    }
    
    // Output the nextBlock section of the display
    out << endl << "Next:" << endl;
    for (int i = 0; i < nextBlockRows; ++i) {
      for (int j = 0; j < nextBlockCols; ++j) {
        out << nextBlockGrid.at(i).at(j);
      }
      out << endl;
    }
  }

  return out;
}
