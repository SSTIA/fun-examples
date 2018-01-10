
// ForbiddenPointFinder.cpp: implementation of the CForbiddenPointFinder class.
//
// Code written by: Wenzhe Lu
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "ForbiddenPointFinder.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CForbiddenPointFinder::CForbiddenPointFinder()
{
	Clear();
}

CForbiddenPointFinder::~CForbiddenPointFinder()
{
}

//////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////

void CForbiddenPointFinder::Clear()
{
	nForbiddenPoints = 0;

	for (int i=0; i<BOARDSIZE+2; i++)
	{
		cBoard[0][i] = '$';
		cBoard[(BOARDSIZE+1)][i] = '$';
		cBoard[i][0] = '$';
		cBoard[i][(BOARDSIZE+1)] = '$';
	}

	for (i=1; i<=BOARDSIZE; i++)
		for (int j=1; j<=BOARDSIZE; j++)
			cBoard[i][j] = EMPTYSTONE;
}

int CForbiddenPointFinder::AddStone(int x, int y, char cStone)
{
	int nResult = -1;

	if (cStone == BLACKSTONE)
	{
		if (IsFive(x, y, 0))
			nResult = BLACKFIVE;
		for (int i=0; i<nForbiddenPoints; i++)
		{
			if (ptForbidden[i] == CPoint(x,y))
				nResult = BLACKFORBIDDEN;
		}
	}
	else if (cStone == WHITESTONE)
	{
		if (IsFive(x, y, 1))
			nResult = WHITEFIVE;
	}
	
	cBoard[x+1][y+1] = cStone;
	if (nResult == -1)
		FindForbiddenPoints();
	else
		nForbiddenPoints = 0;
	return nResult;
}

void CForbiddenPointFinder::SetStone(int x, int y, char cStone)
{
	cBoard[x+1][y+1] = cStone;
}

BOOL CForbiddenPointFinder::IsFive(int x, int y, int nColor)
{
	if (cBoard[x+1][y+1] != EMPTYSTONE)
		return FALSE;

	if (nColor == 0)	// black
	{
		SetStone(x, y, BLACKSTONE);
		
		// detect black five
		int i, j;
		
		// 1 - horizontal direction
		int nLine = 1;
		i = x;
		while (i > 0)
		{
			if (cBoard[i--][y+1] == BLACKSTONE)
				nLine++;
			else
				break;
		}
		i = x+2;
		while (i < (BOARDSIZE+1))
		{
			if (cBoard[i++][y+1] == BLACKSTONE)
				nLine++;
			else
				break;
		}
		if (nLine == 5)
		{
			SetStone(x, y, EMPTYSTONE);
			return TRUE;
		}

		// 2 - vertical direction
		nLine = 1;
		i = y;
		while (i > 0)
		{
			if (cBoard[x+1][i--] == BLACKSTONE)
				nLine++;
			else
				break;
		}
		i = y+2;
		while (i < (BOARDSIZE+1))
		{
			if (cBoard[x+1][i++] == BLACKSTONE)
				nLine++;
			else
				break;
		}
		if (nLine == 5)
		{
			SetStone(x, y, EMPTYSTONE);
			return TRUE;
		}

		// 3 - diagonal direction (lower-left to upper-right: '/')
		nLine = 1;
		i = x;
		j = y;
		while ((i > 0) && (j > 0))
		{
			if (cBoard[i--][j--] == BLACKSTONE)
				nLine++;
			else
				break;
		}
		i = x+2;
		j = y+2;
		while ((i < (BOARDSIZE+1)) && (j < (BOARDSIZE+1)))
		{
			if (cBoard[i++][j++] == BLACKSTONE)
				nLine++;
			else
				break;
		}
		if (nLine == 5)
		{
			SetStone(x, y, EMPTYSTONE);
			return TRUE;
		}

		// 4 - diagonal direction (upper-left to lower-right: '\')
		nLine = 1;
		i = x;
		j = y+2;
		while ((i > 0) && (j < (BOARDSIZE+1)))
		{
			if (cBoard[i--][j++] == BLACKSTONE)
				nLine++;
			else
				break;
		}
		i = x+2;
		j = y;
		while ((i < (BOARDSIZE+1)) && (j > 0))
		{
			if (cBoard[i++][j--] == BLACKSTONE)
				nLine++;
			else
				break;
		}
		if (nLine == 5)
		{
			SetStone(x, y, EMPTYSTONE);
			return TRUE;
		}

		SetStone(x, y, EMPTYSTONE);
		return FALSE;
	}
	else if (nColor == 1)	// white
	{
		SetStone(x, y, WHITESTONE);
		
		// detect white five or more
		int i, j;
		
		// 1 - horizontal direction
		int nLine = 1;
		i = x;
		while (i > 0)
		{
			if (cBoard[i--][y+1] == WHITESTONE)
				nLine++;
			else
				break;
		}
		i = x+2;
		while (i < (BOARDSIZE+1))
		{
			if (cBoard[i++][y+1] == WHITESTONE)
				nLine++;
			else
				break;
		}
		if (nLine >= 5)
		{
			SetStone(x, y, EMPTYSTONE);
			return TRUE;
		}

		// 2 - vertical direction
		nLine = 1;
		i = y;
		while (i > 0)
		{
			if (cBoard[x+1][i--] == WHITESTONE)
				nLine++;
			else
				break;
		}
		i = y+2;
		while (i < (BOARDSIZE+1))
		{
			if (cBoard[x+1][i++] == WHITESTONE)
				nLine++;
			else
				break;
		}
		if (nLine >= 5)
		{
			SetStone(x, y, EMPTYSTONE);
			return TRUE;
		}

		// 3 - diagonal direction (lower-left to upper-right: '/')
		nLine = 1;
		i = x;
		j = y;
		while ((i > 0) && (j > 0))
		{
			if (cBoard[i--][j--] == WHITESTONE)
				nLine++;
			else
				break;
		}
		i = x+2;
		j = y+2;
		while ((i < (BOARDSIZE+1)) && (j < (BOARDSIZE+1)))
		{
			if (cBoard[i++][j++] == WHITESTONE)
				nLine++;
			else
				break;
		}
		if (nLine >= 5)
		{
			SetStone(x, y, EMPTYSTONE);
			return TRUE;
		}

		// 4 - diagonal direction (upper-left to lower-right: '\')
		nLine = 1;
		i = x;
		j = y+2;
		while ((i > 0) && (j < (BOARDSIZE+1)))
		{
			if (cBoard[i--][j++] == WHITESTONE)
				nLine++;
			else
				break;
		}
		i = x+2;
		j = y;
		while ((i < (BOARDSIZE+1)) && (j > 0))
		{
			if (cBoard[i++][j--] == WHITESTONE)
				nLine++;
			else
				break;
		}
		if (nLine >= 5)
		{
			SetStone(x, y, EMPTYSTONE);
			return TRUE;
		}

		SetStone(x, y, EMPTYSTONE);
		return FALSE;
	}
	else 
		return FALSE;
}

BOOL CForbiddenPointFinder::IsOverline(int x, int y)
{
	if (cBoard[x+1][y+1] != EMPTYSTONE)
		return FALSE;

	SetStone(x, y, BLACKSTONE);
		
	// detect black overline
	int i, j;
	BOOL bOverline = FALSE;
		
	// 1 - horizontal direction
	int nLine = 1;
	i = x;
	while (i > 0)
	{
		if (cBoard[i--][y+1] == BLACKSTONE)
			nLine++;
		else
			break;
	}
	i = x+2;
	while (i < (BOARDSIZE+1))
	{
		if (cBoard[i++][y+1] == BLACKSTONE)
			nLine++;
		else
			break;
	}
	if (nLine == 5)
	{
		SetStone(x, y, EMPTYSTONE);
		return FALSE;
	}
	else
		bOverline |= (nLine >= 6);
		
	// 2 - vertical direction
	nLine = 1;
	i = y;
	while (i > 0)
	{
		if (cBoard[x+1][i--] == BLACKSTONE)
			nLine++;
		else
			break;
	}
	i = y+2;
	while (i < (BOARDSIZE+1))
	{
		if (cBoard[x+1][i++] == BLACKSTONE)
			nLine++;
		else
			break;
	}
	if (nLine == 5)
	{
		SetStone(x, y, EMPTYSTONE);
		return FALSE;
	}
	else
		bOverline |= (nLine >= 6);

	// 3 - diagonal direction (lower-left to upper-right: '/')
	nLine = 1;
	i = x;
	j = y;
	while ((i > 0) && (j > 0))
	{
		if (cBoard[i--][j--] == BLACKSTONE)
			nLine++;
		else
			break;
	}
	i = x+2;
	j = y+2;
	while ((i < (BOARDSIZE+1)) && (j < (BOARDSIZE+1)))
	{
		if (cBoard[i++][j++] == BLACKSTONE)
			nLine++;
		else
			break;
	}
	if (nLine == 5)
	{
		SetStone(x, y, EMPTYSTONE);
		return FALSE;
	}
	else
		bOverline |= (nLine >= 6);

	// 4 - diagonal direction (upper-left to lower-right: '\')
	nLine = 1;
	i = x;
	j = y+2;
	while ((i > 0) && (j < (BOARDSIZE+1)))
	{
		if (cBoard[i--][j++] == BLACKSTONE)
			nLine++;
		else
			break;
	}
	i = x+2;
	j = y;
	while ((i < (BOARDSIZE+1)) && (j > 0))
	{
		if (cBoard[i++][j--] == BLACKSTONE)
			nLine++;
		else
			break;
	}
	if (nLine == 5)
	{
		SetStone(x, y, EMPTYSTONE);
		return FALSE;
	}
	else
		bOverline |= (nLine >= 6);

	SetStone(x, y, EMPTYSTONE);
	return bOverline;
}

BOOL CForbiddenPointFinder::IsFive(int x, int y, int nColor, int nDir)
{
	if (cBoard[x+1][y+1] != EMPTYSTONE)
		return FALSE;
	
	char c;
	if (nColor == 0)	// black
		c = BLACKSTONE;
	else if (nColor == 1)	// white
		c = WHITESTONE;
	else
		return FALSE;
		
	SetStone(x, y, c);

	int i, j;
	int nLine;
			
	switch (nDir)
	{
	case 1:		// horizontal direction
		nLine = 1;
		i = x;
		while (i > 0)
		{
			if (cBoard[i--][y+1] == c)
				nLine++;
			else
				break;
		}
		i = x+2;
		while (i < (BOARDSIZE+1))
		{
			if (cBoard[i++][y+1] == c)
				nLine++;
			else
				break;
		}
		if (nLine == 5)
		{
			SetStone(x, y, EMPTYSTONE);
			return TRUE;
		}
		else
		{
			SetStone(x, y, EMPTYSTONE);
			return FALSE;
		}
		break;
	case 2:		// vertial direction
		nLine = 1;
		i = y;
		while (i > 0)
		{
			if (cBoard[x+1][i--] == c)
				nLine++;
			else
				break;
		}
		i = y+2;
		while (i < (BOARDSIZE+1))
		{
			if (cBoard[x+1][i++] == c)
				nLine++;
			else
				break;
		}
		if (nLine == 5)
		{
			SetStone(x, y, EMPTYSTONE);
			return TRUE;
		}
		else
		{
			SetStone(x, y, EMPTYSTONE);
			return FALSE;
		}
		break;
	case 3:		// diagonal direction - '/'
		nLine = 1;
		i = x;
		j = y;
		while ((i > 0) && (j > 0))
		{
			if (cBoard[i--][j--] == c)
				nLine++;
			else
				break;
		}
		i = x+2;
		j = y+2;
		while ((i < (BOARDSIZE+1)) && (j < (BOARDSIZE+1)))
		{
			if (cBoard[i++][j++] == c)
				nLine++;
			else
				break;
		}
		if (nLine == 5)
		{
			SetStone(x, y, EMPTYSTONE);
			return TRUE;
		}
		else
		{
			SetStone(x, y, EMPTYSTONE);
			return FALSE;
		}
		break;
	case 4:		// diagonal direction - '\'
		nLine = 1;
		i = x;
		j = y+2;
		while ((i > 0) && (j < (BOARDSIZE+1)))
		{
			if (cBoard[i--][j++] == c)
				nLine++;
			else
				break;
		}
		i = x+2;
		j = y;
		while ((i < (BOARDSIZE+1)) && (j > 0))
		{
			if (cBoard[i++][j--] == c)
				nLine++;
			else
				break;
		}
		if (nLine == 5)
		{
			SetStone(x, y, EMPTYSTONE);
			return TRUE;
		}
		else
		{
			SetStone(x, y, EMPTYSTONE);
			return FALSE;
		}
		break;
	default:
		SetStone(x, y, EMPTYSTONE);
		return FALSE;
		break;
	}
}

BOOL CForbiddenPointFinder::IsFour(int x, int y, int nColor, int nDir)
{
	if (cBoard[x+1][y+1] != EMPTYSTONE)
		return FALSE;

	if (IsFive(x, y, nColor))	// five?
		return FALSE;
	else if ((nColor == 0) && (IsOverline(x, y)))	// black overline?
		return FALSE;
	else
	{
		char c;
		if (nColor == 0)	// black
			c = BLACKSTONE;
		else if (nColor == 1)	// white
			c = WHITESTONE;
		else
			return FALSE;
		
		SetStone(x, y, c);

		int i, j;
			
		switch (nDir)
		{
		case 1:		// horizontal direction
			i = x;
			while (i > 0)
			{
				if (cBoard[i][y+1] == c)
				{
					i--;
					continue;
				}
				else if (cBoard[i][y+1] == EMPTYSTONE)
				{
					if (IsFive(i-1, y, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else 
						break;
				}
				else
					break;
			}
			i = x+2;
			while (i < (BOARDSIZE+1))
			{
				if (cBoard[i][y+1] == c)
				{
					i++;
					continue;
				}
				else if (cBoard[i][y+1] == EMPTYSTONE)
				{
					if (IsFive(i-1, y, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, EMPTYSTONE);
			return FALSE;
			break;
		case 2:		// vertial direction
			i = y;
			while (i > 0)
			{
				if (cBoard[x+1][i] == c)
				{
					i--;
					continue;
				}
				else if (cBoard[x+1][i] == EMPTYSTONE)
				{
					if (IsFive(x, i-1, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else 
						break;
				}
				else
					break;
			}
			i = y+2;
			while (i < (BOARDSIZE+1))
			{
				if (cBoard[x+1][i] == c)
				{
					i++;
					continue;
				}
				else if (cBoard[x+1][i] == EMPTYSTONE)
				{
					if (IsFive(x, i-1, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, EMPTYSTONE);
			return FALSE;
			break;
		case 3:		// diagonal direction - '/'
			i = x;
			j = y;
			while ((i > 0) && (j > 0))
			{
				if (cBoard[i][j] == c)
				{
					i--;
					j--;
					continue;
				}
				else if (cBoard[i][j] == EMPTYSTONE)
				{
					if (IsFive(i-1, j-1, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else 
						break;
				}
				else
					break;
			}
			i = x+2;
			j = y+2;
			while ((i < (BOARDSIZE+1)) && (j < (BOARDSIZE+1)))
			{
				if (cBoard[i][j] == c)
				{
					i++;
					j++;
					continue;
				}
				else if (cBoard[i][j] == EMPTYSTONE)
				{
					if (IsFive(i-1, j-1, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, EMPTYSTONE);
			return FALSE;
			break;
		case 4:		// diagonal direction - '\'
			i = x;
			j = y+2;
			while ((i > 0) && (j < (BOARDSIZE+1)))
			{
				if (cBoard[i][j] == c)
				{
					i--;
					j++;
					continue;
				}
				else if (cBoard[i][j] == EMPTYSTONE)
				{
					if (IsFive(i-1, j-1, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else 
						break;
				}
				else
					break;
			}
			i = x+2;
			j = y;
			while ((i < (BOARDSIZE+1)) && (j > 0))
			{
				if (cBoard[i][j] == c)
				{
					i++;
					j--;
					continue;
				}
				else if (cBoard[i][j] == EMPTYSTONE)
				{
					if (IsFive(i-1, j-1, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, EMPTYSTONE);
			return FALSE;
			break;
		default:
			SetStone(x, y, EMPTYSTONE);
			return FALSE;
			break;
		}
	}
}

int CForbiddenPointFinder::IsOpenFour(int x, int y, int nColor, int nDir)
{
	if (cBoard[x+1][y+1] != EMPTYSTONE)
		return 0;
	
	if (IsFive(x, y, nColor))	// five?
		return 0;
	else if ((nColor == 0) && (IsOverline(x, y)))	// black overline?
		return 0;
	else
	{
		char c;
		if (nColor == 0)	// black
			c = BLACKSTONE;
		else if (nColor == 1)	// white
			c = WHITESTONE;
		else
			return 0;
		
		SetStone(x, y, c);

		int i, j;
		int nLine;
			
		switch (nDir)
		{
		case 1:		// horizontal direction
			nLine = 1;
			i = x;
			while (i >= 0)
			{
				if (cBoard[i][y+1] == c)
				{
					i--;
					nLine++;
					continue;
				}
				else if (cBoard[i][y+1] == EMPTYSTONE)
				{
					if (!IsFive(i-1, y, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return 0;
					}
					else 
						break;
				}
				else
				{
					SetStone(x, y, EMPTYSTONE);
					return 0;
				}
			}
			i = x+2;
			while (i < (BOARDSIZE+1))
			{
				if (cBoard[i][y+1] == c)
				{
					i++;
					nLine++;
					continue;
				}
				else if (cBoard[i][y+1] == EMPTYSTONE)
				{
					if (IsFive(i-1, y, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return (nLine==4 ? 1 : 2);
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, EMPTYSTONE);
			return 0;
			break;
		case 2:		// vertial direction
			nLine = 1;
			i = y;
			while (i >= 0)
			{
				if (cBoard[x+1][i] == c)
				{
					i--;
					nLine++;
					continue;
				}
				else if (cBoard[x+1][i] == EMPTYSTONE)
				{
					if (!IsFive(x, i-1, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return 0;
					}
					else 
						break;
				}
				else
				{
					SetStone(x, y, EMPTYSTONE);
					return 0;
				}
			}
			i = y+2;
			while (i < (BOARDSIZE+1))
			{
				if (cBoard[x+1][i] == c)
				{
					i++;
					nLine++;
					continue;
				}
				else if (cBoard[x+1][i] == EMPTYSTONE)
				{
					if (IsFive(x, i-1, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return (nLine==4 ? 1 : 2);
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, EMPTYSTONE);
			return 0;
			break;
		case 3:		// diagonal direction - '/'
			nLine = 1;
			i = x;
			j = y;
			while ((i >= 0) && (j >= 0))
			{
				if (cBoard[i][j] == c)
				{
					i--;
					j--;
					nLine++;
					continue;
				}
				else if (cBoard[i][j] == EMPTYSTONE)
				{
					if (!IsFive(i-1, j-1, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return 0;
					}
					else 
						break;
				}
				else
				{
					SetStone(x, y, EMPTYSTONE);
					return 0;
				}
			}
			i = x+2;
			j = y+2;
			while ((i < (BOARDSIZE+1)) && (j < (BOARDSIZE+1)))
			{
				if (cBoard[i][j] == c)
				{
					i++;
					j++;
					nLine++;
					continue;
				}
				else if (cBoard[i][j] == EMPTYSTONE)
				{
					if (IsFive(i-1, j-1, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return (nLine==4 ? 1 : 2);
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, EMPTYSTONE);
			return 0;
			break;
		case 4:		// diagonal direction - '\'
			nLine = 1;
			i = x;
			j = y+2;
			while ((i >= 0) && (j <= (BOARDSIZE+1)))
			{
				if (cBoard[i][j] == c)
				{
					i--;
					j++;
					nLine++;
					continue;
				}
				else if (cBoard[i][j] == EMPTYSTONE)
				{
					if (!IsFive(i-1, j-1, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return 0;
					}
					else 
						break;
				}
				else
				{
					SetStone(x, y, EMPTYSTONE);
					return 0;
				}
			}
			i = x+2;
			j = y;
			while ((i < (BOARDSIZE+1)) && (j > 0))
			{
				if (cBoard[i][j] == c)
				{
					i++;
					j--;
					nLine++;
					continue;
				}
				else if (cBoard[i][j] == EMPTYSTONE)
				{
					if (IsFive(i-1, j-1, 0, nDir))
					{
						SetStone(x, y, EMPTYSTONE);
						return (nLine==4 ? 1 : 2);
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, EMPTYSTONE);
			return 0;
			break;
		default:
			SetStone(x, y, EMPTYSTONE);
			return 0;
			break;
		}
	}
}

BOOL CForbiddenPointFinder::IsDoubleFour(int x, int y)
{
	if (cBoard[x+1][y+1] != EMPTYSTONE)
		return FALSE;

	if (IsFive(x, y, 0))	// five?
		return FALSE;
	
	int nFour = 0;
	for (int i=1; i<=4; i++)
	{
		if (IsOpenFour(x, y, 0, i) == 2)
			nFour += 2;
		else if (IsFour(x, y, 0, i))
			nFour++;
	}

	if (nFour >= 2)
		return TRUE;
	else
		return FALSE;
}

BOOL CForbiddenPointFinder::IsOpenThree(int x, int y, int nColor, int nDir)
{
	if (IsFive(x, y, nColor))	// five?
		return FALSE;
	else if ((nColor == 0) && (IsOverline(x, y)))	// black overline?
		return FALSE;
	else
	{
		char c;
		if (nColor == 0)	// black
			c = BLACKSTONE;
		else if (nColor == 1)	// white
			c = WHITESTONE;
		else
			return FALSE;
		
		SetStone(x, y, c);

		int i, j;
			
		switch (nDir)
		{
		case 1:		// horizontal direction
			i = x;
			while (i > 0)
			{
				if (cBoard[i][y+1] == c)
				{
					i--;
					continue;
				}
				else if (cBoard[i][y+1] == EMPTYSTONE)
				{
					if ((IsOpenFour(i-1, y, nColor, nDir) == 1) && (!IsDoubleFour(i-1, y)) && (!IsDoubleThree(i-1, y)))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else 
						break;
				}
				else
					break;
			}
			i = x+2;
			while (i < (BOARDSIZE+1))
			{
				if (cBoard[i][y+1] == c)
				{
					i++;
					continue;
				}
				else if (cBoard[i][y+1] == EMPTYSTONE)
				{
					if ((IsOpenFour(i-1, y, nColor, nDir) == 1) && (!IsDoubleFour(i-1, y)) && (!IsDoubleThree(i-1, y)))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, EMPTYSTONE);
			return FALSE;
			break;
		case 2:		// vertial direction
			i = y;
			while (i > 0)
			{
				if (cBoard[x+1][i] == c)
				{
					i--;
					continue;
				}
				else if (cBoard[x+1][i] == EMPTYSTONE)
				{
					if ((IsOpenFour(x, i-1, nColor, nDir) == 1) && (!IsDoubleFour(x, i-1)) && (!IsDoubleThree(x, i-1)))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else 
						break;
				}
				else
					break;
			}
			i = y+2;
			while (i < (BOARDSIZE+1))
			{
				if (cBoard[x+1][i] == c)
				{
					i++;
					continue;
				}
				else if (cBoard[x+1][i] == EMPTYSTONE)
				{
					if ((IsOpenFour(x, i-1, nColor, nDir) == 1) && (!IsDoubleFour(x, i-1)) && (!IsDoubleThree(x, i-1)))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, EMPTYSTONE);
			return FALSE;
			break;
		case 3:		// diagonal direction - '/'
			i = x;
			j = y;
			while ((i > 0) && (j > 0))
			{
				if (cBoard[i][j] == c)
				{
					i--;
					j--;
					continue;
				}
				else if (cBoard[i][j] == EMPTYSTONE)
				{
					if ((IsOpenFour(i-1, j-1, nColor, nDir) == 1) && (!IsDoubleFour(i-1, j-1)) && (!IsDoubleThree(i-1, j-1)))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else 
						break;
				}
				else
					break;
			}
			i = x+2;
			j = y+2;
			while ((i < (BOARDSIZE+1)) && (j < (BOARDSIZE+1)))
			{
				if (cBoard[i][j] == c)
				{
					i++;
					j++;
					continue;
				}
				else if (cBoard[i][j] == EMPTYSTONE)
				{
					if ((IsOpenFour(i-1, j-1, nColor, nDir) == 1) && (!IsDoubleFour(i-1, j-1)) && (!IsDoubleThree(i-1, j-1)))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, EMPTYSTONE);
			return FALSE;
			break;
		case 4:		// diagonal direction - '\'
			i = x;
			j = y+2;
			while ((i > 0) && (j < (BOARDSIZE+1)))
			{
				if (cBoard[i][j] == c)
				{
					i--;
					j++;
					continue;
				}
				else if (cBoard[i][j] == EMPTYSTONE)
				{
					if ((IsOpenFour(i-1, j-1, nColor, nDir) == 1) && (!IsDoubleFour(i-1, j-1)) && (!IsDoubleThree(i-1, j-1)))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else 
						break;
				}
				else
					break;
			}
			i = x+2;
			j = y;
			while ((i < (BOARDSIZE+1)) && (j > 0))
			{
				if (cBoard[i][j] == c)
				{
					i++;
					j--;
					continue;
				}
				else if (cBoard[i][j] == EMPTYSTONE)
				{
					if ((IsOpenFour(i-1, j-1, nColor, nDir) == 1) && (!IsDoubleFour(i-1, j-1)) && (!IsDoubleThree(i-1, j-1)))
					{
						SetStone(x, y, EMPTYSTONE);
						return TRUE;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, EMPTYSTONE);
			return FALSE;
			break;
		default:
			SetStone(x, y, EMPTYSTONE);
			return FALSE;
			break;
		}
	}
}

BOOL CForbiddenPointFinder::IsDoubleThree(int x, int y)
{
	if (cBoard[x+1][y+1] != EMPTYSTONE)
		return FALSE;

	if (IsFive(x, y, 0))	// five?
		return FALSE;
	
	int nThree = 0;
	for (int i=1; i<=4; i++)
	{
		if (IsOpenThree(x, y, 0, i))
			nThree++;
	}

	if (nThree >= 2)
		return TRUE;
	else
		return FALSE;
}

void CForbiddenPointFinder::FindForbiddenPoints()
{
	nForbiddenPoints = 0;
	for (int i=0; i<BOARDSIZE; i++)
	{
		for (int j=0; j<BOARDSIZE; j++)
		{
			if (cBoard[i+1][j+1] != EMPTYSTONE)
				continue;
			else
			{
				if (IsOverline(i, j) || IsDoubleFour(i, j) || IsDoubleThree(i, j))
				{
					ptForbidden[nForbiddenPoints].x = i;
					ptForbidden[nForbiddenPoints].y = j;
					nForbiddenPoints++;
				}
			}
		}
	}
}