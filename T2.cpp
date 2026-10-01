#include <bits/stdc++.h>

#define IMAX 0x7FFFFFFF
#define IMIN 0x80000000

using namespace std;
typedef long long ll;

int N, K;
vector<vector<int>> grid;
pair<int,int> cur;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

bool chk(int x, int y){
    return (x >= 0 && x < N) && (y >= 0 && y < N);
}

int bfs(){
    int thrs = grid[cur.first][cur.second];
    vector<vector<int>> vis(N, vector<int>(N,0));
    queue<pair<int,int>> q;
    int found = 0;
    
    q.push(cur);
    vis[cur.first][cur.second] = 1;
    
    while(!q.empty()){
        pair<int,int> tmp = q.front();
        q.pop();
        
        for(int i = 0; i < 4; i++){
            int nx = tmp.first + dx[i], ny = tmp.second + dy[i];
            
            if(chk(nx, ny) && !vis[nx][ny] && grid[nx][ny] < thrs){
                q.push({nx,ny});
                vis[nx][ny]=1;
                found++;
            }
        }
    }


    int candn = -1;
    pair<int,int> candc;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N;j++){
            if(vis[i][j] && candn < grid[i][j] && candn != thrs){
                candn = grid[i][j];
                candc = make_pair(i,j);

            }
        }
    }

    cur = candc;

    return found;
}

void move(int cnt){
    if(cnt == K) return;
    // pair<int, int> cand;
    if(!bfs()){
        return;
    }

    move(cnt + 1);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0);

    cin >> N >> K;
    grid.resize(N, vector<int>(N,-1));

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N;j++){
            cin >> grid[i][j];
        }
    }

    cin >> cur.first >> cur.second;

    move(0);

    cout << cur.first << " " << cur.second;
}