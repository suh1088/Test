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

using namespace std;
typedef long long ll;

int main(void)
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        string cmds;
        int n;
        string arr;
        deque<int> dq;
        bool rev = true;
        bool error = false;
        cin >> cmds >> n >> arr;

        // 2자리수 처리, 더 쉬운 방법을 찾아볼 것
        string temp = "";
        while (1)
        {
            if (arr.empty())
            {
                break;
            }
            switch (arr[0])
            {
            case '[':
                arr.erase(0, 1);
                break;

            case ']':
            case ',':
                dq.push_back(stoi(temp));
                temp = "";
                arr.erase(0, 1);
                break;

            default:
                temp.append(arr.substr(0, 1));
                arr.erase(0, 1);
                break;
            }
        }

        for (int j = 0; j < cmds.size(); j++)
        {
            if (error)
                break;
            switch (cmds[j])
            {
            case 'R':
                rev = !rev;
                break;

            case 'D':
                if (dq.empty())
                {
                    error = true;
                    break;
                }
                if (rev)
                { // 순방향
                    dq.pop_front();
                }

                else
                { // 역방향
                    dq.pop_back();
                }
                break;

            default:
                break;
            }
        } // 명령어 처리 끝

        if (error)
        {
            // cout << "error\n";
            continue;
        }

        string out = "[";
        for (int j = 0; j < dq.size() - 1; j++)
        {
            if (rev)
            {
                out.append(to_string(dq.front()));
                dq.pop_front();
            }
            else
            {
                out.append(to_string(dq.back()));
                dq.pop_back();
            }
            out.append(",");
        }
        if (rev)
        {
            out.append(to_string(dq.front()));
            dq.pop_front();
        }
        else
        {
            out.append(to_string(dq.back()));
            dq.pop_back();
        }
        out.append("]");

        // cout << out << "\n";
    }
}