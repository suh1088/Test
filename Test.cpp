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

using namespace std;
typedef long long ll;

class Node{
    int wei;
    int par;
    int travel;
    set<int> ance;
};

int n;
Node* root;


int main(void){
    cin >> n;
    root = new Node[n];
    while (n--)
    {
        int r, c, w;
        cin >> r >> c >> w;

        /* code */
    }
    
}

/*
1967
*/