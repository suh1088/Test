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

int fill(int row, int col, vector<vector<int>> &v)
{
    if (row == 0 || col == 0)
    {
        return v[row][col] = 0;
    }
    else if (a[row] == b[col])
    {
        return v[row][col] = v[row - 1][col - 1] + 1;
    }
    else if (a[row] != b[col])
    {
        return v[row][col] = max(v[row][col - 1], v[row - 1][col]);
    }
    else
    {
        cout << "SOMETHING WRONG!!\n";
        return -1;
    }
}

int main(void)
{

    cin >> a >> b;

    vector<vector<int>> v(a.size() + 1, vector<int>(b.size() + 1, 0));

    v[0][0] = 0;

    int last = 0;
    for (int i = 0; i <= min(a.size(), b.size()); i++)
    {
        // 행 먼저
        for (int j = i; j <= b.size(); j++)
        {
            last = fill(j, i, v);
        }
        // 다음 가로
        for (int j = i + 1; j <= a.size(); j++)
        {
            last = fill(i, j, v);
        }
    }

    cout << last;
}

/*
9251 LCS

2차원 벡터 생성
위로
*/