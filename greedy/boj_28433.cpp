#include <iostream>
#define ll long long

using namespace std;


int main()
{
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int T, N;
    ll input;
    
    cin >> T;
    for(int i=0; i<T; i++){
        cin >> N;
        int plus_area = 0, minus_area = 0;
        ll cur = 0;
        int idx = 0;
        
        
        cin >> input;
        cur += input;
        idx++;
        for(; idx<N; idx++){
            cin >> input;
            if(cur <= 0){
                if(input > 0) {
                    if(cur + input > 0) cur += input;
                    else {
                        minus_area++;
                        cur = input;
                    }
                }
                else cur += input;
            }
            else{
                if(input > 0){
                    plus_area++;
                    cur = input;
                }
                else{
                    if(input + cur > 0) cur += input;
                    else {
                        plus_area++;
                        cur = input;
                    }
                }
            }
        }
        
        if(cur > 0) plus_area++;
        else if(cur < 0) minus_area++;
        
        if(plus_area > minus_area) cout << "YES\n";
        else cout << "NO\n";
    }
}