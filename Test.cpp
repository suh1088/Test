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

#define IMAX 0x7FFFFFFF

using namespace std;
typedef long long ll;

struct r
{
    int a, b, c;

    r(int a, int b, int c) : a(a), b(b), c(c) {};

    bool operator<(const r &other) const
    {
        return this->c > other.c;
    }
};

int N, M;
vector<int> p;
priority_queue<r> pq;
int cost = 0;
int mc = 0;

void input()
{
    cin >> N >> M;

    p.resize(N + 1, 0);

    for (int i = 0; i <= N; i++)
    {
        p[i] = i;
    }

    for (int i = 0; i < M; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        pq.push(r(a, b, c));
    }
}

int find(int a)
{
    if (p[a] == a)
    {
        return a;
    }
    return p[a] = find(p[a]);
}

int ss(int a, int b)
{
    return find(a) == find(b);
}

int uni(int a, int b)
{
    if (ss(a, b))
    {
        return 0;
    }
    else
    {
        p[find(a)] = find(b);
        return 1;
    }
}

void kruskal()
{

    while (!pq.empty())
    {
        r tmpr = pq.top();
        int a = tmpr.a;
        int b = tmpr.b;
        int c = tmpr.c;
        pq.pop();

        if (uni(a, b))
        {
            cost += c;
            if (mc < c)
            {
                mc = c;
            }
        }
    }

    cost -= mc;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    input();

    kruskal();

    cout << cost;
}

/*
1647

최소 스패닝 트리를 찾은 뒤에 가장 비싼 길을 제거?
*/