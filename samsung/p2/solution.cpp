#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

int N, M, L, curTime;
int V = 0;
struct slot;
struct slot
{
    bool occupied = false;
    int inTime = 0;
    string car;

    int XX;
    char Y;
    int ZZZZ;

    slot() : occupied(false), inTime(0), car(""), XX(0), Y(0), ZZZZ(0) {}

    // 파싱을 위한 생성자
    slot(bool occ, int t, string c) : occupied(occ), inTime(t), car(c)
    {
        if (!c.empty() && c.length() >= 7)
        {
            XX = stoi(c.substr(0, 2));
            Y = c[2];
            ZZZZ = stoi(c.substr(3, 4));
        }
        else
        {
            XX = 0;
            Y = 0;
            ZZZZ = 0;
        }
    }

    int status() // -1:견인 필요(주차 가능) , 0:주차 불가능, 1:주차 가능
    {
        if (!occupied)
            return 1;
        if (curTime - inTime >= L)
            return -1;
        return 0;
    }
};
unordered_map<string, pair<int, int>> loc;
vector<vector<slot>> parking;
unordered_map<string, int> status; // -1:견인 , 0:정보없음(출차됨), 1:주차
unordered_map<string, slot> towingRecord;
unordered_map<string, vector<string>> searchRecord; // key:차량번호 뒷자리, value:차량번호

queue<slot> timeline;
vector<int> emptyCnt;

struct RESULT_E
{
    int success;
    char locname[5];
};

struct RESULT_S
{
    int cnt;
    char carlist[5][8];
};

void tow(string carNo)
{ // 견인
    if (status[carNo] != 1)
        return;

    emptyCnt[loc[carNo].first]++;

    status[carNo] = -1;
    slot &s = parking[loc[carNo].first][loc[carNo].second];
    towingRecord[carNo] = slot(true, s.inTime, s.car);
    s.occupied = false;
    loc.erase(carNo);
}

void delInfo(string carNo)
{
    if (status[carNo] == 0) // 정보 없음
        return;
    if (status[carNo] == 1) // 주차된 상태
    {
        if (loc.find(carNo) != loc.end())
        {
            int dist = loc[carNo].first;
            int num = loc[carNo].second;

            emptyCnt[dist]++;

            parking[dist][num].occupied = false;
            loc.erase(carNo);
        }
    }

    // 견인 또는 주차된 상태

    status[carNo] = 0;
    towingRecord.erase(carNo);

    string key = carNo.substr(3, 4);
    auto &vec = searchRecord[key];
    vec.erase(remove(vec.begin(), vec.end(), carNo), vec.end());
}

void updateInfo(string carNo)
{ // 언제 필요할까용??
    if (status[carNo] == 1)
    { // 주차된 차량
        int dist = loc[carNo].first;
        int num = loc[carNo].second;
        if (curTime - parking[dist][num].inTime >= L)
        {
            tow(carNo);
        }
    }
}

bool compareCars(const string &a, const string &b)
{
    bool isParkedA = false;
    int xxA, inTimeA;
    char yA;

    if (loc.count(a))
    {
        slot &s = parking[loc[a].first][loc[a].second];
        inTimeA = s.inTime;
        isParkedA = (curTime - inTimeA < L);
        xxA = s.XX;
        yA = s.Y;
    }
    else
    {
        slot &s = towingRecord[a];
        inTimeA = s.inTime;
        isParkedA = false; // 견인 기록에 있다면 주차 상태가 아님
        xxA = s.XX;
        yA = s.Y;
    }

    bool isParkedB = false;
    int xxB, inTimeB;
    char yB;

    if (loc.count(b))
    {
        slot &s = parking[loc[b].first][loc[b].second];
        inTimeB = s.inTime;
        isParkedB = (curTime - inTimeB < L);
        xxB = s.XX;
        yB = s.Y;
    }
    else
    {
        slot &s = towingRecord[b];
        inTimeB = s.inTime;
        isParkedB = false;
        xxB = s.XX;
        yB = s.Y;
    }

    // 주차된 차량이 앞선다
    if (isParkedA != isParkedB)
    {
        return isParkedA > isParkedB;
    }

    // 차량 번호 앞 2자리(XX)
    if (xxA != xxB)
    {
        return xxA < xxB;
    }

    // 차량 번호 중간 문자(Y)
    return yA < yB;
}

void locToChar(int dist, int num, char *locname)
{
    locname[0] = 'A' + dist;
    int tmp = 100;
    for (int i = 1; i <= 3; i++)
    {
        locname[i] = '0' + (num / tmp) % 10;
        tmp /= 10;
    }
    locname[4] = '\0';
}

void init(int N_, int M_, int L_)
{ // 초기화
    N = N_;
    M = M_;
    L = L_;
    parking.clear();
    parking.resize(N, vector<slot>(M));
    loc.clear();
    searchRecord.clear();
    status.clear();
    towingRecord.clear();

    timeline = queue<slot>();
    emptyCnt.clear();
    emptyCnt.resize(N, M);
    return;
}

void updateTimeline()
{
    while (!timeline.empty())
    {
        slot s = timeline.front();

        if (curTime - s.inTime < L)
            break;

        timeline.pop();
        updateInfo(s.car);
    }
}

RESULT_E enter(int mTime, char mCarNo[])
{
    RESULT_E res_e;
    res_e.success = -1;
    curTime = mTime;

    string carN = string(mCarNo);

    updateInfo(carN);

    switch (status[carN])
    {
    case 1: // 주차중
        res_e.success = -111;
        // cout<< "enter error: already parked " << carN << endl;
        return res_e;
    case -1: // 견인중
        delInfo(carN);
        break;
    case 0: // 정보 없음(출차됨)
        break;
    }

    int dist = -1;
    int num = -1;
    int maxEmpty = -1;

    updateTimeline();

    for (int i = 0; i < N; i++)
    {
        if (emptyCnt[i] > maxEmpty)
        {
            maxEmpty = emptyCnt[i];
            dist = i;
        }
    }

    if (maxEmpty <= 0)
    { // 주차 불가
        res_e.success = 0;
        return res_e;
    }

    for (int j = 0; j < M; j++)
    {
        if (parking[dist][j].status() != 0)
        {
            num = j;
            break;
        }
    }

    if (parking[dist][num].status() == -1)
    { // 견인 필요
        tow(parking[dist][num].car);
    }

    status[carN] = 1;
    parking[dist][num] = slot(true, curTime, carN);
    loc[carN] = make_pair(dist, num);
    string key = carN.substr(3, 4);
    searchRecord[key].push_back(carN);
    locToChar(dist, num, res_e.locname);
    res_e.success = 1;

    timeline.push(parking[dist][num]);
    emptyCnt[dist]--;

    return res_e;
}

int pullout(int mTime, char mCarNo[])
{
    curTime = mTime;
    string carN = string(mCarNo);
    updateInfo(carN);

    int ret;

    if (status[carN] == -1)
    {
        ret = (L + (curTime - towingRecord[carN].inTime - L) * 5) * (-1);
        delInfo(carN);
        return ret;
    }
    else if (status[carN] == 0)
    {
        return -1;
    }
    else if (status[carN] == 1)
    {
        int dist = loc[carN].first;
        int num = loc[carN].second;
        ret = curTime - parking[dist][num].inTime;
        delInfo(carN);
        return ret;
    }

    return -1;
}

RESULT_S search(int mTime, char mStr[])
{
    curTime = mTime;
    RESULT_S res_s;

    res_s.cnt = -1;

    string key = string(mStr);

    sort(searchRecord[key].begin(), searchRecord[key].end(), compareCars);

    res_s.cnt = min((int)searchRecord[key].size(), 5);
    for (int i = 0; i < res_s.cnt; i++)
    {
        strcpy(res_s.carlist[i], searchRecord[key][i].c_str());
    }

    return res_s;
}