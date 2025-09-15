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

int N, S, idx = 0x7FFFFFFF;

vector<int> arr;

int main(void){
    ios::sync_with_stdio(false); 
    cin.tie(NULL);

    cin >> N >> S;

    arr.resize(N+1, 0);
    for(int i = 1; i <= N; i++){
        int tmp;
        cin >> tmp;
        arr[i] = tmp + arr[i-1];

        if(arr[i] >= S){
            idx = min(idx, i);
        }
    }

    if(idx == 0x7FFFFFFF){
        cout << 0;
        return 0;
    }

    int m = 0x7FFFFFFF;

    int st = 0, en = 0;
    while(en <= N){
        if(arr[en] - arr[st] >= S){
            m = min(m, en - st);
            st++;
        }
        else{
            en++;
        }
    }

    cout << m;
}

/*
1806

투 포인터
포인터 두개를 가지고, 가능한 방법을 향해 움직임
저번에 풀었던 용액 문제와 비슷
*/