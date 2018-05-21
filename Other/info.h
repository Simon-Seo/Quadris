#ifndef INFO_H_
#define INFO_H_

enum class SubjectType { Tetromino, Square, Level, Scoreboard };

struct Info {
  int row, col;        // Coordinates of Square (if Subject is a Square)
  SubjectType subject; // Which Subject am I?
};

#endif
