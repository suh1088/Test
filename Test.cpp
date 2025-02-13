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

typedef struct cor
{
    cor(int a, int b)
    {
        r = a;
        c = b;
    }
    int r;
    int c;
} cor;

int main(void)
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> box(n, vector<int>(m, 0));
    vector<cor> riped;

    int unriped = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> box[i][j];
            if (box[i][j] == 1)
                riped.push_back(cor(i, j));
            else if (box[i][j] == 0)
                unriped++;
        }
    }
}

/*
7576

토마토가 들어있지 않은 칸 -1
익은 토마토가 2개 이상인 경우 처리

*/