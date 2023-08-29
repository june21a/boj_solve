#include <iostream>
#include <vector>
#define ll long long

using namespace std;

bool check_who_win(string str){
    int cnt_white=0, cnt_black=0;
    ll move_white=0, move_black=0;
    int idx = str.length()-1;
    
    while(idx > -1){
        if(str[idx] == 'W'){
            if(cnt_black >= cnt_white+1) {
                cnt_black = 0;
                cnt_white = 0;
            }
            else cnt_white++;
        }
        else if(str[idx] == 'B'){
            if(cnt_black+1 <= cnt_white) {
                cnt_black = 0;
                cnt_white = 0;
            }
            else cnt_black++;
        }
        else{
            move_white += cnt_white;
            move_black += cnt_black;
        }
        idx--;
    }
    
    if(move_white > move_black) return true;
    else return false;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    string str;
    
    cin >> T;
    for(int i=0; i<T; i++){
        cin >> str;
        if(check_who_win(str)) cout << "WHITE\n";
        else cout << "BLACK\n";
    }
}