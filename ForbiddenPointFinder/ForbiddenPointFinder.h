#ifndef FORBIDDEN_POINT_FINDER_H
#define FORBIDDEN_POINT_FINDER_H

#include "CPoint.h"

#define BOARD_SIZE 15
#define BLACK_STONE 'X'
#define WHITE_STONE 'O'
#define EMPTY_STONE '.'
#define BLACK_FIVE 0
#define WHITE_FIVE 1
#define BLACK_FORBIDDEN 2

class CForbiddenPointFinder {
public:
    int nForbiddenPoints;
    CPoint ptForbidden[BOARD_SIZE * BOARD_SIZE];

private:
    char cBoard[BOARD_SIZE + 2][BOARD_SIZE + 2];

public:
    CForbiddenPointFinder();
    virtual ~CForbiddenPointFinder();

    void Clear();
    int AddStone(int x, int y, char cStone);

private:
    void SetStone(int x, int y, char cStone);
    bool IsFive(int x, int y, int nColor);
    bool IsOverline(int x, int y);
    bool IsFive(int x, int y, int nColor, int nDir);
    bool IsFour(int x, int y, int nColor, int nDir);
    int IsOpenFour(int x, int y, int nColor, int nDir);
    bool IsOpenThree(int x, int y, int nColor, int nDir);
    bool IsDoubleFour(int x, int y);
    bool IsDoubleThree(int x, int y);

    void FindForbiddenPoints();
};

#endif // FORBIDDEN_POINT_FINDER_H