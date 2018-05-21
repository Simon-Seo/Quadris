#include <string>
#include "level0.h"
#include "../Other/state.h"
#include "../Tetrominoes/iblock.h"
#include "../Tetrominoes/jblock.h"
#include "../Tetrominoes/lblock.h"
#include "../Tetrominoes/oblock.h"
#include "../Tetrominoes/sblock.h"
#include "../Tetrominoes/tblock.h"
#include "../Tetrominoes/zblock.h"
#include "../Tetrominoes/tetromino.h"
using namespace std;

Level0::Level0(string scriptFile): Level{0, 1, scriptFile}, scriptFile{scriptFile} {

}

// Level0 creates next blocks from sequence.txt or a specified file
Tetromino *Level0::createNextBlock() {
  string nextBlockType;
  if (!(sequenceFileStream >> nextBlockType)) {
    sequenceFileStream.close();
    sequenceFileStream.open(scriptFile);
    sequenceFileStream >> nextBlockType;
  }

  return createBlock(nextBlockType);
}

// Level 0 does not have an external constructive force
Tetromino *Level0::createSingleBlock() {
  return nullptr;
}

void Level0::norandom(string fileName) {
  // There is no concept of "randomness" in Level0
}

void Level0::random() {

}

void Level0::resetBlocksPlaced() {
  // Level 0 does not keep track of the blocks placed
}
