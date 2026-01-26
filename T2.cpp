#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

bool isNonIncreasing(vector<int> &arr)
{
    for (int i = 0; i < (int)arr.size() - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return true; // 단조증가하지 않음
        }
    }
    return false; // 단조증가
}

vector<int> performOperation(vector<int> arr, int pos)
{
    arr[pos] = arr[pos] ^ arr[pos + 1];
    arr.erase(arr.begin() + pos + 1);
    return arr;
}

bool canAchieveInK(vector<int> arr, int k)
{
    if (k == 0)
    {
        return isNonIncreasing(arr);
    }

    if (arr.size() == 1)
        return false;

    // k번 연산으로 가능한 모든 경우 탐색 (BFS 또는 DFS)
    // 간단한 구현: 각 단계에서 모든 위치 시도
    for (int pos = 0; pos < (int)arr.size() - 1; pos++)
    {
        vector<int> next = performOperation(arr, pos);
        if (canAchieveInK(next, k - 1))
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    int T;
    freopen("input.txt", "r", stdin);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case)
    {
        int N;
        cin >> N;
        vector<int> arr(N);

        for (int i = 0; i < N; i++)
        {
            cin >> arr[i];
        }

        // 이미 단조증가하지 않으면 답은 0
        if (isNonIncreasing(arr))
        {
            cout << 0 << '\n';
            continue;
        }

        // k = 1부터 N-1까지 시도
        int answer = -1;
        for (int k = 1; k < N; k++)
        {
            if (canAchieveInK(arr, k))
            {
                answer = k;
                break;
            }
        }

        cout << answer << '\n';
    }
    return 0;
}