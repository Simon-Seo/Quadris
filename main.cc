#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Board/quadrisboard.h"
#include "Board/scoreboard.h"
using namespace std;

const int maxLevel = 4;
const int minLevel = 0;

// TODO: implement sequence

// Compare each string in v with the given prefix to see if any string contains the prefix
vector<string> filter(const vector<string> &v, string prefix) {
  const size_t prefixLength = prefix.length();
  vector<string> filteredVector;

  for (auto &s: v) {
    if (prefix == s.substr(0, prefixLength)) {
      filteredVector.emplace_back(s);
    }
  }

  return filteredVector;
}

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);

  bool textOnly = false;              // If set to true, only launch textDisplay
  int seed;                           // The random number seed for Levels
  string scriptfile = "sequence.txt"; // The file to use as a source of blocks for Level 0
  int startingLevel = 0;              // The starting level of the game
  ifstream sequenceStream;            // Executes the sequence of commands found in given file
  vector<string> availableCommands{ "left", "right", "down", "clockwise", "counterclockwise", "drop",
                                          "levelup", "leveldown", "norandom", "random", "sequence", "restart", "hint",
                                          "I", "J", "L", "O", "S", "T", "Z" };

  // Handle command line arguments first
  for (int i = 1; i < argc; ++i) {
    string option(argv[i]);
    if (option == "-text") {
      textOnly = true;
    }
    else if (option == "-seed") {
      try {
        int j;
        istringstream iss{argv[i + 1]};
        if (iss >> j) {
          seed = j;
        }
      }
      catch (const out_of_range &exception) {

      }
    }
    else if (option == "-scriptfile") {
      try {
        string s;
        istringstream iss{argv[i + 1]};
        if (iss >> s) {
          scriptfile = s;
        }
      }
      catch (const out_of_range &exception) {

      }
    }
    else if (option == "-startlevel") {
      try {
        int j;
        istringstream iss{argv[i + 1]};
        if (iss >> j) {
          if (j < minLevel) {
            startingLevel = minLevel;
          }
          else if (j > maxLevel) {
            startingLevel = maxLevel;
          }
          else {
            startingLevel = j;
          }
        }
      }
      catch (const out_of_range &exception) {

      }
    }
  } // End of command line arguments

  Scoreboard scoreboard{startingLevel};
  QuadrisBoard board{textOnly, seed, scriptfile, startingLevel, &scoreboard};
  string input;
  cout << board;

  // Take in continuous input from cin
  try {
    while (true) {
      if (sequenceStream.is_open()) {
        if (!(sequenceStream >> input)) {
          sequenceStream.close();
          if (!(cin >> input)) {
            break;
          }
        }
      }
      else {
        if (!(cin >> input)) {
          break;
        }
      }
      int multiplier = 1; // Default multiplier is 1
      string cmd;

      istringstream multiplierStream{input};
      istringstream cmdStream{input};

      // If we can read in a multiplier, then we can keep using the same istringstream
      if (multiplierStream >> multiplier) {
        multiplierStream >> cmd;
      }
      // If not, the multiplierStream is no longer valid, so we use the second istringstream
      else {
        multiplier = 1;
        cmdStream >> cmd;
      }
      bool gameOver = board.isGameOver();
      vector<string> filteredVector = filter(availableCommands, cmd);
      if (filteredVector.size() == 1) {
        cmd = filteredVector.at(0);

        board.destroyHint();  // destroy the HintBlock, if it exists.

        if ((cmd == "left") && !gameOver) {
          multiplier = multiplier > numCols ? numCols : multiplier;
          for (int i = 0; i < multiplier; ++i) {
            board.left();
          }
          board.gravity();
        }
        else if ((cmd == "right") && !gameOver) {
          multiplier = multiplier > numCols ? numCols : multiplier;
          for (int i = 0; i < multiplier; ++i) {
            board.right();
          }
          board.gravity();
        }
        else if ((cmd == "down") && !gameOver) {
          multiplier = multiplier > numRows ? numRows : multiplier;
          for (int i = 0; i < multiplier; ++i) {
            board.down();
          }
          board.gravity();
        }
        else if ((cmd == "clockwise") && !gameOver) {
          for (int i = 0; i < (multiplier % 4); ++i) {
            board.clockwise();
          }
          board.gravity();
        }
        else if ((cmd == "counterclockwise") && !gameOver) {
          for (int i = 0; i < (multiplier % 4); ++i) {
            board.counterclockwise();
          }
          board.gravity();
        }
        else if ((cmd == "drop") && !gameOver) {
          multiplier = multiplier > numRows ? numRows : multiplier;
          for (int i = 0; i < multiplier; ++i) {
            board.drop();
          }
        }
        else if ((cmd == "levelup") && !gameOver) {
          multiplier = multiplier > maxLevel ? maxLevel : multiplier;
          for (int i = 0; i < multiplier; ++i) {
            board.levelup();
          }
        }
        else if ((cmd == "leveldown") && !gameOver) {
          multiplier = multiplier > maxLevel ? maxLevel : multiplier;
          for (int i = 0; i < multiplier; ++i) {
            board.leveldown();
          }
        }
        else if ((cmd == "norandom") && !gameOver) {
          string fileName;
          if (cin >> fileName) {
            board.norandom(fileName);
          }
        }
        else if ((cmd == "random") && !gameOver) {
          board.random();
        }
        else if ((cmd == "sequence") && !gameOver) {
          string fileName;
          if (cin >> fileName) {
            sequenceStream.open(fileName);
          }
        }
        else if ((cmd == "I" || cmd == "J" || cmd == "L" || cmd == "O" || cmd == "S" || cmd == "T" || cmd == "Z") && !gameOver) {
          board.replaceCurrent(cmd);
        }
        else if (cmd == "restart") {
          board.restart();
        }
        else if ((cmd == "hint") && !gameOver) {
          board.hint();
        }
      } // End of if-else statements to interpret commands

      cout << board;
    } // End of while loop
  }
  catch (const ios::failure &exception) {

  } // End of try-catch
}
