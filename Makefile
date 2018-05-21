CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -MMD -Werror=vla
EXEC = quadris
OBJECTS = main.o Board/quadrisboard.o Board/scoreboard.o Display/textdisplay.o Display/graphicsdisplay.o Display/window.o Levels/level.o Levels/level0.o Levels/level1.o Levels/level2.o Levels/level3.o Levels/level4.o Other/subject.o Tetrominoes/hintblock.o Tetrominoes/iblock.o Tetrominoes/jblock.o Tetrominoes/lblock.o Tetrominoes/oblock.o Tetrominoes/sblock.o Tetrominoes/singleblock.o Tetrominoes/square.o Tetrominoes/tblock.o Tetrominoes/tetromino.o Tetrominoes/zblock.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
