#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Map.h"

class Board {
public:
    Board(const unsigned int rows=10, const unsigned int cols=10);
    Board(const Board& orig);
    virtual ~Board();
    void printMaps();
private:
    Map m_mapA;
    Map m_mapB;
};

#endif /* BOARD_H */

