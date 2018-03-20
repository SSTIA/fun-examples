#ifndef FORBIDDEN_POINT_FINDER_H
#define FORBIDDEN_POINT_FINDER_H

#ifndef _MSC_VER
#include "CPoint.h"
#endif

class ForbiddenPointFinder {
public:
    // standard renju / gomoku have 15 x 15 board
    static const int BoardSize = 15;

    enum class Stone {
        Black = 'X',
        White = 'O',
        Empty = '.',
        Wall = '$'
    };

    enum class Result {
        BlackWin = 0,
        WhiteWin = 1,
        Forbidden = 2,
        UNKNOWN = -1
    };

    int nForbiddenPoints = 0;
    CPoint ptForbidden[BoardSize * BoardSize] = {};

private:
    Stone cBoard[BoardSize + 2][BoardSize + 2];

public:
    ForbiddenPointFinder();

    virtual ~ForbiddenPointFinder();

    void clear();

    Result addStone(int x, int y, Stone cStone);

private:
    void setStone(int x, int y, Stone cStone);

    bool isFive(int x, int y, int nColor);

    bool isOverline(int x, int y);

    bool isFive(int x, int y, int nColor, int nDir);

    bool isFour(int x, int y, int nColor, int nDir);

    int isOpenFour(int x, int y, int nColor, int nDir);

    bool isOpenThree(int x, int y, int nColor, int nDir);

    bool isDoubleFour(int x, int y);

    bool isDoubleThree(int x, int y);

    void findForbiddenPoints();
};

#endif // FORBIDDEN_POINT_FINDER_H