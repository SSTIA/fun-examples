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

ForbiddenPointFinder::ForbiddenPointFinder() {
    clear();
}

ForbiddenPointFinder::~ForbiddenPointFinder() {
}

//////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////

void ForbiddenPointFinder::clear() {
    nForbiddenPoints = 0;

    for (int i = 0; i < BoardSize + 2; i++) {
        cBoard[0][i] = Stone ::Wall;
        cBoard[(BoardSize + 1)][i] = Stone ::Wall;
        cBoard[i][0] = Stone ::Wall;
        cBoard[i][(BoardSize + 1)] = Stone ::Wall;
    }

    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
            cBoard[i][j] = Stone::Empty;
}

ForbiddenPointFinder::Result ForbiddenPointFinder::addStone(int x, int y, Stone cStone) {
    Result nResult = Result::UNKNOWN;

    if (cStone == Stone::Black) {
        if (isFive(x, y, 0))
            nResult = Result::BlackWin;
        for (int i = 0; i < nForbiddenPoints; i++) {
            if (ptForbidden[i] == CPoint(x, y))
                nResult = Result::Forbidden;
        }
    } else if (cStone == Stone::White) {
        if (isFive(x, y, 1))
            nResult = Result::WhiteWin;
    }

    cBoard[x + 1][y + 1] = cStone;
    if (nResult == Result::UNKNOWN)
        findForbiddenPoints();
    else
        nForbiddenPoints = 0;
    return nResult;
}

void ForbiddenPointFinder::setStone(int x, int y, Stone cStone) {
    cBoard[x + 1][y + 1] = cStone;
}

bool ForbiddenPointFinder::isFive(int x, int y, int nColor) {
    if (cBoard[x + 1][y + 1] != Stone::Empty)
        return false;

    if (nColor == 0)    // black
    {
        setStone(x, y, Stone::Black);

        // detect black five
        int i, j;

        // 1 - horizontal direction
        int nLine = 1;
        i = x;
        while (i > 0) {
            if (cBoard[i--][y + 1] == Stone::Black)
                nLine++;
            else
                break;
        }
        i = x + 2;
        while (i < (BoardSize + 1)) {
            if (cBoard[i++][y + 1] == Stone::Black)
                nLine++;
            else
                break;
        }
        if (nLine == 5) {
            setStone(x, y, Stone::Empty);
            return true;
        }

        // 2 - vertical direction
        nLine = 1;
        i = y;
        while (i > 0) {
            if (cBoard[x + 1][i--] == Stone::Black)
                nLine++;
            else
                break;
        }
        i = y + 2;
        while (i < (BoardSize + 1)) {
            if (cBoard[x + 1][i++] == Stone::Black)
                nLine++;
            else
                break;
        }
        if (nLine == 5) {
            setStone(x, y, Stone::Empty);
            return true;
        }

        // 3 - diagonal direction (lower-left to upper-right: '/')
        nLine = 1;
        i = x;
        j = y;
        while ((i > 0) && (j > 0)) {
            if (cBoard[i--][j--] == Stone::Black)
                nLine++;
            else
                break;
        }
        i = x + 2;
        j = y + 2;
        while ((i < (BoardSize + 1)) && (j < (BoardSize + 1))) {
            if (cBoard[i++][j++] == Stone::Black)
                nLine++;
            else
                break;
        }
        if (nLine == 5) {
            setStone(x, y, Stone::Empty);
            return true;
        }

        // 4 - diagonal direction (upper-left to lower-right: '\')
        nLine = 1;
        i = x;
        j = y + 2;
        while ((i > 0) && (j < (BoardSize + 1))) {
            if (cBoard[i--][j++] == Stone::Black)
                nLine++;
            else
                break;
        }
        i = x + 2;
        j = y;
        while ((i < (BoardSize + 1)) && (j > 0)) {
            if (cBoard[i++][j--] == Stone::Black)
                nLine++;
            else
                break;
        }
        if (nLine == 5) {
            setStone(x, y, Stone::Empty);
            return true;
        }

        setStone(x, y, Stone::Empty);
        return false;
    } else if (nColor == 1)    // white
    {
        setStone(x, y, Stone::White);

        // detect white five or more
        int i, j;

        // 1 - horizontal direction
        int nLine = 1;
        i = x;
        while (i > 0) {
            if (cBoard[i--][y + 1] == Stone::White)
                nLine++;
            else
                break;
        }
        i = x + 2;
        while (i < (BoardSize + 1)) {
            if (cBoard[i++][y + 1] == Stone::White)
                nLine++;
            else
                break;
        }
        if (nLine >= 5) {
            setStone(x, y, Stone::Empty);
            return true;
        }

        // 2 - vertical direction
        nLine = 1;
        i = y;
        while (i > 0) {
            if (cBoard[x + 1][i--] == Stone::White)
                nLine++;
            else
                break;
        }
        i = y + 2;
        while (i < (BoardSize + 1)) {
            if (cBoard[x + 1][i++] == Stone::White)
                nLine++;
            else
                break;
        }
        if (nLine >= 5) {
            setStone(x, y, Stone::Empty);
            return true;
        }

        // 3 - diagonal direction (lower-left to upper-right: '/')
        nLine = 1;
        i = x;
        j = y;
        while ((i > 0) && (j > 0)) {
            if (cBoard[i--][j--] == Stone::White)
                nLine++;
            else
                break;
        }
        i = x + 2;
        j = y + 2;
        while ((i < (BoardSize + 1)) && (j < (BoardSize + 1))) {
            if (cBoard[i++][j++] == Stone::White)
                nLine++;
            else
                break;
        }
        if (nLine >= 5) {
            setStone(x, y, Stone::Empty);
            return true;
        }

        // 4 - diagonal direction (upper-left to lower-right: '\')
        nLine = 1;
        i = x;
        j = y + 2;
        while ((i > 0) && (j < (BoardSize + 1))) {
            if (cBoard[i--][j++] == Stone::White)
                nLine++;
            else
                break;
        }
        i = x + 2;
        j = y;
        while ((i < (BoardSize + 1)) && (j > 0)) {
            if (cBoard[i++][j--] == Stone::White)
                nLine++;
            else
                break;
        }
        if (nLine >= 5) {
            setStone(x, y, Stone::Empty);
            return true;
        }

        setStone(x, y, Stone::Empty);
        return false;
    } else
        return false;
}

bool ForbiddenPointFinder::isOverline(int x, int y) {
    if (cBoard[x + 1][y + 1] != Stone::Empty)
        return false;

    setStone(x, y, Stone::Black);

    // detect black overline
    int i, j;
    bool bOverline = false;

    // 1 - horizontal direction
    int nLine = 1;
    i = x;
    while (i > 0) {
        if (cBoard[i--][y + 1] == Stone::Black)
            nLine++;
        else
            break;
    }
    i = x + 2;
    while (i < (BoardSize + 1)) {
        if (cBoard[i++][y + 1] == Stone::Black)
            nLine++;
        else
            break;
    }
    if (nLine == 5) {
        setStone(x, y, Stone::Empty);
        return false;
    } else
        bOverline |= (nLine >= 6);

    // 2 - vertical direction
    nLine = 1;
    i = y;
    while (i > 0) {
        if (cBoard[x + 1][i--] == Stone::Black)
            nLine++;
        else
            break;
    }
    i = y + 2;
    while (i < (BoardSize + 1)) {
        if (cBoard[x + 1][i++] == Stone::Black)
            nLine++;
        else
            break;
    }
    if (nLine == 5) {
        setStone(x, y, Stone::Empty);
        return false;
    } else
        bOverline |= (nLine >= 6);

    // 3 - diagonal direction (lower-left to upper-right: '/')
    nLine = 1;
    i = x;
    j = y;
    while ((i > 0) && (j > 0)) {
        if (cBoard[i--][j--] == Stone::Black)
            nLine++;
        else
            break;
    }
    i = x + 2;
    j = y + 2;
    while ((i < (BoardSize + 1)) && (j < (BoardSize + 1))) {
        if (cBoard[i++][j++] == Stone::Black)
            nLine++;
        else
            break;
    }
    if (nLine == 5) {
        setStone(x, y, Stone::Empty);
        return false;
    } else
        bOverline |= (nLine >= 6);

    // 4 - diagonal direction (upper-left to lower-right: '\')
    nLine = 1;
    i = x;
    j = y + 2;
    while ((i > 0) && (j < (BoardSize + 1))) {
        if (cBoard[i--][j++] == Stone::Black)
            nLine++;
        else
            break;
    }
    i = x + 2;
    j = y;
    while ((i < (BoardSize + 1)) && (j > 0)) {
        if (cBoard[i++][j--] == Stone::Black)
            nLine++;
        else
            break;
    }
    if (nLine == 5) {
        setStone(x, y, Stone::Empty);
        return false;
    } else
        bOverline |= (nLine >= 6);

    setStone(x, y, Stone::Empty);
    return bOverline;
}

bool ForbiddenPointFinder::isFive(int x, int y, int nColor, int nDir) {
    if (cBoard[x + 1][y + 1] != Stone::Empty)
        return false;

    Stone c;
    if (nColor == 0)    // black
        c = Stone::Black;
    else if (nColor == 1)    // white
        c = Stone::White;
    else
        return false;

    setStone(x, y, c);

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
            while (i < (BoardSize + 1)) {
                if (cBoard[i++][y + 1] == c)
                    nLine++;
                else
                    break;
            }
            if (nLine == 5) {
                setStone(x, y, Stone::Empty);
                return true;
            } else {
                setStone(x, y, Stone::Empty);
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
            while (i < (BoardSize + 1)) {
                if (cBoard[x + 1][i++] == c)
                    nLine++;
                else
                    break;
            }
            if (nLine == 5) {
                setStone(x, y, Stone::Empty);
                return true;
            } else {
                setStone(x, y, Stone::Empty);
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
            while ((i < (BoardSize + 1)) && (j < (BoardSize + 1))) {
                if (cBoard[i++][j++] == c)
                    nLine++;
                else
                    break;
            }
            if (nLine == 5) {
                setStone(x, y, Stone::Empty);
                return true;
            } else {
                setStone(x, y, Stone::Empty);
                return false;
            }
            break;
        case 4:        // diagonal direction - '\'
            nLine = 1;
            i = x;
            j = y + 2;
            while ((i > 0) && (j < (BoardSize + 1))) {
                if (cBoard[i--][j++] == c)
                    nLine++;
                else
                    break;
            }
            i = x + 2;
            j = y;
            while ((i < (BoardSize + 1)) && (j > 0)) {
                if (cBoard[i++][j--] == c)
                    nLine++;
                else
                    break;
            }
            if (nLine == 5) {
                setStone(x, y, Stone::Empty);
                return true;
            } else {
                setStone(x, y, Stone::Empty);
                return false;
            }
            break;
        default:
            setStone(x, y, Stone::Empty);
            return false;
            break;
    }
}

bool ForbiddenPointFinder::isFour(int x, int y, int nColor, int nDir) {
    if (cBoard[x + 1][y + 1] != Stone::Empty)
        return false;

    if (isFive(x, y, nColor))    // five?
        return false;
    else if ((nColor == 0) && (isOverline(x, y)))    // black overline?
        return false;
    else {
        Stone c;
        if (nColor == 0)    // black
            c = Stone::Black;
        else if (nColor == 1)    // white
            c = Stone::White;
        else
            return false;

        setStone(x, y, c);

        int i, j;

        switch (nDir) {
            case 1:        // horizontal direction
                i = x;
                while (i > 0) {
                    if (cBoard[i][y + 1] == c) {
                        i--;
                        continue;
                    } else if (cBoard[i][y + 1] == Stone::Empty) {
                        if (isFive(i - 1, y, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = x + 2;
                while (i < (BoardSize + 1)) {
                    if (cBoard[i][y + 1] == c) {
                        i++;
                        continue;
                    } else if (cBoard[i][y + 1] == Stone::Empty) {
                        if (isFive(i - 1, y, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                setStone(x, y, Stone::Empty);
                return false;
                break;
            case 2:        // vertial direction
                i = y;
                while (i > 0) {
                    if (cBoard[x + 1][i] == c) {
                        i--;
                        continue;
                    } else if (cBoard[x + 1][i] == Stone::Empty) {
                        if (isFive(x, i - 1, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = y + 2;
                while (i < (BoardSize + 1)) {
                    if (cBoard[x + 1][i] == c) {
                        i++;
                        continue;
                    } else if (cBoard[x + 1][i] == Stone::Empty) {
                        if (isFive(x, i - 1, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                setStone(x, y, Stone::Empty);
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
                    } else if (cBoard[i][j] == Stone::Empty) {
                        if (isFive(i - 1, j - 1, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = x + 2;
                j = y + 2;
                while ((i < (BoardSize + 1)) && (j < (BoardSize + 1))) {
                    if (cBoard[i][j] == c) {
                        i++;
                        j++;
                        continue;
                    } else if (cBoard[i][j] == Stone::Empty) {
                        if (isFive(i - 1, j - 1, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                setStone(x, y, Stone::Empty);
                return false;
                break;
            case 4:        // diagonal direction - '\'
                i = x;
                j = y + 2;
                while ((i > 0) && (j < (BoardSize + 1))) {
                    if (cBoard[i][j] == c) {
                        i--;
                        j++;
                        continue;
                    } else if (cBoard[i][j] == Stone::Empty) {
                        if (isFive(i - 1, j - 1, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = x + 2;
                j = y;
                while ((i < (BoardSize + 1)) && (j > 0)) {
                    if (cBoard[i][j] == c) {
                        i++;
                        j--;
                        continue;
                    } else if (cBoard[i][j] == Stone::Empty) {
                        if (isFive(i - 1, j - 1, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                setStone(x, y, Stone::Empty);
                return false;
                break;
            default:
                setStone(x, y, Stone::Empty);
                return false;
                break;
        }
    }
}

int ForbiddenPointFinder::isOpenFour(int x, int y, int nColor, int nDir) {
    if (cBoard[x + 1][y + 1] != Stone::Empty)
        return 0;

    if (isFive(x, y, nColor))    // five?
        return 0;
    else if ((nColor == 0) && (isOverline(x, y)))    // black overline?
        return 0;
    else {
        Stone c;
        if (nColor == 0)    // black
            c = Stone::Black;
        else if (nColor == 1)    // white
            c = Stone::White;
        else
            return 0;

        setStone(x, y, c);

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
                    } else if (cBoard[i][y + 1] == Stone::Empty) {
                        if (!isFive(i - 1, y, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return 0;
                        } else
                            break;
                    } else {
                        setStone(x, y, Stone::Empty);
                        return 0;
                    }
                }
                i = x + 2;
                while (i < (BoardSize + 1)) {
                    if (cBoard[i][y + 1] == c) {
                        i++;
                        nLine++;
                        continue;
                    } else if (cBoard[i][y + 1] == Stone::Empty) {
                        if (isFive(i - 1, y, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return (nLine == 4 ? 1 : 2);
                        } else
                            break;
                    } else
                        break;
                }
                setStone(x, y, Stone::Empty);
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
                    } else if (cBoard[x + 1][i] == Stone::Empty) {
                        if (!isFive(x, i - 1, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return 0;
                        } else
                            break;
                    } else {
                        setStone(x, y, Stone::Empty);
                        return 0;
                    }
                }
                i = y + 2;
                while (i < (BoardSize + 1)) {
                    if (cBoard[x + 1][i] == c) {
                        i++;
                        nLine++;
                        continue;
                    } else if (cBoard[x + 1][i] == Stone::Empty) {
                        if (isFive(x, i - 1, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return (nLine == 4 ? 1 : 2);
                        } else
                            break;
                    } else
                        break;
                }
                setStone(x, y, Stone::Empty);
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
                    } else if (cBoard[i][j] == Stone::Empty) {
                        if (!isFive(i - 1, j - 1, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return 0;
                        } else
                            break;
                    } else {
                        setStone(x, y, Stone::Empty);
                        return 0;
                    }
                }
                i = x + 2;
                j = y + 2;
                while ((i < (BoardSize + 1)) && (j < (BoardSize + 1))) {
                    if (cBoard[i][j] == c) {
                        i++;
                        j++;
                        nLine++;
                        continue;
                    } else if (cBoard[i][j] == Stone::Empty) {
                        if (isFive(i - 1, j - 1, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return (nLine == 4 ? 1 : 2);
                        } else
                            break;
                    } else
                        break;
                }
                setStone(x, y, Stone::Empty);
                return 0;
                break;
            case 4:        // diagonal direction - '\'
                nLine = 1;
                i = x;
                j = y + 2;
                while ((i >= 0) && (j <= (BoardSize + 1))) {
                    if (cBoard[i][j] == c) {
                        i--;
                        j++;
                        nLine++;
                        continue;
                    } else if (cBoard[i][j] == Stone::Empty) {
                        if (!isFive(i - 1, j - 1, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return 0;
                        } else
                            break;
                    } else {
                        setStone(x, y, Stone::Empty);
                        return 0;
                    }
                }
                i = x + 2;
                j = y;
                while ((i < (BoardSize + 1)) && (j > 0)) {
                    if (cBoard[i][j] == c) {
                        i++;
                        j--;
                        nLine++;
                        continue;
                    } else if (cBoard[i][j] == Stone::Empty) {
                        if (isFive(i - 1, j - 1, 0, nDir)) {
                            setStone(x, y, Stone::Empty);
                            return (nLine == 4 ? 1 : 2);
                        } else
                            break;
                    } else
                        break;
                }
                setStone(x, y, Stone::Empty);
                return 0;
                break;
            default:
                setStone(x, y, Stone::Empty);
                return 0;
                break;
        }
    }
}

bool ForbiddenPointFinder::isDoubleFour(int x, int y) {
    if (cBoard[x + 1][y + 1] != Stone::Empty)
        return false;

    if (isFive(x, y, 0))    // five?
        return false;

    int nFour = 0;
    for (int i = 1; i <= 4; i++) {
        if (isOpenFour(x, y, 0, i) == 2)
            nFour += 2;
        else if (isFour(x, y, 0, i))
            nFour++;
    }

    if (nFour >= 2)
        return true;
    else
        return false;
}

bool ForbiddenPointFinder::isOpenThree(int x, int y, int nColor, int nDir) {
    if (isFive(x, y, nColor))    // five?
        return false;
    else if ((nColor == 0) && (isOverline(x, y)))    // black overline?
        return false;
    else {
        Stone c;
        if (nColor == 0)    // black
            c = Stone::Black;
        else if (nColor == 1)    // white
            c = Stone::White;
        else
            return false;

        setStone(x, y, c);

        int i, j;

        switch (nDir) {
            case 1:        // horizontal direction
                i = x;
                while (i > 0) {
                    if (cBoard[i][y + 1] == c) {
                        i--;
                        continue;
                    } else if (cBoard[i][y + 1] == Stone::Empty) {
                        if ((isOpenFour(i - 1, y, nColor, nDir) == 1) && (!isDoubleFour(i - 1, y)) &&
                            (!isDoubleThree(i - 1, y))) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = x + 2;
                while (i < (BoardSize + 1)) {
                    if (cBoard[i][y + 1] == c) {
                        i++;
                        continue;
                    } else if (cBoard[i][y + 1] == Stone::Empty) {
                        if ((isOpenFour(i - 1, y, nColor, nDir) == 1) && (!isDoubleFour(i - 1, y)) &&
                            (!isDoubleThree(i - 1, y))) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                setStone(x, y, Stone::Empty);
                return false;
                break;
            case 2:        // vertial direction
                i = y;
                while (i > 0) {
                    if (cBoard[x + 1][i] == c) {
                        i--;
                        continue;
                    } else if (cBoard[x + 1][i] == Stone::Empty) {
                        if ((isOpenFour(x, i - 1, nColor, nDir) == 1) && (!isDoubleFour(x, i - 1)) &&
                            (!isDoubleThree(x, i - 1))) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = y + 2;
                while (i < (BoardSize + 1)) {
                    if (cBoard[x + 1][i] == c) {
                        i++;
                        continue;
                    } else if (cBoard[x + 1][i] == Stone::Empty) {
                        if ((isOpenFour(x, i - 1, nColor, nDir) == 1) && (!isDoubleFour(x, i - 1)) &&
                            (!isDoubleThree(x, i - 1))) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                setStone(x, y, Stone::Empty);
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
                    } else if (cBoard[i][j] == Stone::Empty) {
                        if ((isOpenFour(i - 1, j - 1, nColor, nDir) == 1) && (!isDoubleFour(i - 1, j - 1)) &&
                            (!isDoubleThree(i - 1, j - 1))) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = x + 2;
                j = y + 2;
                while ((i < (BoardSize + 1)) && (j < (BoardSize + 1))) {
                    if (cBoard[i][j] == c) {
                        i++;
                        j++;
                        continue;
                    } else if (cBoard[i][j] == Stone::Empty) {
                        if ((isOpenFour(i - 1, j - 1, nColor, nDir) == 1) && (!isDoubleFour(i - 1, j - 1)) &&
                            (!isDoubleThree(i - 1, j - 1))) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                setStone(x, y, Stone::Empty);
                return false;
                break;
            case 4:        // diagonal direction - '\'
                i = x;
                j = y + 2;
                while ((i > 0) && (j < (BoardSize + 1))) {
                    if (cBoard[i][j] == c) {
                        i--;
                        j++;
                        continue;
                    } else if (cBoard[i][j] == Stone::Empty) {
                        if ((isOpenFour(i - 1, j - 1, nColor, nDir) == 1) && (!isDoubleFour(i - 1, j - 1)) &&
                            (!isDoubleThree(i - 1, j - 1))) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                i = x + 2;
                j = y;
                while ((i < (BoardSize + 1)) && (j > 0)) {
                    if (cBoard[i][j] == c) {
                        i++;
                        j--;
                        continue;
                    } else if (cBoard[i][j] == Stone::Empty) {
                        if ((isOpenFour(i - 1, j - 1, nColor, nDir) == 1) && (!isDoubleFour(i - 1, j - 1)) &&
                            (!isDoubleThree(i - 1, j - 1))) {
                            setStone(x, y, Stone::Empty);
                            return true;
                        } else
                            break;
                    } else
                        break;
                }
                setStone(x, y, Stone::Empty);
                return false;
                break;
            default:
                setStone(x, y, Stone::Empty);
                return false;
                break;
        }
    }
}

bool ForbiddenPointFinder::isDoubleThree(int x, int y) {
    if (cBoard[x + 1][y + 1] != Stone::Empty)
        return false;

    if (isFive(x, y, 0))    // five?
        return false;

    int nThree = 0;
    for (int i = 1; i <= 4; i++) {
        if (isOpenThree(x, y, 0, i))
            nThree++;
    }

    if (nThree >= 2)
        return true;
    else
        return false;
}

void ForbiddenPointFinder::findForbiddenPoints() {
    nForbiddenPoints = 0;
    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            if (cBoard[i + 1][j + 1] != Stone::Empty)
                continue;
            else {
                if (isOverline(i, j) || isDoubleFour(i, j) || isDoubleThree(i, j)) {
                    ptForbidden[nForbiddenPoints].x = i;
                    ptForbidden[nForbiddenPoints].y = j;
                    nForbiddenPoints++;
                }
            }
        }
    }
}