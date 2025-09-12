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

int N, acidx; // 
int curmin = 0x7FFFFFFF;
int c1, c2;
vector<int> liq;


int main(void){
    // ios::sync_with_stdio(false); 
    // cin.tie(NULL);


    cin >> N;
    liq.resize(N, 0);
    bool flag = true;

    for(int i = 0; i < N; i++){
        cin >> liq[i];
        if(flag && liq[i] > 0){
            acidx = i;
            flag = false;
        }
    }

    
    
    if(acidx > 1 && abs(liq[acidx - 1] + liq[acidx - 2]) < curmin){
        c2 = acidx - 1;
        c1 = acidx - 2;
        curmin = abs(liq[acidx - 1] + liq[acidx - 2]);
    }
    if(acidx < N-1 && abs(liq[acidx] + liq[acidx + 1]) < curmin){
        c1 = acidx;
        c2 = acidx + 1;
        curmin = abs(liq[acidx] + liq[acidx + 1]);
    }

    int a = 0, b = N - 1;
    while(a < b){
        if(abs(liq[a] + liq[b]) < curmin){
            c1 = a;
            c2 = b;
            curmin = abs(liq[a] + liq[b]);
        }

        if(liq[a] + liq[b] > 0){
            b--;
        }
        else if(liq[a] + liq[b] < 0){
            a++;
        }
        else{
            c1 = a;
            c2 = b;
            break;
        }
    }

    cout << liq[c1] << " " << liq[c2];

}

/*
2467

1. 이성애

2. 동성애-
ㄴ 무조건 -1 -2

3. 동성애+
ㄴ 무조건 +0 +1

*/