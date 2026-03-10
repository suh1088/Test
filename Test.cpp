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

class cord{
    public:
    int r, c;
    cord(){
        r = -1;
        c = -1;
    }
    cord(int a, int b){
        r = a;
        c = b;
    }
};

class pos{
    public:
    cord R;
    cord B;
    int time = 0;
    bool valid = true;
    bool blue = false;
    pos();
    pos(cord& a, cord& b, int t){
        R = a;
        B = b;
        time = t;
    }
};


int N, M;
vector<vector<char>> board;
queue<pos*> q;

vector<cord> mov = {cord(-1, 0), cord(1, 0), cord(0, -1), cord(0, -1)};

bool chk(int r, int c, cord& oth){
    if((0 > r || N <= r) || (0 > c || M <= c)) return false;
    if(board[r][c] == '#') return false;
    if(board[r][c] == 'O') return true;
    bool tmp = true;
    tmp &= (oth.r != r || oth.c != c);
    return tmp;
}

pos* up(pos* tmp){
    pos* cur = new pos(tmp->R, tmp->B, tmp->time);
    if(cur->B.r < cur->R.r){
        while(chk(cur->B.r - 1, cur->B.c, cur->R)){
            cur->B.r--;
            if(board[cur->B.r][cur->B.c] == 'O'){
                cur->valid = false;
                cur->blue = true;
                break;
                // return cur;
            }
        }
        while(chk(cur->R.r - 1, cur->R.c, cur->B)){
            cur->R.r--;
            if(board[cur->R.r][cur->R.c] == 'O'){
                cur->valid = false;

                break;
                // return cur;
            }
        }
    }
    else{
        while(chk(cur->R.r - 1, cur->R.c, cur->B)){
            cur->R.r--;
            if(board[cur->R.r][cur->R.c] == 'O'){
                cur->valid = false;
     
                break;
                // return cur;
            }
        }
        while(chk(cur->B.r - 1,cur->B.c, cur->R)){
            cur->B.r--;
            if(board[cur->B.r][cur->B.c] == 'O'){
                cur->valid = false;
                cur->blue = true;
                break;
                // return cur;
            }
        }
    }
    cur->time++;
    return cur;
}

pos* down(pos* tmp){
    pos* cur = new pos(tmp->R, tmp->B, tmp->time);
    if(cur->B.r > cur->R.r){
        while(chk(cur->B.r + 1,cur->B.c, cur->R)){
            cur->B.r++;
            if(board[cur->B.r][cur->B.c] == 'O'){
                cur->valid = false;
                cur->blue = true;
                break;
                // return cur;
            }
        }
        while(chk(cur->R.r + 1,cur->R.c, cur->B)){
            cur->R.r++;
            if(board[cur->R.r][cur->R.c] == 'O'){
                cur->valid = false;
          
                break;
                // return cur;
            }
        }
    }
    else{
        while(chk(cur->R.r + 1,cur->R.c, cur->B)){
            cur->R.r++;
            if(board[cur->R.r][cur->R.c] == 'O'){
                cur->valid = false;
          
                break;
                // return cur;
            }
        }
        while(chk(cur->B.r + 1,cur->B.c, cur->R)){
            cur->B.r++;
            if(board[cur->B.r][cur->B.c] == 'O'){
                cur->valid = false;
                cur->blue = true;
                break;
                // return cur;
            }
        }
    }
    cur->time++;
    return cur;
}

pos* left_(pos* tmp){
    pos* cur = new pos(tmp->R, tmp->B, tmp->time);
    if(cur->B.c < cur->R.c){
        while(chk(cur->B.r,cur->B.c - 1, cur->R)){
            cur->B.c--;
            if(board[cur->B.r][cur->B.c] == 'O'){
                cur->valid = false;
                cur->blue = true;
                break;
                // return cur;
            }
        }
        while(chk(cur->R.r,cur->R.c - 1, cur->B)){
            cur->R.c--;
            if(board[cur->R.r][cur->R.c] == 'O'){
                cur->valid = false;
       
                break;
                // return cur;
            }
        }
    }
    else{
        while(chk(cur->R.r,cur->R.c - 1, cur->B)){
            cur->R.c--;
            if(board[cur->R.r][cur->R.c] == 'O'){
                cur->valid = false;
       
                break;
                // return cur;
            }
        }
        while(chk(cur->B.r,cur->B.c - 1, cur->R)){
            cur->B.c--;
            if(board[cur->B.r][cur->B.c] == 'O'){
                cur->valid = false;
                cur->blue = true;
                break;
                // return cur;
            }
            
        }
    }
    cur->time++;
    return cur;
}

pos* right_(pos* tmp){
    pos* cur = new pos(tmp->R, tmp->B, tmp->time);
    if(cur->B.c > cur->R.c){
        while(chk(cur->B.r,cur->B.c + 1, cur->R)){
            cur->B.c++;
            if(board[cur->B.r][cur->B.c] == 'O'){
                cur->valid = false;
                cur->blue = true;
                break;
                // return cur;
            }
        }
        while(chk(cur->R.r,cur->R.c + 1, cur->B)){
            cur->R.c++;
            if(board[cur->R.r][cur->R.c] == 'O'){
                cur->valid = false;
   
                break;
                // return cur;
            }
        }
    }
    else{
        while(chk(cur->R.r,cur->R.c + 1, cur->B)){
            cur->R.c++;
            if(board[cur->R.r][cur->R.c] == 'O'){
                cur->valid = false;
            
                break;
                // return cur;
            }
        }
        while(chk(cur->B.r,cur->B.c + 1, cur->R)){
            cur->B.c++;
            if(board[cur->B.r][cur->B.c] == 'O'){
                cur->valid = false;
                cur->blue = true;
                break;
                // return cur;
            }
        }
    }
    cur->time++;
    return cur;
}

int main(void){
    ios::sync_with_stdio(false); 
    cin.tie(NULL);

    cin >> N >> M;
    board.resize(N, vector<char>(M, 0));

    cord red, b;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            char tmp;
            cin >> tmp;
            if(tmp == 'R'){
                red = cord(i, j);
                board[i][j] = '.';
            }
            else if(tmp == 'B'){
                b = cord(i, j);
                board[i][j] = '.';

            }
            else{
                board[i][j] = tmp;
            }
        }
    }
    pos* init = new pos(red, b, 0);

    q.push(init);

    

    while(!q.empty()){
        pos* tmp = q.front();
        q.pop();

        if(tmp->time > 10){
            cout << -1;
            return 0;
        }

        pos* u;
        pos* d;
        pos* l;
        pos* r;

        u = up(tmp);
        d = down(tmp);
        l = left_(tmp);
        r = right_(tmp);

        if(u->valid){
            q.push(u);
        }
        else{
            if(!u->blue && u->time < 11){
                cout << u->time;
                return 0;
            }
            else{
                delete u;
            }
        }

        if(d->valid){
            q.push(d);
        }
        else{
            if(!d->blue && d->time < 11){
                cout << d->time;
                return 0;
            }
            else{
                delete d;
            }
        }

        if(l->valid){
            q.push(l);
        }
        else{
            if(!l->blue && l->time < 11){
                cout << l->time;
                return 0;
            }
            else{
                delete l;
            }
        }

        if(r->valid){
            q.push(r);
        }
        else{
            if(!r->blue && r->time < 11){
                cout << r->time;
                return 0;
            }
            else{
                delete r;
            }
        }

        delete tmp;
    }
    cout << -1;
    return 0;
}

/*
13460

진짜 역대급으로 오래걸렸다. 
이것저것 실수한거 고치느라 거의 3시간 걸린듯

먼저 전략 세우고
깔끔한 구현방향 고민하고
손 움직이기
*/