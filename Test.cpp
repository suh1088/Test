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

int N, M, K;
vector<int> par;
vector<int> card;
vector<int> prin;

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
    else if (a > b)
    {
        par[b] = a;
    }
    else if (a < b)
    {
        par[a] = b;
    }
}

void input()
{
    cin >> N >> M >> K;

    par.resize(N + 1, -1);
    for (int i = 0; i < M; i++)
    {
        int c;
        cin >> c;

        par[c] = c;
        card.push_back(c);
    }

    sort(card.begin(), card.end());
    int s = 0;
    for (int i : card)
    {
        for (int j = s; j < i; j++)
        {
            par[j] = i;
        }
        s = i + 1;
    }
    par[s] = s;

    for (int i = 0; i < K; i++)
    {
        int c;
        cin >> c;

        int out = find(c + 1);
        prin.push_back(out);
        uni(out, out + 1);
    }
}

void solve()
{
    for (int i : prin)
    {
        cout << i << "\n";
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
16566

= 랑 == 혼동 주의
유니온 파인드 아이디어만 떠올리면 쉬운 문제인데 구현 과정에서 실수가 너무 많다
*/