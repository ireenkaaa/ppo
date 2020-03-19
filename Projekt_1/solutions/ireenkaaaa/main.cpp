#include <iostream>
#include "minesweeperboard.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "field.h"
#include "minesweeperboard.cpp"
using std::cout;
using std::endl;

int main() {
    srand( time( NULL ) );
    MinesweeperBoard Board1(9, 7, DEBUG);
    Board1.debug_display();

    return 0;
}
