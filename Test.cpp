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

int spin(int want, deque<int> fdq)
{
    int fcnt = 0;
    while (fdq.front() != want)
    {
        int temp = fdq.front();
        fdq.pop_front();
        fdq.push_back(temp);
        fcnt++;
    }
    return fcnt;
}

int cspin(int want, deque<int> sdq)
{
    int scnt = 0;
    while (sdq.front() != want)
    {
        int temp = sdq.back();
        sdq.pop_back();
        sdq.push_front(temp);
        scnt++;
    }
    return scnt;
}

int main(void)
{
    int N, M;
    cin >> N >> M;

    vector<int> want(M);

    for (int i = 0; i < M; i++)
    {
        cin >> want[i];
    } // input ended 삭제 가능

    deque<int> dq;
    for (int i = 0; i < N; i++)
        dq.push_back(i + 1);

    int cnt;
    for (int i = 0; i < M; i++)
    {
        int s = spin(want[i], dq);
        int c = cspin(want[i], dq);
        if (s < c)
        {
            cnt += s;
            while (s--)
            {
                int temp = dq.front();
                dq.pop_front();
                dq.push_back(temp);
            }
        }
        else
        {
            cnt += c;
            while (c--)
            {
                int temp = dq.back();
                dq.pop_back();
                dq.push_front(temp);
            }
        }

        dq.pop_front();
    }
    cout << cnt;
}

/*
1021

다이얼 금고

빠져있는 숫자도 생각

*/