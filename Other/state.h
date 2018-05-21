#ifndef STATE_H
#define STATE_H

enum class SquareType { I, J, L, O, S, Z, T, Empty, Hint, Single };

struct State {
  SquareType type; // What type of Tetromino am I?
};

#endif
