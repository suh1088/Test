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

priority_queue<pair<int, int>, greater<pair<int, int>>> q; // pos and time

int main(void){
    cin >> N >> K;

    if(K < N){
        ans = N - K;
        cout << ans;
        return 0;
    }

    q.push(make_pair(N, 0));

    while(1){
        
        int time = q.front().second;
        int pos = q.front().first;
        q.pop();

        if(pos == K){
            ans = time;
            break;
        }

        if(pos-1 >= 0){
            q.push(make_pair(pos - 1, time + 1));
        }
        if(pos < K){
            q.push(make_pair(pos + 1, time + 1));
        }
        if(pos < K){
            q.push(make_pair(pos * 2, time));
        }
    }

    cout << ans;
}   

/*
13549

걷는 경우 거리 계산 쉬움
순간이동 할 경우 가능한 횟수 그리 많지 않음

걷기랑 점멸 랜덤하게 섞인경우?


*/