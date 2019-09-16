#include <iostream>

#include "Map.h"

Map::Map(int rowsNum, int colsNum): m_rowsNum(rowsNum), m_colsNum(colsNum)
{
    m_map = new State[rowsNum * colsNum];
    
    for (int i=0; i<rowsNum*colsNum; i++) {
        m_map[i] = State::empty;
    }
}

Map::Map(const Map& orig)
{
    m_rowsNum = orig.m_rowsNum;
    m_colsNum = orig.m_colsNum;
    
    m_map = new State[m_rowsNum * m_colsNum];
    
    for (int i=0; i<m_rowsNum*m_colsNum; i++) {
        m_map[i] = orig.m_map[i];
    }
}

Map::~Map()
{
    delete m_map;
}

Map::State Map::getState(int row, int col) const
{
    return m_map[getIndex(row, col)];
}

void Map::setState(int row, int col, State state)
{
    m_map[getIndex(row, col)] = state;
}

void Map::addBoat(int length)
{
    srand(time(NULL));
    
    int startRow, startCol, endRow, endCol, dRow, dCol;
    
    do {
        do {
            do {
                startRow = rand() % m_rowsNum;
                startCol = rand() % m_colsNum;

            } while (getState(startRow, startCol) != State::empty);

            if (rand()%2) {
                // vertical
                dRow = 0;
                dCol = (rand()%2 * 2) - 1;
            } else {
                // horizontal
                dCol = 0;
                dRow = (rand()%2 * 2) - 1;
            }

            endRow = startRow + dRow*(length-1);
            endCol = startCol + dCol*(length-1);
        } while(endRow < 0 || endRow >= m_rowsNum || endCol < 0 || endCol >= m_colsNum);
    } while (!canAddBoat(startRow, startCol, endRow, endCol, length));
    
    for (int i=0; i<length; i++) {
        setState(startRow+(i*dRow), startCol+(i*dCol), State::alive);
    }
}

std::string Map::getPositionDescription(int row, int col)
{
    char buf[4];
    snprintf(buf, 4, "%c%i", (char)(row+65), col+1);

    return std::string(buf);
}

void Map::print() const
{
    std::cout << " ";
    
    for (int i=0; i<m_colsNum; i++) {
        std::cout << i+1;
    }
    
    std::cout << std::endl;
    
    for (int i=0; i<m_rowsNum; i++) {
        std::cout << (char)(i+65);
        
        for (int j=0; j<m_colsNum; j++) {
            switch (getState(i, j)) {
                case State::alive:
                    std::cout << "O";
                    break;
                case State::dead:
                    std::cout << "X";
                    break;
                case State::empty:
                    std::cout << " ";
            }
        }
        
        std::cout << std::endl;
    }
}

int Map::getIndex(int row, int col) const
{
    return row * m_colsNum + col;
}

bool Map::canAddBoat(int startRow, int startCol, int endRow, int endCol, int length) const
{
    if (endRow < startRow) {
        int tmp = endRow;
        endRow = startRow;
        startRow = tmp;
    }
    if (endCol < startCol) {
        int tmp = endCol;
        endCol = startCol;
        startCol = tmp;
    }
    
    int row = startRow;
    do {
        int col = startCol;
        do {
            if (
                    row < 0 ||
                    col < 0 ||
                    row >= m_rowsNum ||
                    col >= m_colsNum ||
                    getState(row, col) != State::empty ||
                    (row-1 >= 0         && col-1 >= 0           && getState(row-1, col-1)   != State::empty) ||
                    (row-1 >= 0                                 && getState(row-1, col)     != State::empty) ||
                    (row-1 >= 0         && col+1 < m_colsNum    && getState(row-1, col+1)   != State::empty) ||
                    (                      col+1 < m_colsNum    && getState(row, col+1)     != State::empty) ||
                    (row+1 < m_rowsNum  && col+1 < m_colsNum    && getState(row+1, col+1)   != State::empty) ||
                    (row+1 < m_rowsNum                          && getState(row+1, col)     != State::empty) ||
                    (row+1 < m_rowsNum  && col-1 >= 0           && getState(row+1, col-1)   != State::empty) ||
                    (                      col-1 >= 0           && getState(row, col-1)     != State::empty)
            ) {
                return false;
            }
            col++;
        } while (col <= endCol);
        row++;
    } while(row <= endRow);

    return true;
}