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

string a, b;

int main(void)
{

    cin >> a >> b;

    vector<vector<int>> v(a.size() + 1, vector<int>(b.size() + 1, 0));

    for (int i = 1; i <= a.size(); i++)
    {
        for (int j = 1; j <= b.size(); j++)
        {
            if (a[i - 1] == b[j - 1])
            {
                v[i][j] = v[i - 1][j - 1] + 1;
            }
            else if (a[i - 1] != b[j - 1])
            {
                v[i][j] = max(v[i][j - 1], v[i - 1][j]);
            }
            // last = fill(j, i, v);
            // v[j][i] = last;
        }
    }

    cout << v[a.size()][b.size()];
}

/*
9251 LCS

2차원 벡터 생성
위로
*/