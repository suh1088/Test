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

vector<pair<int, int>> obj;
vector<vector<int>> dp;
int N, W;

int fill(int n, int w)
{
    if (n == 0)
    {
        if (w >= obj[n].first)
        {
            return obj[n].second;
        }
        else
        {
            return 0;
        }
    }

    if (w < obj[n].first)
    {
        return dp[w][n - 1];
    }
    else
    {
        return max(dp[w][n - 1], obj[n].second + dp[w - obj[n].first][n - 1]);
    }
}

int main(void)
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    cin >> N >> W;

    dp.resize(W + 1, vector<int>(N, 0));

    for (int i = 0; i < N; i++)
    {
        int a, b; // w and v
        cin >> a >> b;
        obj.push_back(make_pair(a, b));
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            dp[j][i] = fill(i, j);
        }
    }

    cout << dp[W][N - 1];
}

/*
12865
*/