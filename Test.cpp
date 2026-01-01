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
#include <iomanip>

#define IMAX 0x7FFFFFFF

using namespace std;
typedef long long ll;

int N, M, ans;
vector<vector<int>> dm; // U D R L
vector<int> par;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {-1, 1, 0, 0};

int find(int a)
{
    if (par[a] == a)
    {
        return a;
    }
    return par[a] = find(par[a]);
}

void uni(int a_, int b_)
{
    int a = find(a_);
    int b = find(b_);
    if (a == b)
    {
        return;
    }
    par[a] = b;
    ans--;
}

int idx(int r, int c)
{
    return r * M + c;
}

void input()
{
    cin >> N >> M;
    dm.resize(N, vector<int>(M, 0));
    par.resize(N * M);
    ans = N * M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            char c;
            cin >> c;
            switch (c)
            {
            case 'U':
                dm[i][j] = 0;
                break;
            case 'D':
                dm[i][j] = 1;
                break;
            case 'R':
                dm[i][j] = 2;
                break;
            case 'L':
                dm[i][j] = 3;
                break;
            }
        }
    }

    for (int i = 0; i < N * M; i++)
    {
        par[i] = i;
    }
}

void solve()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            uni(idx(i, j), idx(i + dy[dm[i][j]], j + dx[dm[i][j]]));
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    input();

    solve();

    cout << ans;
}
/*
16724

구현은 간단하지만 약간의 발상이 필요한 문제
*/