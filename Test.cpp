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

int n;

int main(void)
{
    cin >> n;
    int sum = 0;
    int Min = 4444, Max = -4444;
    int most_frec = 0;
    map<int, int> frec;
    priority_queue<int> down;

    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        sum += tmp;
        Min = min(tmp, Min);
        Max = max(tmp, Max);
        frec[tmp]++;
        most_frec = max(frec[tmp], most_frec);
        down.push(tmp);
    }

    double mean = (double)sum / n;
    int p = n / 2;
    for (int i = 0; i < p; i++)
        down.pop();
    int mid = down.top();
    int range = Max - Min;

    priority_queue<int, vector<int>, greater<int>> max_frecs;

    for (pair i : frec)
    {
        if (i.second == most_frec)
        {
            max_frecs.push(i.first);
        }
    }
    max_frecs.pop();
    int s_fr = max_frecs.top();

    cout << lround(mean) << endl
         << mid << endl
         << s_fr << endl
         << range;
}

/*
2108


*/