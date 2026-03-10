#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

#define CMD_INIT (100)
#define CMD_ENTER (200)
#define CMD_PULL_OUT (300)
#define CMD_SEARCH (400)

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

extern void init(int N, int M, int L);
extern RESULT_E enter(int mTime, char mCarNo[]);
extern int pullout(int mTime, char mCarNo[]);
extern RESULT_S search(int mTime, char mStr[]);

static bool run()
{
    int Q, N, M, L;
    int mTime;

    char mCarNo[8];
    char mStr[5];

    int ret = -1, ans;

    RESULT_E res_e;
    RESULT_S res_s;

    scanf("%d", &Q);

    bool okay = false;

    for (int q = 0; q < Q; ++q)
    {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd)
        {
        case CMD_INIT:
            scanf("%d %d %d", &N, &M, &L);
            init(N, M, L);
            okay = true;
            break;
        case CMD_ENTER:
            scanf("%d %s", &mTime, mCarNo);
            res_e = enter(mTime, mCarNo);
            scanf("%d", &ans);
            if (res_e.success != ans)
            {
                okay = false;
                cout << "enter success mismatch: " << mTime << " " << res_e.success << " " << ans << endl;
            }
            if (ans == 1)
            {
                scanf("%s", mStr);
                if (strcmp(res_e.locname, mStr) != 0)
                {
                    cout << "enter locname mismatch: " << mTime << " " << res_e.locname << " " << mStr << endl;
                    okay = false;
                }
            }
            // cout << "ans: " << ans << " " << mStr << endl;
            break;
        case CMD_PULL_OUT:
            scanf("%d %s", &mTime, mCarNo);
            ret = pullout(mTime, mCarNo);
            scanf("%d", &ans);
            if (ret != ans)
            {
                cout << "pullout mismatch: " << ret << " " << ans << endl;
                okay = false;
            }

            // cout << "ans: " << ans << endl;
            break;
        case CMD_SEARCH:
            scanf("%d %s", &mTime, mStr);
            res_s = search(mTime, mStr);
            scanf("%d", &ans);
            // cout << "searching: \n";
            if (res_s.cnt != ans)
            {
                cout << "search cnt mismatch: " << res_s.cnt << " " << ans << endl;
                okay = false;
            }
            for (int i = 0; i < ans; ++i)
            {
                scanf("%s", mCarNo);
                strcat(mCarNo, mStr);
                // cout << mCarNo << " ";
                if (strcmp(res_s.carlist[i], mCarNo) != 0)
                {
                    cout << "search carlist mismatch: " << res_s.carlist[i] << " " << mCarNo << endl;
                    okay = false;
                }
            }

            // cout << ans << endl;
            break;
        default:
            okay = false;
            break;
        }
    }

    return okay;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int TC, MARK;

    scanf("%d %d", &TC, &MARK);
    for (int tc = 1; tc <= TC; ++tc)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}