#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, curTime;
bool P = false;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

struct Pos
{
    int x;
    int y;

    bool operator==(const Pos &other)
    {
        return (x == other.x) && (y == other.y);
    }
};

struct Bug
{
    int id;
    int length;
    int potential;
    int dir; // 0~3
    Pos head;
    vector<Pos> body;
    // bool alive;
};

vector<Bug> bugs;
vector<vector<vector<int>>> grid; // 각 격자마다 여러 벌레들이 겹칠수 있음
vector<Bug> markedId;

struct RESULT
{
    int cnt = 0;
    int IDs[5] = {0, 0, 0, 0, 0};
};

bool OutOfBound(Pos p)
{
    return (p.x < 0 || p.x >= N) || (p.y < 0 || p.y >= N);
}

bool chkIfColide(Pos p)
{
    if (OutOfBound(p))
    {
        // cout<< "Error: chkIfColide OutOfBound!" << endl;
        // exit(1);
    }
    return grid[p.y][p.x].size() > 1;
}

void pushGrid(int id, Pos p)
{
    if (OutOfBound(p))
        return;
    grid[p.y][p.x].push_back(id);
}

void popGrid(int id, Pos p)
{
    if (OutOfBound(p))
        return;

    if (grid[p.y][p.x].empty())
        return;

    for (int i = 0; i < grid[p.y][p.x].size(); i++)
    {
        if (grid[p.y][p.x][i] == id)
        {
            grid[p.y][p.x].erase(grid[p.y][p.x].begin() + i);
            return;
        }
    }
}

Bug &findBug(int id)
{
    for (auto &bug : bugs)
    {
        if (bug.id == id)
            return bug;
    }
    // cout<< "Error: Bug not found!" << endl;
    // exit(1);
    return bugs[0];
}

int potentialTo(Pos p, int length)
{
    if (OutOfBound(p))
    {
        // cout<< "Error: potentialTo OutOfBound!" << endl;
        return -1;
    }
    for (int id : grid[p.y][p.x])
    {
        Bug &b = findBug(id);
        if (!(b.head == p))
        {
            b.potential += length;
            return id;
        }
    }
    return -1;
}

int getNextDir(Bug &bug)
{ // 벌레의 헤드가 다음에 향할 방향
    // ㄷ자 애벌래는 존재할 수 없다!
    if (bug.head.x == bug.body.back().x || bug.head.y == bug.body.back().y)
    {
        bug.dir++;
        if (bug.dir == 4)
            bug.dir = 0;
    }
    return bug.dir;
}

void marking()
{ // 이동 후 소멸될 벌레들 리스트 만들기
    for (auto &bug : bugs)
    {
        if (OutOfBound(bug.head) || chkIfColide(bug.head))
        {
            markedId.push_back(bug);
        }
    }
}

void deleteBugs()
{ // 마킹된 벌레들 중 없어져야 할 벌레들 판단 후 없애기

    marking();
    for (Bug bug : markedId)
    {
        int id = bug.id;

        if (!OutOfBound(bug.head) && chkIfColide(bug.head))
        {
            potentialTo(bug.head, bug.length);
        }

        // 그리드에서 지우기
        for (Pos p : bug.body)
        {
            popGrid(id, p);
        }
        // 벌레 리스트에서 지우기
        for (int i = 0; i < bugs.size(); i++)
        {
            if (bugs[i].id == id)
            {
                bugs.erase(bugs.begin() + i);
                break;
            }
        }
    }
    markedId.clear();
}

void sortBugs()
{ // 벌레 리스트 정렬(필요한진 모르겠음)
}

bool compare(const int &a, const int &b)
{
    Bug &bugA = bugs[a];
    Bug &bugB = bugs[b];

    if (bugA.length != bugB.length)
    {
        return bugA.length > bugB.length;
    }
    return bugA.id > bugB.id;
}

int move(Bug &bug)
{ // 한 벌레를 움직이는 함수. (꼬리 없애고 머리 추가) 충돌시 일단 마킹

    // 방향 확인
    int dir = getNextDir(bug);
    // 꼬리 제거
    if (bug.potential > 0)
    {
        bug.length++;
        bug.potential--;
    }
    else
    {
        popGrid(bug.id, bug.body.back());
        bug.body.pop_back();
    }

    // 머리 추가
    Pos newHead = Pos{bug.head.x + dx[dir], bug.head.y + dy[dir]};
    bug.body.insert(bug.body.begin(), newHead);

    // 충돌 확인
    // if (OutOfBound(newHead) || chkIfColide(newHead))
    // {
    //     markedId.push_back(bug.id);
    // }
    bug.head = newHead;
    pushGrid(bug.id, newHead);
    return 0;
}

void oneStep()
{ // 1초 스텝 함수

    for (auto &bug : bugs)
    {
        move(bug);
    }
    //  //cout<< "curTime: " << curTime << endl;

    deleteBugs();
}

// void prinGrid()
// {
//      //cout<< "Grid state " << curTime << ": " << endl;
//     for (int y = 0; y < N; y++)
//     {
//         for (int x = 0; x < N; x++)
//         {
//              //cout<< "[";
//             for (int id : grid[y][x])
//             {
//                  //cout<< id;
//             }
//             if (grid[y][x].empty())
//             {
//                  //cout<< " ";
//             }
//              //cout<< "]";
//         }
//          //cout<< endl;
//     }
// }
void timeWarp(int destTime)
{ // 원하는 시간까지 타임워프
    while (curTime < destTime)
    {
        // if (P)
        //     prinGrid();
        oneStep();
        curTime++;
    }
}

void init(int N_)
{ // 초기 세팅
    N = N_;
    curTime = 0;
    bugs.clear();
    grid = vector<vector<vector<int>>>(N, vector<vector<int>>(N, vector<int>()));
}

void join(int mTime, int mID, int mX, int mY, int mLength)
{ // 애벌레 추가
    timeWarp(mTime);

    Bug newBug;
    newBug.id = mID;
    newBug.length = mLength;
    newBug.potential = 0;
    newBug.dir = 0;
    newBug.head = Pos{mX, mY};

    // 몸통 생성
    newBug.body.push_back(newBug.head);
    for (int i = 1; i < mLength; i++)
    {
        Pos bodyPart = Pos{mX, mY + i};
        newBug.body.push_back(bodyPart);
        // pushGrid(mID, bodyPart);
    }

    // 그리드에 추가
    for (Pos p : newBug.body)
    {
        pushGrid(mID, p);
    }

    bugs.push_back(newBug);
}

RESULT top5(int mTime)
{
    RESULT ret = RESULT();
    timeWarp(mTime);

    vector<int> idx;
    for (int i = 0; i < bugs.size(); i++)
    {
        idx.push_back(i);
    }

    sort(idx.begin(), idx.end(), compare);

    ret.cnt = min(5, (int)bugs.size());

    //  //cout<< "Top bugs at time " << mTime << ": " << ret.cnt << " ";
    for (int i = 0; i < ret.cnt; i++)
    {
        ret.IDs[i] = bugs[idx[i]].id;
        //  //cout<< ret.IDs[i] << " ";
    }
    //  //cout<< endl;
    return ret;
}
