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

int V;
vector<vector<pair<int, int>>> tree;
// vector<vector<int>> dist;
vector<int> totd;
int maxdist = 0;

void input()
{
    cin >> V;
    tree.resize(V + 1);
    // dist.resize(V + 1, vector<int>(V + 1));

    for (int i = 1; i <= V; i++)
    {
        int s;
        cin >> s;

        int to, d;
        while (1)
        {
            cin >> to;
            if (to == -1)
                break;

            cin >> d;
            tree[s].push_back(make_pair(to, d));
            // dist[s][to] = d;
        }
    }
}

int bfs(int st)
{ // return deepest node
    queue<int> q;
    q.push(st);
    int deepest;

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        for (pair i : tree[cur])
        {
            if (totd[i.first] == 0 && i.first != st)
            {
                q.push(i.first);
                totd[i.first] = totd[cur] + i.second;
                if (totd[i.first] > maxdist)
                {
                    deepest = i.first;
                    maxdist = totd[i.first];
                }
            }
        }
    }
    return deepest;
}

void solve()
{
    totd.resize(V + 1, 0);
    int st = bfs(1);

    for (int i = 0; i <= V; i++)
    {
        totd[i] = 0;
    }
    maxdist = 0;

    bfs(st);
    cout << maxdist;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    input();

    solve();
}
/*
1167

2차원 벡터 만들어 버리면 시간과 메모리 초과 가능성 높음.
간단한 지식 하나만으로 쉽게 풀리는 문제
*/