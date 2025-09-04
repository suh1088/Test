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

int N, K, ans;

// visited needed?

queue<pair<int, int>> q; // pos and time

int main(void){
    cin >> N >> K;

    q.push(make_pair(N, 0));

    while(1){
        pair<int, int> tmp = q.front();
        q.pop();

        if(tmp.first == K){
            ans = tmp.second;
            break;
        }

        else if(tmp.first < 0 || tmp.first > 100000){
            continue;
        }

        q.push(make_pair(tmp.first - 1, tmp.second + 1));
        q.push(make_pair(tmp.first + 1, tmp.second + 1));
        q.push(make_pair(tmp.first * 2, tmp.second));
    }

    cout << ans;
}   

/*
13549
*/