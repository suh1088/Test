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

int N, M;
vector<int> arr;
vector<int> odd;
vector<int> even; // idx + 0.5 == real idx

void input()
{
    cin >> N;
    arr.resize(N + 1, 0);
    odd.resize(N + 1, 0);
    even.resize(N + 1, 0);
    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
    }
    cin >> M;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    input();

    for (int i = 1; i <= N; i++)
    {
        int l = i - 1, r = i + 1;
        int len = 1;
        while (arr[l--] == arr[r++])
        {
            len += 2;
        }
        odd[i] = len;
    }

    for (int i = 1; i < N; i++)
    {
        int l = i, r = i + 1;
        int len = 0;
        while (arr[l--] == arr[r++])
        {
            len += 2;
        }
        even[i] = len;
    }

    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;

        if ((b - a) % 2 == 0)
        { // use odd
            int idx = (a + b) / 2;
            if (odd[idx] > (b - a) + 1)
            {
                cout << "1\n";
            }
            else
            {
                cout << "0\n";
            }
        }
        else
        { // use even
            int idx = (a + b) / 2;
            if (even[idx] > (b - a) + 1)
            {
                cout << "1\n";
            }
            else
                cout << "0\n";
        }
    }
}

/*
1202

정렬하고 이진탐색 할바엔 그냥 멀티셋 쓰세요 제발....
이 간단한걸 지금까지 나만 몰랐네 ㅠㅠ
*/