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

int clo(int now, int want, vector<int> &dial)
{
    int cnt = 0;
    while (now != want)
    {
        if (now > dial.size())
            now = 0;
        now++;
        cnt += dial[now];
    }
    return cnt;
}

int coclo(int now, int want, vector<int> &dial)
{
    int cnt = 0;
    while (now != want)
    {
        if (now < 0)
            now = dial.size();
        now--;
        cnt += dial[now];
    }
    return cnt;
}

int main(void)
{
    int N, M;
    cin >> N >> M;

    vector<int> want(M);
    vector<int> dial(N, 1);
    dial[0] = 0;

    for (int i = 0; i < M; i++)
    {
        cin >> want[i];
    } // input ended

    int now = 1;
    int cnt = 0;

    for (int i = 0; i < M; i++)
    {
        cnt += min(clo(now, want[i], dial), coclo(now, want[i], dial));
        dial[want[i]] = 0;
        now++;
    }

    cout << cnt;
}

/*
1021

다이얼 금고

빠져있는 숫자도 생각

1번 풀이, deque 무식한 방법법
*/