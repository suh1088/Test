#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <map>

using namespace std;
typedef long long ll;

vector<int> ppl(51); // [num] , group, truth

int find(int a)
{
    if (a != ppl[a])
    {
        return ppl[a] = find(ppl[a]);
    }
    return ppl[a];
}

void merge(int a, int b)
{
    int x = find(a);
    int y = find(b);

    if (x != y)
    {
        if (x < y)
        {
            ppl[y] = x;
        }
        else
        {
            ppl[x] = y;
        }
    }
}

int main()
{
    std::cin.tie(0);
    std::ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        ppl[i] = i;
    }

    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int tmp;
        cin >> tmp;
        ppl[tmp] = 0;
    } // 2nd line end

    vector<int> pty;

    for (int i = 0; i < m; i++)
    {
        int ptppl, prev = 0, now = 0;
        cin >> ptppl >> prev;

        pty.push_back(prev);

        for (int j = 1; j < ptppl; j++)
        {
            cin >> now;
            merge(prev, now);
            prev = now;
        }
    }

    int ans = m;
    for (int i = 0; i < m; i++)
    {
        if (find(pty[i]) == 0)
        {
            ans--;
        }
    }

    cout << ans;
}
/*
1043
진실 공동체를 그룹으로 분류함
만약 그룹에서 진실을 아는 사람이 적어도 한명 있으면 전부 진실
모든 그룹원이 진실을 모른다면 전부 거짓짓
*/