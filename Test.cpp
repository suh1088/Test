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

// int fill(int row, int col, vector<vector<int>> v)
// {
//     if (row == 0 || col == 0)
//     {
//         return v[row][col] = 0;
//     }
//     else if (a[row] == b[col])
//     {
//         return v[row][col] = v[row - 1][col - 1] + 1;
//     }
//     else if (a[row] != b[col])
//     {
//         return v[row][col] = max(v[row][col - 1], v[row - 1][col]);
//     }
//     else
//     {
//         cout << "SOMETHING WRONG!!\n";
//         return -1;
//     }
// }

// int fill(int row, int col, vector<vector<int>> v)
// {
//     if (row == 0 || col == 0)
//     {
//         return 0;
//     }
//     else if (a[row] == b[col])
//     {
//         return v[row - 1][col - 1] + 1;
//     }
//     else if (a[row] != b[col])
//     {
//         return max(v[row][col - 1], v[row - 1][col]);
//     }
//     else
//     {
//         cout << "SOMETHING WRONG!!\n";
//         return -1;
//     }
// }

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