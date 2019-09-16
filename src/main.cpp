#include <iostream>

#include "Map.h"

int main(int argc, char** argv)
{
    Map map(10, 10);
    
    map.addBoat(4);
    map.addBoat(3);
    map.addBoat(3);
    map.addBoat(2);
    map.addBoat(2);
    map.addBoat(2);
    map.addBoat(1);
    map.addBoat(1);
    map.addBoat(1);
    map.addBoat(1);
    
    map.print();
    
    return 0;
}

