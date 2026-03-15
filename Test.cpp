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


int N, M;
int arr[101][101];
int ans = 0;

int main() {
    // 입력: N(격자 크기), M(연속으로 같은 값이 필요한 최소 길이)
    cin >> N >> M;

    // N x N 격자 입력
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            cin >> arr[r][c];
        }
    }

    // 한 "직선 라인"(행/열)에서 같은 값이 연속으로 M개 이상 있는지 검사한다.
    // (sr, sc)에서 시작해서 (dr, dc) 방향으로 N칸을 순회한다.
    auto lineHasRunAtLeastM = [&](int sr, int sc, int dr, int dc) -> bool {
        // M == 1이면 어떤 행/열이든(원소가 존재하는 한) 조건을 만족한다.
        if (M <= 1) return true;

        int prev = arr[sr][sc];
        int runLen = 1;

        for (int step = 1; step < N; ++step) {
            const int r = sr + dr * step;
            const int c = sc + dc * step;

            if (arr[r][c] == prev) {
                ++runLen;
                // 목표 길이에 도달하면 더 볼 필요 없이 즉시 성공
                if (runLen >= M) return true;
            } else {
                // 값이 바뀌면 연속 길이를 1로 초기화
                prev = arr[r][c];
                runLen = 1;
            }
        }
        return false;
    };

    // 결과는 main 한 번 실행 기준으로 0부터 다시 센다.
    ans = 0;

    // 1) 각 행이 조건을 만족하는지 검사
    for (int r = 0; r < N; r++) {
        if (lineHasRunAtLeastM(r, 0, 0, 1)) {
            ans++;
        }
    }

    // 2) 각 열이 조건을 만족하는지 검사
    for (int c = 0; c < N; c++) {
        if (lineHasRunAtLeastM(0, c, 1, 0)) {
            ans++;
        }
    }

    cout << ans;
    return 0;
}

/*
not add and commit on test1
*/
