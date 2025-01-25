#include <string>
#include <vector>

using namespace std;

int TtoI(string time){
    int It = 0;
    It += stoi(time.substr(3,2));
    It += stoi(time.substr(0,2)) * 60;
    return It;
}

string solution(string video_len, string pos, string op_start, string op_end, vector<string> commands) {
    
    int st = TtoI(op_start);
    int en = TtoI(op_end);
    int len = TtoI(video_len);
    int po = TtoI(pos);
    
    for(int i = 0 ; i < commands.size(); i++){
        if(po >= st && po <= en){
            po = en;
        }
        if(commands[i] == "prev"){
            po -= 10;
            if(po < 0){
                po = 0;
            }
        }
        
        else if(commands[i] == "next"){
            po += 10;
            if(po > len){
                po = len;
            }
        }
    }
    
    string answer = "";
    
    int min = po / 60;
    if(min < 10) answer += "0";
    answer += to_string(min);
    
    answer += ":";
    
    int sec = po % 60;
    if(sec < 10) answer += "0";
    answer += to_string(sec);
    
    return answer;
}