#include <iostream>
#include <vector>

#define WIDTH (8)

using namespace std;

struct Move
{
    int score = -1;
    int y, x;   // 기준 좌표
    int ay, ax; // 인접 좌표
    int dir;    // 0: 오른쪽, 1: 위쪽
};

vector<vector<int>> ypos(8, vector<int>(8, 0));
int nextDepth[8] = {8, 8, 8, 8, 8, 8, 8, 8};
int score[9] = {0, 0, 0, 1, 4, 9, 9, 9, 9};
int mRet[5] = {-1, -1, -1, -1, -1};
Move MaxMove;

int (*mTiles)[WIDTH] = nullptr;

int v(int x, int y)
{
    return ypos[y][x];
}

void init(int N, int Tiles[][WIDTH])
{
    mTiles = Tiles;
    for (int i = 0; i < 8; i++)
    {
        nextDepth[i] = 8;
        for (int j = 0; j < 8; j++)
        {
            ypos[i][j] = Tiles[i][j];
        }
    }
}

void swapYpos(int x1, int y1, int x2, int y2)
{ // 반드시 되돌려놓을 것
    int tmp = ypos[y1][x1];
    ypos[y1][x1] = ypos[y2][x2];
    ypos[y2][x2] = tmp;
}

int calcScore(bool marked[8][8])
{
    int totScore = 0;
    // 가로
    for (int y = 0; y < 8; y++)
    {
        int s_idx = -1;
        for (int x = 0; x < 8; x++)
        {
            if (s_idx < 0 && marked[y][x])
            {
                s_idx = x;
            }

            else if (s_idx >= 0)
            {
                // 길이 늘리기
                if (marked[y][x] && (v(x, y) == v(s_idx, y)))
                {
                    if (x == 7)
                    {
                        totScore += score[x - s_idx + 1];
                    }
                    continue;
                }

                // 중단
                else if (!marked[y][x])
                {
                    totScore += score[x - s_idx];
                    s_idx = -1;
                }

                // 다른 라인
                else if (marked[y][x] && (v(x, y) != v(s_idx, y)))
                {
                    totScore += score[x - s_idx];
                    s_idx = x;
                }
            }
        }
    }

    // 세로
    for (int x = 0; x < 8; x++)
    {
        int s_idx = -1;
        for (int y = 0; y < 8; y++)
        {
            if (s_idx < 0 && marked[y][x])
            {
                s_idx = y;
            }

            else if (s_idx >= 0)
            {
                // 길이 늘리기
                if (marked[y][x] && (v(x, y) == v(x, s_idx)))
                {
                    if (y == 7)
                    {
                        totScore += score[y - s_idx + 1];
                    }
                    continue;
                }

                // 중단
                else if (!marked[y][x])
                {
                    totScore += score[y - s_idx];
                    s_idx = -1;
                }

                // 다른 라인
                else if (marked[y][x] && (v(x, y) != v(x, s_idx)))
                {
                    totScore += score[y - s_idx];
                    s_idx = y;
                }
            }
        }
    }

    return totScore;
}

bool marking(bool marked[8][8])
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            marked[i][j] = false;

    bool hasMatch = false;

    // 가로
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x <= 5; x++)
        {
            if (v(x, y) == v(x + 1, y) && v(x, y) == v(x + 2, y))
            {
                marked[y][x] = marked[y][x + 1] = marked[y][x + 2] = true;
                hasMatch = true;
            }
        }
    }

    // 세로
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y <= 5; y++)
        {
            if (v(x, y) == v(x, y + 1) && v(x, y) == v(x, y + 2))
            {
                marked[y][x] = marked[y + 1][x] = marked[y + 2][x] = true;
                hasMatch = true;
            }
        }
    }

    return hasMatch;
}

bool canMakeMove()
{
    bool ret = false;
    bool marked[8][8];

    MaxMove.score = -1;

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            bool flag = false;
            if (y == 7 && x == 7)
                continue;

            // 오른
            if (x <= 6)
            {
                swapYpos(x, y, x + 1, y);
                flag = marking(marked);
                ret |= flag;
                int tmpScore = calcScore(marked);
                if (flag && MaxMove.score < tmpScore)
                {
                    MaxMove.score = tmpScore;
                    MaxMove.x = x;
                    MaxMove.y = y;
                    MaxMove.ax = x + 1;
                    MaxMove.ay = y;
                }
                swapYpos(x, y, x + 1, y);
            }

            // 위
            if (y <= 6)
            {
                swapYpos(x, y, x, y + 1);
                flag = marking(marked);
                ret |= flag;
                int tmpScore = calcScore(marked);
                if (flag && MaxMove.score < tmpScore)
                {
                    MaxMove.score = tmpScore;
                    MaxMove.x = x;
                    MaxMove.y = y;
                    MaxMove.ax = x;
                    MaxMove.ay = y + 1;
                }
                swapYpos(x, y, x, y + 1);
            }
        }
    }
    return ret;
}

void tilePop(bool marked[8][8])
{
    for (int x = 0; x < 8; x++)
    {
        int writeY = 0;
        for (int readY = 0; readY < 8; readY++)
        {
            if (!marked[readY][x])
            {
                ypos[writeY][x] = ypos[readY][x];
                writeY++;
            }
        }
        while (writeY < 8)
        {
            ypos[writeY][x] = mTiles[nextDepth[x]++][x];
            writeY++;
        }
    }
}

int move()
{
    if (MaxMove.score == -1)
    {
        // cout << "cannot move in turn\n"; // remove before flight
        return -1;
    }

    swapYpos(MaxMove.x, MaxMove.y, MaxMove.ax, MaxMove.ay);
    int totScore = 0;
    bool marked[8][8];

    // 연쇄 삭제
    while (marking(marked))
    {
        totScore += calcScore(marked);
        tilePop(marked);
    }

    return totScore;
}

void makeReady()
{
    bool marked[8][8];

    while (marking(marked))
    {
        // cout << "tile pop in makeReady\n";
        tilePop(marked);
    }

    while (!canMakeMove())
    {
        // cout << "All tile poped in makeReady\n";
        for (int x = 0; x < 8; x++)
            for (int y = 0; y < 8; y++)
                marked[y][x] = true;

        tilePop(marked);

        while (marking(marked))
        {
            tilePop(marked);
        }
    }
}

int *takeTurn()
{
    MaxMove = {-1, -1, -1, -1, -1};
    makeReady();

    mRet[0] = move();
    mRet[1] = MaxMove.y;
    mRet[2] = MaxMove.x;
    mRet[3] = MaxMove.ay;
    mRet[4] = MaxMove.ax;

    // for (int i = 0; i < 5; i++)
    // {
    //     cout << mRet[i] << " ";
    // }
    // cout << endl;
    return mRet;
}
