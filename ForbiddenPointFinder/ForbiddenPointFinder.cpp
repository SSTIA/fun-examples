// ForbiddenPointFinder.cpp: implementation of the CForbiddenPointFinder class.
//
// Code written by: Wenzhe Lu
// Modified by: tc-imba (https://github.com/tc-imba)
//
//////////////////////////////////////////////////////////////////////

#include "ForbiddenPointFinder.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CForbiddenPointFinder::CForbiddenPointFinder() {
    Clear();
}

CForbiddenPointFinder::~CForbiddenPointFinder() {
}

//////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////

void CForbiddenPointFinder::Clear() {
    nForbiddenPoints = 0;

    for (int i = 0; i < BOARD_SIZE + 2; i++) {
        cBoard[0][i] = '$';
        cBoard[(BOARD_SIZE + 1)][i] = '$';
        cBoard[i][0] = '$';
        cBoard[i][(BOARD_SIZE + 1)] = '$';
    }

    for (int i = 1; i <= BOARD_SIZE; i++)
        for (int j = 1; j <= BOARD_SIZE; j++)
            cBoard[i][j] = EMPTY_STONE;
}

int CForbiddenPointFinder::AddStone(int x, int y, char cStone) {
    int nResult = -1;

    if (cStone == BLACK_STONE) {
        if (IsFive(x, y, 0))
            nResult = BLACK_FIVE;
        for (int i = 0; i < nForbiddenPoints; i++) {
            if (ptForbidden[i] == CPoint(x, y))
                nResult = BLACK_FORBIDDEN;
        }
    } else if (cStone == WHITE_STONE) {
        if (IsFive(x, y, 1))
            nResult = WHITE_FIVE;
    }

    cBoard[x + 1][y + 1] = cStone;
    if (nResult == -1)
        FindForbiddenPoints();
    else
        nForbiddenPoints = 0;
    return nResult;
}

void CForbiddenPointFinder::SetStone(int x, int y, char cStone) {
    cBoard[x + 1][y + 1] = cStone;
}

bool CForbiddenPointFinder::IsFive(int x, int y, int nColor) {
    if (cBoard[x + 1][y + 1] != EMPTY_STONE)
        return false;

    if (nColor == 0)    // black
    {
        SetStone(x, y, BLACK_STONE);

        // detect black five
        int i, j;

        // 1 - horizontal direction
        int nLine = 1;
        i = x;
        while (i > 0) {
            if (cBoard[i--][y + 1] == BLACK_STONE)
                nLine++;
            else
                break;
        }
        i = x + 2;
        while (i < (BOARD_SIZE + 1)) {
            if (cBoard[i++][y + 1] == BLACK_STONE)
                nLine++;
            else
                break;
        }
        if (nLine == 5) {
            SetStone(x, y, EMPTY_STONE);
            return true;
        }

        // 2 - vertical direction
        nLine = 1;
        i = y;
        while (i > 0) {
            if (cBoard[x + 1][i--] == BLACK_STONE)
                nLine++;
            else
                break;
        }
        i = y + 2;
        while (i < (BOARD_SIZE + 1)) {
            if (cBoard[x + 1][i++] == BLACK_STONE)
                nLine++;
            else
                break;
        }
        if (nLine == 5) {
            SetStone(x, y, EMPTY_STONE);
            return true;
        }

        // 3 - diagonal direction (lower-left to upper-right: '/')
        nLine = 1;
        i = x;
        j = y;
        while ((i > 0) && (j > 0)) {
            if (cBoard[i--][j--] == BLACK_STONE)
                nLine++;
            else
                break;
        }
        i = x + 2;
        j = y + 2;
        while ((i < (BOARD_SIZE + 1)) && (j < (BOARD_SIZE + 1))) {
            if (cBoard[i++][j++] == BLACK_STONE)
                nLine++;
            else
                break;
        }
        if (nLine == 5) {
            SetStone(x, y, EMPTY_STONE);
            return true;
        }

        // 4 - diagonal direction (upper-left to lower-right: '\')
        nLine = 1;
        i = x;
        j = y + 2;
        while ((i > 0) && (j < (BOARD_SIZE + 1))) {
            if (cBoard[i--][j++] == BLACK_STONE)
                nLine++;
            else
                break;
        }
        i = x + 2;
        j = y;
        while ((i < (BOARD_SIZE + 1)) && (j > 0)) {
            if (cBoard[i++][j--] == BLACK_STONE)
                nLine++;
            else
                break;
        }
        if (nLine == 5) {
            SetStone(x, y, EMPTY_STONE);
            return true;
        }

        SetStone(x, y, EMPTY_STONE);
        return false;
    } else if (nColor == 1)    // white
    {
        SetStone(x, y, WHITE_STONE);

        // detect white five or more
        int i, j;

        // 1 - horizontal direction
        int nLine = 1;
        i = x;
        while (i > 0) {
            if (cBoard[i--][y + 1] == WHITE_STONE)
                nLine++;
            else
                break;
        }
        i = x + 2;
        while (i < (BOARD_SIZE + 1)) {
            if (cBoard[i++][y + 1] == WHITE_STONE)
                nLine++;
            else
                break;
        }
        if (nLine >= 5) {
            SetStone(x, y, EMPTY_STONE);
            return true;
        }

        // 2 - vertical direction
        nLine = 1;
        i = y;
        while (i > 0) {
            if (cBoard[x + 1][i--] == WHITE_STONE)
                nLine++;
            else
                break;
        }
        i = y + 2;
        while (i < (BOARD_SIZE + 1)) {
            if (cBoard[x + 1][i++] == WHITE_STONE)
                nLine++;
            else
                break;
        }
        if (nLine >= 5) {
            SetStone(x, y, EMPTY_STONE);
            return true;
        }

        // 3 - diagonal direction (lower-left to upper-right: '/')
        nLine = 1;
        i = x;
        j = y;
        while ((i > 0) && (j > 0)) {
            if (cBoard[i--][j--] == WHITE_STONE)
                nLine++;
            else
                break;
        }
        i = x + 2;
        j = y + 2;
        while ((i < (BOARD_SIZE + 1)) && (j < (BOARD_SIZE + 1))) {
            if (cBoard[i++][j++] == WHITE_STONE)
                nLine++;
            else
                break;
        }
        if (nLine >= 5) {
            SetStone(x, y, EMPTY_STONE);
            return true;
        }

        // 4 - diagonal direction (upper-left to lower-right: '\')
        nLine = 1;
        i = x;
        j = y + 2;
        while ((i > 0) && (j < (BOARD_SIZE + 1))) {
            if (cBoard[i--][j++] == WHITE_STONE)
                nLine++;
            else
                break;
        }
        i = x + 2;
        j = y;
        while ((i < (BOARD_SIZE + 1)) && (j > 0)) {
            if (cBoard[i++][j--] == WHITE_STONE)
                nLine++;
            else
                break;
        }
        if (nLine >= 5) {
            SetStone(x, y, EMPTY_STONE);
            return true;
        }

        SetStone(x, y, EMPTY_STONE);
        return false;
    } else
        return false;
}

bool CForbiddenPointFinder::IsOverline(int x, int y) {
    if (cBoard[x + 1][y + 1] != EMPTY_STONE)
        return false;

    SetStone(x, y, BLACK_STONE);

    // detect black overline
    int i, j;
    bool bOverline = false;

    // 1 - horizontal direction
    int nLine = 1;
    i = x;
    while (i > 0) {
        if (cBoard[i--][y + 1] == BLACK_STONE)
            nLine++;
        else
            break;
    }
    i = x + 2;
    while (i < (BOARD_SIZE + 1)) {
        if (cBoard[i++][y + 1] == BLACK_STONE)
            nLine++;
        else
            break;
    }
    if (nLine == 5) {
        SetStone(x, y, EMPTY_STONE);
        return false;
    } else
        bOverline |= (nLine >= 6);

    // 2 - vertical direction
    nLine = 1;
    i = y;
    while (i > 0) {
        if (cBoard[x + 1][i--] == BLACK_STONE)
            nLine++;
        else
            break;
    }
    i = y + 2;
    while (i < (BOARD_SIZE + 1)) {
        if (cBoard[x + 1][i++] == BLACK_STONE)
            nLine++;
        else
            break;
    }
    if (nLine == 5) {
        SetStone(x, y, EMPTY_STONE);
        return false;
    } else
        bOverline |= (nLine >= 6);

    // 3 - diagonal direction (lower-left to upper-right: '/')
    nLine = 1;
    i = x;
    j = y;
    while ((i > 0) && (j > 0)) {
        if (cBoard[i--][j--] == BLACK_STONE)
            nLine++;
        else
            break;
    }
    i = x + 2;
    j = y + 2;
    while ((i < (BOARD_SIZE + 1)) && (j < (BOARD_SIZE + 1))) {
        if (cBoard[i++][j++] == BLACK_STONE)
            nLine++;
        else
            break;
    }
    if (nLine == 5) {
        SetStone(x, y, EMPTY_STONE);
        return false;
    } else
        bOverline |= (nLine >= 6);

    // 4 - diagonal direction (upper-left to lower-right: '\')
    nLine = 1;
    i = x;
    j = y + 2;
    while ((i > 0) && (j < (BOARD_SIZE + 1))) {
        if (cBoard[i--][j++] == BLACK_STONE)
            nLine++;
        else
            break;
    }
    i = x + 2;
    j = y;
    while ((i < (BOARD_SIZE + 1)) && (j > 0)) {
        if (cBoard[i++][j--] == BLACK_STONE)
            nLine++;
        else
            break;
    }
    if (nLine == 5) {
        SetStone(x, y, EMPTY_STONE);
        return false;
    } else
        bOverline |= (nLine >= 6);

    SetStone(x, y, EMPTY_STONE);
    return bOverline;
}

bool CForbiddenPointFinder::IsFive(int x, int y, int nColor, int nDir) {
    if (cBoard[x + 1][y + 1] != EMPTY_STONE)
        return false;

    char c;
    if (nColor == 0)    // black
        c = BLACK_STONE;
    else if (nColor == 1)    // white
        c = WHITE_STONE;
    else
        return false;

    SetStone(x, y, c);

    int i, j;
    int nLine;

    switch (nDir) {
        case 1:        // horizontal direction
            nLine = 1;
            i = x;
            while (i > 0) {
                if (cBoard[i--][y + 1] == c)
                    nLine++;
                else
                    break;
            }
            i = x + 2;
            while (i < (BOARD_SIZE + 1)) {
                if (cBoard[i++][y + 1] == c)
                    nLine++;
                else
                    break;
            }
            if (nLine == 5) {
                SetStone(x, y, EMPTY_STONE);
                return true;
            } else {
                SetStone(x, y, EMPTY_STONE);
                return false;
            }
            break;
        case 2:        // vertial direction
            nLine = 1;
            i = y;
            while (i > 0) {
                if (cBoard[x + 1][i--] == c)
                    nLine++;
                else
                    break;
            }
            i = y + 2;
            while (i < (BOARD_SIZE + 1)) {
                if (cBoard[x + 1][i++] == c)
                    nLine++;
                else
                    break;
            }
            if (nLine == 5) {
                SetStone(x, y, EMPTY_STONE);
                return true;
            } else {
                SetStone(x, y, EMPTY_STONE);
                return false;
            }
            break;
        case 3:        // diagonal direction - '/'
            nLine = 1;
            i = x;
            j = y;
            while ((i > 0) && (j > 0)) {
                if (cBoard[i--][j--] == c)
                    nLine++;
                else
                    break;
            }
            i = x + 2;
            j = y + 2;
            while ((i < (BOARD_SIZE + 1)) && (j < (BOARD_SIZE + 1))) {
                if (cBoard[i++][j++] == c)
                    nLine++;
                else
                    break;
            }
            if (nLine == 5) {
                SetStone(x, y, EMPTY_STONE);
                return true;
            } else {
                SetStone(x, y, EMPTY_STONE);
                return false;
            }
            break;
        case 4:        // diagonal direction - '\'
            nLine = 1;
            i = x;
            j = y + 2;
            while ((i > 0) && (j < (BOARD_SIZE + 1))) {
                if (cBoard[i--][j++] == c)
                    nLine++;
                else
                    break;
            }
            i = x + 2;
            j = y;
            while ((i < (BOARD_SIZE + 1)) && (j > 0)) {
                if (cBoard[i++][j--] == c)
                    nLine++;
                else
                    break;
            }
            if (nLine == 5) {
                SetStone(x, y, EMPTY_STONE);
                return true;
            } else {
                SetStone(x, y, EMPTY_STONE);
                return false;
            }
            break;
        default:
            SetStone(x, y, EMPTY_STONE);
            return false;
            break;
    }
}

bool CForbiddenPointFinder::IsFour(int x, int y, int nColor, int nDir) {
    if (cBoard[x + 1][y + 1] != EMPTY_STONE)
        return false;

    if (IsFive(x, y, nColor))    // five?
        return false;
    else if ((nColor == 0) && (IsOverline(x, y)))    // black overline?
        return false;
    else {
        char c;
        if (nColor == 0)    // black
            c = BLACK_STONE;
        else if (nColor == 1)    // white
            c = WHITE_STONE;
        else
            return false;

        SetStone(x, y, c);

        int i, j;

        switch (nDir) {
            case 1:        // horizontal direction
                i = x;
                while (i > 0) {
                    if (cBoard[i][y + 1] == c) {
                        i--;
                        continue;
                    } else if (cBoard[i][y + 1] == EMPTY_STONE) {
                        if (IsFive(i - 1, y, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = x + 2;
                while (i < (BOARD_SIZE + 1)) {
                    if (cBoard[i][y + 1] == c) {
                        i++;
                        continue;
                    } else if (cBoard[i][y + 1] == EMPTY_STONE) {
                        if (IsFive(i - 1, y, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                SetStone(x, y, EMPTY_STONE);
                return false;
                break;
            case 2:        // vertial direction
                i = y;
                while (i > 0) {
                    if (cBoard[x + 1][i] == c) {
                        i--;
                        continue;
                    } else if (cBoard[x + 1][i] == EMPTY_STONE) {
                        if (IsFive(x, i - 1, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = y + 2;
                while (i < (BOARD_SIZE + 1)) {
                    if (cBoard[x + 1][i] == c) {
                        i++;
                        continue;
                    } else if (cBoard[x + 1][i] == EMPTY_STONE) {
                        if (IsFive(x, i - 1, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                SetStone(x, y, EMPTY_STONE);
                return false;
                break;
            case 3:        // diagonal direction - '/'
                i = x;
                j = y;
                while ((i > 0) && (j > 0)) {
                    if (cBoard[i][j] == c) {
                        i--;
                        j--;
                        continue;
                    } else if (cBoard[i][j] == EMPTY_STONE) {
                        if (IsFive(i - 1, j - 1, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = x + 2;
                j = y + 2;
                while ((i < (BOARD_SIZE + 1)) && (j < (BOARD_SIZE + 1))) {
                    if (cBoard[i][j] == c) {
                        i++;
                        j++;
                        continue;
                    } else if (cBoard[i][j] == EMPTY_STONE) {
                        if (IsFive(i - 1, j - 1, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                SetStone(x, y, EMPTY_STONE);
                return false;
                break;
            case 4:        // diagonal direction - '\'
                i = x;
                j = y + 2;
                while ((i > 0) && (j < (BOARD_SIZE + 1))) {
                    if (cBoard[i][j] == c) {
                        i--;
                        j++;
                        continue;
                    } else if (cBoard[i][j] == EMPTY_STONE) {
                        if (IsFive(i - 1, j - 1, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = x + 2;
                j = y;
                while ((i < (BOARD_SIZE + 1)) && (j > 0)) {
                    if (cBoard[i][j] == c) {
                        i++;
                        j--;
                        continue;
                    } else if (cBoard[i][j] == EMPTY_STONE) {
                        if (IsFive(i - 1, j - 1, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                SetStone(x, y, EMPTY_STONE);
                return false;
                break;
            default:
                SetStone(x, y, EMPTY_STONE);
                return false;
                break;
        }
    }
}

int CForbiddenPointFinder::IsOpenFour(int x, int y, int nColor, int nDir) {
    if (cBoard[x + 1][y + 1] != EMPTY_STONE)
        return 0;

    if (IsFive(x, y, nColor))    // five?
        return 0;
    else if ((nColor == 0) && (IsOverline(x, y)))    // black overline?
        return 0;
    else {
        char c;
        if (nColor == 0)    // black
            c = BLACK_STONE;
        else if (nColor == 1)    // white
            c = WHITE_STONE;
        else
            return 0;

        SetStone(x, y, c);

        int i, j;
        int nLine;

        switch (nDir) {
            case 1:        // horizontal direction
                nLine = 1;
                i = x;
                while (i >= 0) {
                    if (cBoard[i][y + 1] == c) {
                        i--;
                        nLine++;
                        continue;
                    } else if (cBoard[i][y + 1] == EMPTY_STONE) {
                        if (!IsFive(i - 1, y, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return 0;
                        } else
                            break;
                    } else {
                        SetStone(x, y, EMPTY_STONE);
                        return 0;
                    }
                }
                i = x + 2;
                while (i < (BOARD_SIZE + 1)) {
                    if (cBoard[i][y + 1] == c) {
                        i++;
                        nLine++;
                        continue;
                    } else if (cBoard[i][y + 1] == EMPTY_STONE) {
                        if (IsFive(i - 1, y, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return (nLine == 4 ? 1 : 2);
                        } else
                            break;
                    } else
                        break;
                }
                SetStone(x, y, EMPTY_STONE);
                return 0;
                break;
            case 2:        // vertial direction
                nLine = 1;
                i = y;
                while (i >= 0) {
                    if (cBoard[x + 1][i] == c) {
                        i--;
                        nLine++;
                        continue;
                    } else if (cBoard[x + 1][i] == EMPTY_STONE) {
                        if (!IsFive(x, i - 1, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return 0;
                        } else
                            break;
                    } else {
                        SetStone(x, y, EMPTY_STONE);
                        return 0;
                    }
                }
                i = y + 2;
                while (i < (BOARD_SIZE + 1)) {
                    if (cBoard[x + 1][i] == c) {
                        i++;
                        nLine++;
                        continue;
                    } else if (cBoard[x + 1][i] == EMPTY_STONE) {
                        if (IsFive(x, i - 1, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return (nLine == 4 ? 1 : 2);
                        } else
                            break;
                    } else
                        break;
                }
                SetStone(x, y, EMPTY_STONE);
                return 0;
                break;
            case 3:        // diagonal direction - '/'
                nLine = 1;
                i = x;
                j = y;
                while ((i >= 0) && (j >= 0)) {
                    if (cBoard[i][j] == c) {
                        i--;
                        j--;
                        nLine++;
                        continue;
                    } else if (cBoard[i][j] == EMPTY_STONE) {
                        if (!IsFive(i - 1, j - 1, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return 0;
                        } else
                            break;
                    } else {
                        SetStone(x, y, EMPTY_STONE);
                        return 0;
                    }
                }
                i = x + 2;
                j = y + 2;
                while ((i < (BOARD_SIZE + 1)) && (j < (BOARD_SIZE + 1))) {
                    if (cBoard[i][j] == c) {
                        i++;
                        j++;
                        nLine++;
                        continue;
                    } else if (cBoard[i][j] == EMPTY_STONE) {
                        if (IsFive(i - 1, j - 1, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return (nLine == 4 ? 1 : 2);
                        } else
                            break;
                    } else
                        break;
                }
                SetStone(x, y, EMPTY_STONE);
                return 0;
                break;
            case 4:        // diagonal direction - '\'
                nLine = 1;
                i = x;
                j = y + 2;
                while ((i >= 0) && (j <= (BOARD_SIZE + 1))) {
                    if (cBoard[i][j] == c) {
                        i--;
                        j++;
                        nLine++;
                        continue;
                    } else if (cBoard[i][j] == EMPTY_STONE) {
                        if (!IsFive(i - 1, j - 1, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return 0;
                        } else
                            break;
                    } else {
                        SetStone(x, y, EMPTY_STONE);
                        return 0;
                    }
                }
                i = x + 2;
                j = y;
                while ((i < (BOARD_SIZE + 1)) && (j > 0)) {
                    if (cBoard[i][j] == c) {
                        i++;
                        j--;
                        nLine++;
                        continue;
                    } else if (cBoard[i][j] == EMPTY_STONE) {
                        if (IsFive(i - 1, j - 1, 0, nDir)) {
                            SetStone(x, y, EMPTY_STONE);
                            return (nLine == 4 ? 1 : 2);
                        } else
                            break;
                    } else
                        break;
                }
                SetStone(x, y, EMPTY_STONE);
                return 0;
                break;
            default:
                SetStone(x, y, EMPTY_STONE);
                return 0;
                break;
        }
    }
}

bool CForbiddenPointFinder::IsDoubleFour(int x, int y) {
    if (cBoard[x + 1][y + 1] != EMPTY_STONE)
        return false;

    if (IsFive(x, y, 0))    // five?
        return false;

    int nFour = 0;
    for (int i = 1; i <= 4; i++) {
        if (IsOpenFour(x, y, 0, i) == 2)
            nFour += 2;
        else if (IsFour(x, y, 0, i))
            nFour++;
    }

    if (nFour >= 2)
        return true;
    else
        return false;
}

bool CForbiddenPointFinder::IsOpenThree(int x, int y, int nColor, int nDir) {
    if (IsFive(x, y, nColor))    // five?
        return false;
    else if ((nColor == 0) && (IsOverline(x, y)))    // black overline?
        return false;
    else {
        char c;
        if (nColor == 0)    // black
            c = BLACK_STONE;
        else if (nColor == 1)    // white
            c = WHITE_STONE;
        else
            return false;

        SetStone(x, y, c);

        int i, j;

        switch (nDir) {
            case 1:        // horizontal direction
                i = x;
                while (i > 0) {
                    if (cBoard[i][y + 1] == c) {
                        i--;
                        continue;
                    } else if (cBoard[i][y + 1] == EMPTY_STONE) {
                        if ((IsOpenFour(i - 1, y, nColor, nDir) == 1) && (!IsDoubleFour(i - 1, y)) &&
                            (!IsDoubleThree(i - 1, y))) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = x + 2;
                while (i < (BOARD_SIZE + 1)) {
                    if (cBoard[i][y + 1] == c) {
                        i++;
                        continue;
                    } else if (cBoard[i][y + 1] == EMPTY_STONE) {
                        if ((IsOpenFour(i - 1, y, nColor, nDir) == 1) && (!IsDoubleFour(i - 1, y)) &&
                            (!IsDoubleThree(i - 1, y))) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                SetStone(x, y, EMPTY_STONE);
                return false;
                break;
            case 2:        // vertial direction
                i = y;
                while (i > 0) {
                    if (cBoard[x + 1][i] == c) {
                        i--;
                        continue;
                    } else if (cBoard[x + 1][i] == EMPTY_STONE) {
                        if ((IsOpenFour(x, i - 1, nColor, nDir) == 1) && (!IsDoubleFour(x, i - 1)) &&
                            (!IsDoubleThree(x, i - 1))) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = y + 2;
                while (i < (BOARD_SIZE + 1)) {
                    if (cBoard[x + 1][i] == c) {
                        i++;
                        continue;
                    } else if (cBoard[x + 1][i] == EMPTY_STONE) {
                        if ((IsOpenFour(x, i - 1, nColor, nDir) == 1) && (!IsDoubleFour(x, i - 1)) &&
                            (!IsDoubleThree(x, i - 1))) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                SetStone(x, y, EMPTY_STONE);
                return false;
                break;
            case 3:        // diagonal direction - '/'
                i = x;
                j = y;
                while ((i > 0) && (j > 0)) {
                    if (cBoard[i][j] == c) {
                        i--;
                        j--;
                        continue;
                    } else if (cBoard[i][j] == EMPTY_STONE) {
                        if ((IsOpenFour(i - 1, j - 1, nColor, nDir) == 1) && (!IsDoubleFour(i - 1, j - 1)) &&
                            (!IsDoubleThree(i - 1, j - 1))) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = x + 2;
                j = y + 2;
                while ((i < (BOARD_SIZE + 1)) && (j < (BOARD_SIZE + 1))) {
                    if (cBoard[i][j] == c) {
                        i++;
                        j++;
                        continue;
                    } else if (cBoard[i][j] == EMPTY_STONE) {
                        if ((IsOpenFour(i - 1, j - 1, nColor, nDir) == 1) && (!IsDoubleFour(i - 1, j - 1)) &&
                            (!IsDoubleThree(i - 1, j - 1))) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                SetStone(x, y, EMPTY_STONE);
                return false;
                break;
            case 4:        // diagonal direction - '\'
                i = x;
                j = y + 2;
                while ((i > 0) && (j < (BOARD_SIZE + 1))) {
                    if (cBoard[i][j] == c) {
                        i--;
                        j++;
                        continue;
                    } else if (cBoard[i][j] == EMPTY_STONE) {
                        if ((IsOpenFour(i - 1, j - 1, nColor, nDir) == 1) && (!IsDoubleFour(i - 1, j - 1)) &&
                            (!IsDoubleThree(i - 1, j - 1))) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = x + 2;
                j = y;
                while ((i < (BOARD_SIZE + 1)) && (j > 0)) {
                    if (cBoard[i][j] == c) {
                        i++;
                        j--;
                        continue;
                    } else if (cBoard[i][j] == EMPTY_STONE) {
                        if ((IsOpenFour(i - 1, j - 1, nColor, nDir) == 1) && (!IsDoubleFour(i - 1, j - 1)) &&
                            (!IsDoubleThree(i - 1, j - 1))) {
                            SetStone(x, y, EMPTY_STONE);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                SetStone(x, y, EMPTY_STONE);
                return false;
                break;
            default:
                SetStone(x, y, EMPTY_STONE);
                return false;
                break;
        }
    }
}

bool CForbiddenPointFinder::IsDoubleThree(int x, int y) {
    if (cBoard[x + 1][y + 1] != EMPTY_STONE)
        return false;

    if (IsFive(x, y, 0))    // five?
        return false;

    int nThree = 0;
    for (int i = 1; i <= 4; i++) {
        if (IsOpenThree(x, y, 0, i))
            nThree++;
    }

    if (nThree >= 2)
        return true;
    else
        return false;
}

void CForbiddenPointFinder::FindForbiddenPoints() {
    nForbiddenPoints = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (cBoard[i + 1][j + 1] != EMPTY_STONE)
                continue;
            else {
                if (IsOverline(i, j) || IsDoubleFour(i, j) || IsDoubleThree(i, j)) {
                    ptForbidden[nForbiddenPoints].x = i;
                    ptForbidden[nForbiddenPoints].y = j;
                    nForbiddenPoints++;
                }
            }
        }
    }
}