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

vector<int> arr = {1,2,3,4,5};

int next(int idx, int max){
    if(idx < 0){
        return 0;
    }

    if(arr[idx] + 5 - idx <= max){
        return ++arr[idx];
    }
    
    else{
        int tmp = next(idx-1, max);
        if(tmp == 0){
            return 0;
        }
        arr[idx] = tmp + 1;
        return arr[idx];
    }
}

int main(void){
    do{
        for(int i = 0; i < 5; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
    }while(next(4, 10) != 0);
    

}   

/*
1753
*/