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

int N, mod = 10007;
int comb[53][53] = {};

void input()
{
    cin >> N;
}

ll solve()
{
    for (int i = 0; i <= 52; i++)
    {
        comb[i][0] = 1;
    }
    for (int i = 1; i <= 52; i++)
    {
        for (int j = 1; j <= 52; j++)
        {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
        }
    }

    int ans = 0;
    for (int i = 1; i <= 13 && N - 4 * i >= 0; i++)
    {
        if (i % 2 == 1)
            ans = (ans + comb[52 - 4 * i][N - 4 * i] * comb[13][i]) % mod;
        else
            ans = (ans - (comb[52 - 4 * i][N - 4 * i] * comb[13][i]) % mod + mod) % mod;
    }
    return ans;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}
/*
16565
*/