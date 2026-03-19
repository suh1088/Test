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
#include <iomanip>

#define IMAX 0x7FFFFFFF

using namespace std;
typedef long long ll;

struct status{
    int i, j, jump, time;

    status(int s1, int s2, int jump, int time)
        : i(s1), j(s2), jump(jump), time(time) {}

    bool operator<(const status& s) const{
        return time > s.time;
    }
};

int t[51][51][6];
char m[51][51];
int N, Q;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

bool chk(int s1, int s2, int dir, int jmp){
    int d1 = s1 + dx[dir]*jmp;
    int d2 = s2 + dy[dir]*jmp;
    if(d1 < 1 || d1 > N || d2 < 1 || d2 > N){
        return false;
    }

    if(s1 == d1){
        int jMin = min(s2, d2), jMax = max(s2, d2);
        for(int j = jMin; j < jMax; j++){
            if(m[s1][j] == '#'){
                return false;
            }
        }
        if(m[d1][d2] == '.'){
            return true;
        }
        else return false;
    }
    else{ // diff
        int iMin = min(s1, d1), iMax = max(s1, d1);
        for(int i = iMin; i < iMax; i++){
            if(m[i][s2] == '#'){
                return false;
            }
        }
        if(m[d1][d2] == '.'){
            return true;
        }
        else return false;
    }

    return false;
}

int djk(int s1, int s2){
    priority_queue<status> pq;

    t[s1][s2][1] = 0;
    pq.push(status(s1, s2, 1, 0));

    while(!pq.empty()){
        status tmp = pq.top();
        pq.pop();
        int curi=tmp.i;
        int curj=tmp.j;
        int jmp=tmp.jump;
        int curtime=tmp.time;

        if(curtime > t[curi][curj][jmp]){
            continue;
        }

        //jmp
        for(int i = 0; i < 4; i++){
            int d2 = curj+dy[i]*jmp;
            int d1 = curi+dx[i]*jmp;
            
            if(chk(curi, curj, i, jmp) && t[d1][d2][jmp] > curtime + 1){
                t[d1][d2][jmp] = curtime + 1;
                pq.push(status(d1, d2, jmp, curtime + 1));

            }
        }

        //inc
        if(jmp < 5){
            int newTime = curtime + (jmp+1)*(jmp+1);
            if(t[curi][curj][jmp+1] > newTime){
                t[curi][curj][jmp+1] = newTime;
                pq.push(status(curi, curj, jmp+1, newTime));
            }
        }
        //dec
        if(jmp > 1){
            int newTime = curtime + 1;
            for(int newjmp = 1; newjmp <= jmp-1; newjmp++){
                if(t[curi][curj][newjmp] > newTime){
                    t[curi][curj][newjmp] = newTime;
                    pq.push(status(curi, curj, newjmp, newTime));
                }
            }
            
        }
    }
    return 0;
}

int main() {
    cin >> N;

    for(int i = 1; i <= N;i++){
        // for(int j = 1; j <= N; j++){
        //     cin >> m[i];
            
        // }
        cin >> (m[i] + 1);
    }

    cin >> Q;
    while(Q--){
        for(int i = 1; i <= N;i++){
            for(int j = 1; j <= N; j++){
                for(int k = 0; k<6; k++){
                    t[i][j][k] = IMAX;
                }
            }
        }

        int s1, s2, d1, d2;
        cin >> s1 >> s2 >> d1 >> d2;
        
        djk(s1, s2);

        int minimum = IMAX;
        for(int k = 0; k<6; k++){
            if(minimum > t[d1][d2][k]){
                minimum = t[d1][d2][k];
            }
        }

        if(minimum == IMAX){
            cout << -1 << '\n';
        }
        else{
            cout << minimum << '\n';
        }
    }
}

/*

*/
