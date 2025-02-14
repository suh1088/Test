#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <map>
#include <deque>
#include <set>

using namespace std;
typedef long long ll;

typedef struct cor
{
    cor(int a, int b, int c)
    {
        m = a;
        n = b;
        h = c;
    }
    int m;
    int n;
    int h;
} cor;

int m, n, h;
int unri = 0;
int box[111][111][111]; // m n h (가로, 세로, 높이)
queue<cor> riped;
int dm[6] = {-1, 1, 0, 0, 0, 0}; // 좌우 앞뒤 상하 (사실 알빠노긴 함 ㅋㅋ)
int dn[6] = {0, 0, -1, 1, 0, 0};
int dh[6] = {0, 0, 0, 0, 1, -1};

bool chkin(int M, int N, int H)
{
    if (M >= 0 && M < m && N >= 0 && N < n && H >= 0 && H < h)
        return true;
    else
        return false;
}

int bfs()
{
    int Max = 0;
    while (!riped.empty())
    {
        cor tmp = riped.front();
        riped.pop();
        for (int i = 0; i < 6; i++)
        {
            int M = tmp.m + dm[i];
            int N = tmp.n + dn[i];
            int H = tmp.h + dh[i];

            if (chkin(M, N, H))
            {
                if (box[M][N][H] == 0)
                {
                    box[M][N][H] = box[tmp.m][tmp.n][tmp.h] + 1;
                    Max = max(box[M][N][H], Max);
                    riped.push(cor(M, N, H));
                    unri--;
                }
            }
        }
    }
    return Max;
}

int main(void)
{

    cin >> m >> n >> h;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < m; k++)
            {
                int tmp;
                cin >> tmp;
                box[k][j][i] = tmp;
                if (tmp == 0)
                    unri++;
                else if (tmp == 1)
                    riped.push(cor(k, j, i));
            }
        }
    } // 입력 완!

    int sol = bfs();
    if (unri > 0)
    {
        cout << -1;
        return 0;
    }
    else if (sol == 0)
    {
        cout << sol;
    }
    else
        cout << sol - 1;
}

/*
7569

bfs 함수 내에 return 구문을 작성하지 않았는데, 함수 내의 while 구문에 illeagal instruction 에러가 뜸. 이유가 뭔지 모르겠음;;
*/