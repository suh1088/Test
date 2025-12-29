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

int N, M;
vector<int> ind;
vector<vector<int>> deg;
priority_queue<int, vector<int>, greater<int>> pq;

void input()
{
    cin >> N >> M;

    ind.resize(N + 1, 0);
    deg.resize(N + 1);

    for (int i = 0; i < M; ++i)
    {
        int a, b;
        cin >> a >> b;
        ind[b]++;
        deg[a].push_back(b);
    }

    for (int i = 1; i <= N; i++)
    {
        if (ind[i] == 0)
        {
            pq.push(i);
        }
    }
}

void solve()
{
    while (!pq.empty())
    {
        int sol = pq.top();
        pq.pop();

        ind[sol] = -1;

        cout << sol << " ";

        for (int i : deg[sol])
        {
            ind[i]--;
            if (ind[i] == 0)
            {
                pq.push(i);
            }
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    input();

    solve();
}
/*
1766

위상정렬만 사용하면 간단하게 풀리는 문제, 대체 왜 골드2인지 의문.
*/