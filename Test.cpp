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

typedef struct cord
{
    int r;
    int c;
    cord(int row, int col)
    {
        r = row;
        c = col;
    }
} cord;

int n, m;
cord st(0, 0);
vector<vector<int>> v;
vector<vector<int>> sol;
queue<cord> que;
int dr[4] = {1, 0, -1, 0};
int dc[4] = {0, 1, 0, -1};

bool chkin(int r, int c)
{
    if (r < n && r >= 0 && c < m && c >= 0 && v[r][c] == 1 && sol[r][c] == 0)
        return true;
    else
        return false;
}

void bfs()
{
    while (!que.empty())
    {
        cord tmp = que.front();
        que.pop();
        int k = 4;
        while (k--)
        {
            int nr = tmp.r + dr[k];
            int nc = tmp.c + dc[k];

            if (chkin(nr, nc))
            {
                sol[nr][nc] = sol[tmp.r][tmp.c] + 1;
                que.push(cord(nr, nc));
            }
        }
    }
}

int main(void)
{
    cin >> n >> m;
    v.resize(n, vector<int>(m, 0));
    sol.resize(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int tmp;
            cin >> tmp;
            v[i][j] = tmp;
            if (tmp == 2)
            {
                st = cord(i, j);
            }
        }
    }

    que.push(st);
    bfs();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (v[i][j] == 1 && sol[i][j] == 0)
            {
                cout << "-1 ";
            }
            else
                cout << sol[i][j] << " ";
        }
        cout << endl;
    }
}

/*
14940

 0은 갈 수 없는 땅이고 1은 갈 수 있는 땅, 2는 목표지점이다. 입력에서 2는 단 한개이다.

 원래 갈 수 있는 땅인 부분 중에서 도달할 수 없는 위치는 -1을 출력한다.
*/