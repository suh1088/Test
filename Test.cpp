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

int N, M;
vector<int> par;
int Fcycle = 0;

int find(int a)
{ // return root
    if (par[a] == a)
    {
        return a;
    }
    else
    {
        return par[a] = find(par[a]);
    }
}

int uni(int a, int b)
{
    if (find(a) != find(b))
    {
        par[par[a]] = par[b];
    }

    return 0;
}

int input()
{
    cin >> N >> M;
    par.resize(N, 0);
    for (int i = 0; i < N; i++)
    {
        par[i] = i;
    }
    return 0;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    input();

    for (int i = 1; i <= M; i++)
    {
        int a, b;
        cin >> a >> b;

        if (find(a) == find(b) && Fcycle == 0)
        {
            Fcycle = i;
            // break;
        }
        else
        {
            uni(a, b);
        }
    }

    cout << Fcycle;
}

/*
20040

유니온 파인드 알면 별로 어렵진 않은데 실수한거 있어서 오래걸린듯
*/