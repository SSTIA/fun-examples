//
// Created by liu on 18-3-20.
//

#include "ForbiddenPointFinder.h"
#include <iostream>

using namespace std;

void add(int x, int y, ForbiddenPointFinder::Stone cStone) {
    static ForbiddenPointFinder finder;
    cout << (int) finder.addStone(x, y, cStone) << " " << finder.nForbiddenPoints << endl;
}

int main() {
    add(7, 5, ForbiddenPointFinder::Stone::Black);
    add(0, 0, ForbiddenPointFinder::Stone::White);
    add(7, 6, ForbiddenPointFinder::Stone::Black);
    add(0, 1, ForbiddenPointFinder::Stone::White);
    add(5, 7, ForbiddenPointFinder::Stone::Black);
    add(0, 2, ForbiddenPointFinder::Stone::White);
    add(6, 7, ForbiddenPointFinder::Stone::Black);
    add(0, 3, ForbiddenPointFinder::Stone::White);
    add(7, 7, ForbiddenPointFinder::Stone::Black);
    return 0;
}