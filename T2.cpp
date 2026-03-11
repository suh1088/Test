#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<long long> A, B, C;

// [start, end] 범위를 자유롭게 DP
long long dpFree(int start, int end) {
    vector<vector<long long>> dp(N, vector<long long>(4, -1e18));
    
    dp[start][0] = 0;
    dp[start][1] = A[start];
    dp[start][2] = B[start];
    dp[start][3] = C[start];
    
    for (int i = start + 1; i <= end; i++) {
        dp[i][0] = max({dp[i-1][0], dp[i-1][1], dp[i-1][2], dp[i-1][3]});
        dp[i][1] = max({dp[i-1][0], dp[i-1][2], dp[i-1][3]}) + A[i];
        dp[i][2] = max({dp[i-1][0], dp[i-1][1], dp[i-1][3]}) + B[i];
        dp[i][3] = max({dp[i-1][0], dp[i-1][1], dp[i-1][2]}) + C[i];
    }
    
    return max({dp[end][0], dp[end][1], dp[end][2], dp[end][3]});
}

// start와 end에서 forbidden 색상을 못 가져감
long long dpWithConstraint(int start, int end, int forbidden) {
    vector<vector<long long>> dp(N, vector<long long>(4, -1e18));
    
    dp[start][0] = 0;
    dp[start][1] = (forbidden != 1) ? A[start] : -1e18;
    dp[start][2] = (forbidden != 2) ? B[start] : -1e18;
    dp[start][3] = (forbidden != 3) ? C[start] : -1e18;
    
    for (int i = start + 1; i <= end; i++) {
        dp[i][0] = max({dp[i-1][0], dp[i-1][1], dp[i-1][2], dp[i-1][3]});
        
        long long v1 = max({dp[i-1][0], dp[i-1][2], dp[i-1][3]}) + A[i];
        long long v2 = max({dp[i-1][0], dp[i-1][1], dp[i-1][3]}) + B[i];
        long long v3 = max({dp[i-1][0], dp[i-1][1], dp[i-1][2]}) + C[i];
        
        if (i == end) {
            // 끝점에서는 forbidden 색상 제약 추가
            dp[i][1] = (forbidden != 1) ? v1 : -1e18;
            dp[i][2] = (forbidden != 2) ? v2 : -1e18;
            dp[i][3] = (forbidden != 3) ? v3 : -1e18;
        } else {
            dp[i][1] = v1;
            dp[i][2] = v2;
            dp[i][3] = v3;
        }
    }
    
    return max({dp[end][0], dp[end][1], dp[end][2], dp[end][3]});
}

int main() {
    cin >> N;
    A.resize(N);
    B.resize(N);
    C.resize(N);
    
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];
    for (int i = 0; i < N; i++) cin >> C[i];
    
    long long ans = 0;
    
    // Case 1: 0번 바구니에서 아무것도 안 가져감
    if (N > 1) {
        ans = max(ans, dpFree(1, N - 1));
    }
    
    // Case 2: 0번 바구니에서 A 공 가져감
    if (N > 1) {
        ans = max(ans, A[0] + dpWithConstraint(1, N - 1, 1));
    } else {
        ans = max(ans, A[0]);
    }
    
    // Case 3: 0번 바구니에서 B 공 가져감
    if (N > 1) {
        ans = max(ans, B[0] + dpWithConstraint(1, N - 1, 2));
    } else {
        ans = max(ans, B[0]);
    }
    
    // Case 4: 0번 바구니에서 C 공 가져감
    if (N > 1) {
        ans = max(ans, C[0] + dpWithConstraint(1, N - 1, 3));
    } else {
        ans = max(ans, C[0]);
    }
    
    cout << ans << endl;
    
    return 0;
}
