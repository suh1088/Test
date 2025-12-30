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

int N, Midx = 0;
vector<int> prisum; // idx 번쨰 소수까지의 합
vector<int> pri;

void setpri()
{
    pri.resize(N + 1, 1);
    pri[0] = pri[1] = 0;

    for (int i = 2; i <= N; i++)
    {
        if (pri[i])
        {
            for (int j = 2; i * j <= N; j++)
            {
                pri[i * j] = 0;
            }
        }
    }
}

int chkpri(int n)
{
    return pri[n];
}

void input()
{
    cin >> N;
    prisum.push_back(0);
    setpri();
    for (int i = 2; i <= N; i++)
    {
        if (chkpri(i))
        {
            prisum.push_back(prisum.back() + i);
            Midx++;
        }
    }
}

int solve()
{
    int ans = 0;
    int l = 0;
    int r = 0;

    while (r <= Midx)
    {
        int tmp = prisum[r] - prisum[l];
        if (tmp == N)
        {
            ans++;
            l++;
        }

        else if (tmp > N)
        {
            l++;
        }
        else if (tmp < N)
        {
            r++;
        }
    }

    return ans;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    input();

    cout << solve();
}
/*
1644

에라토스테네스의 체 + 투 포인터
*/