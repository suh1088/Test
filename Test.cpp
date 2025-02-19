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

int N, cnt = 0;
vector<int> board; // 가능세계 (0 ~ N-1)

bool chkThreat(int r, int c)
{ // 들어오는 좌표는 가장 아래있는 퀸
    // 가로 -> 한 줄에 한분씩 계시니까 걍 무시
    // 세로 -> 위에서부터 체크
    for (int i = 0; i < r; i++)
    {
        if (board[i] == c)
            return true;
    }

    // 대각 -> 양쪽 대각으로 체크
    for (int i = r - 1; i >= 0; i--)
    {
        int r_ = c + (r - i);
        int l = c - (r - i);
        if (l >= 0 && r_ < N)
        {
            if (board[i] == l || board[i] == r_)
                return true;
        }
        else if (l >= 0)
        {
            if (board[i] == l)
                return true;
        }
        else if (r_ < N)
        {
            if (board[i] == r_)
                return true;
        }
    }

    return false;
}

int dig(int dep)
{
    if (dep > N - 1)
    {
        cnt++;
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        if (!chkThreat(dep, i))
        {
            board[dep] = i;
            dig(dep + 1);
        }
    }
    return 0;
}

int main(void)
{
    cin >> N;
    board.resize(N, 0);

    dig(0);

    cout << cnt;
}

/*
9663

한 열에 최소 하나의 여왕님이 계셔야 함 ㅇㅇ
ㄴ 대충 비둘기집 어쩌구
*/