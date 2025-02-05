#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <map>

using namespace std;
typedef long long ll;

int n, m;

void prin(string &ans, int st, int more)
{
    if (more <= 0)
    {
        cout << ans << "\n";
        return;
    }

    for (int i = st; i <= n - more + 1; i++)
    {
        string tmp = ans;
        tmp += " ";
        tmp += to_string(i);
        prin(tmp, i + 1, more - 1);
    }
}
int main(void)
{

    cin >> n >> m;

    for (int i = 1; i <= n + 1 - m; i++)
    {
        string a = "";
        a += to_string(i);
        prin(a, i + 1, m - 1);
    }
}