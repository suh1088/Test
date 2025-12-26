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

int N;
vector<vector<int>> plate;
map<int, bool> av1; // 차 일정
map<int, bool> av2; // 합 일정
vector<int> best(2, 0);

bool chk(int x, int y)
{
    bool tmp = true;
    if (x < 0 || x >= N)
        tmp = false;
    if (y < 0 || y >= N)
        tmp = false;
    return tmp;
}

int sol(int dia, int bish, int col)
{

    if (dia > N * 2 - 1)
    {
        best[col] = max(bish, best[col]);
        return bish;
    } // ending

    int x, y;
    if (dia < N)
    {
        x = dia;
        y = 0;
    }
    else
    {
        x = N - 1;
        y = dia - N + 1;
    } // find first pos

    while (chk(x, y))
    {

        if (plate[x][y] == 1 && av1[x - y] && av2[x + y])
        {
            plate[x][y] = 2;
            av1[x - y] = false;
            av2[x + y] = false;

            sol(dia + 2, bish + 1, col);

            plate[x][y] = 1;
            av1[x - y] = true;
            av2[x + y] = true;
        }

        x--;
        y++;
    }
    // 배치하지 않고 넘어가는 경우
    sol(dia + 2, bish, col);

    return bish;
}

int main(void)
{
    // ios::sync_with_stdio(false);
    // cin.tie(NULL);

    // cin >> N;
    plate.resize(N, vector<int>(N));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> plate[i][j];
            av1[i - j] = true;
            av2[i + j] = true;
        }
    }

    // sol(0,0)
    sol(0, 0, 0);
    sol(1, 0, 1);
    cout << best[0] + best[1];
}