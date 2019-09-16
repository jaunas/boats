#ifndef MAP_H
#define MAP_H

#include <string>

class Map {
public:
    enum State { empty, alive, dead };

    Map(int colsNum, int rowsNum);
    Map(const Map& orig);
    virtual ~Map();
    State getState(int row, int col) const;
    void setState(int row, int col, State state);
    void addBoat(int length);
    static std::string getPositionDescription(int row, int col);
    
    void print() const;
    bool canAddBoat(int startRow, int startCol, int endRow, int endCol, int length) const;
private:
    State* m_map;
    int m_colsNum, m_rowsNum;
    
    int getIndex(int row, int col) const;
};

#endif /* MAP_H */

