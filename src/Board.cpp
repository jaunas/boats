#include <iostream>

#include "Board.h"
#include "Map.h"

Board::Board(const unsigned int rows, const unsigned int cols)
: m_mapA(rows, cols), m_mapB(rows, cols)
{
    for (int i=4; i>0; i--) {
        for (int j=0; j<=4-i; j++) {
            m_mapA.addBoat(i);
            m_mapB.addBoat(i);
        }
    }
}

Board::Board(const Board& orig)
: m_mapA(orig.m_mapA), m_mapB(orig.m_mapB)
{
}

Board::~Board()
{
}

void Board::printMaps()
{
    std::cout << "Map A" << std::endl;
    m_mapA.print();

    std::cout << "Map B" << std::endl;
    m_mapB.print();
}

