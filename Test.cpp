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

int N;
vector<int> p(501);
vector<vector<int>> dp(501, vector<int>(501, IMAX));

int input()
{
    cin >> N;
    int a;
    for (int i = 0; i < N; i++)
    {
        cin >> p[i];
        cin >> a;
    }
    p[N] = a;

    for (int i = 0; i <= 500; i++)
    {
        dp[i][i] = 0;
    }
    return 0;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    input();

    for (int l = 2; l <= N; l++)
    {
        for (int i = 0; i < N - l + 1; i++)
        {
            int j = i + l - 1;

            for (int k = i; k < j; k++)
            {
                // Ai~Ak * Ak+1~Aj
                int tmp = dp[i][k] + dp[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (dp[i][j] > tmp)
                {
                    dp[i][j] = tmp;
                }
            }
        }
    }

    cout << dp[0][N - 1];
}

/*
11049

학교에서 배운 dp 문제

*/