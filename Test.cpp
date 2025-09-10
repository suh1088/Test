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

int N, M; // 도시 크기, 
// vector<vector<int>> town;
vector<pair<int, int>> kfc;
vector<pair<int, int>> home;

int sol = 0x7FFFFFFF;

int caldis(pair<int, int> a, pair<int, int> b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void fmin(vector<int>& comb){ // 살릴 치킨집의 idx
    int chkdis = 0;
    
    for(pair<int, int> h : home){
        int dis = 0x7FFFFFFF;
        for(int i : comb){
            dis = min(caldis(h, kfc[i]), dis);
        }
        chkdis += dis;
    }
    sol = min(sol, chkdis);
    
}

void fcomb(int st, vector<int>& comb){
    if(comb.size() == M){
        fmin(comb);
    }

    for(int i = st; i < kfc.size(); i++){
        comb.push_back(i);
        fcomb(i + 1, comb);
        comb.pop_back();
    }
}

int main(void){
    // ios::sync_with_stdio(false); 
    // cin.tie(NULL);

    cin >> N >> M;

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            int tmp;
            cin >> tmp;

            if(tmp == 1){
                home.push_back(make_pair(i,j));
            }
            else if(tmp == 2){
                kfc.push_back(make_pair(i,j));
            }
        }
    }

    // input compl
    vector<int> comb;

    fcomb(0, comb);

    cout << sol;
}

/*
11660

*/