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

deque<int> dq;

int main(void)
{
    int n;
    cin >> n;
    int icut = (int)lround((double)n * 0.15);
    while (n--)
    {
        int tmp;
        cin >> tmp;
        dq.push_back(tmp);
    }
    sort(dq.begin(), dq.end());
    while (icut--)
    {
        dq.pop_back();
        dq.pop_front();
    }

    int sum = 0;
    for (int i : dq)
    {
        sum += i;
    }
    int final = (int)lround((double)sum / (dq.size()));
    cout << final;
}

/*
18110

EZ
*/