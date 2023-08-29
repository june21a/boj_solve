#include <iostream>
#include <algorithm>
#define INF 30000

using namespace std;

int N;
int DP[1 << 16];
int elec_value[16][16];
int target;


int power_plant(int current_state, int current_cnt){
    if(current_cnt >= target) return 0;
    if(DP[current_state] != INF) return DP[current_state];
    
    int min_value[16];
    for(int i=0; i<N; i++) min_value[i] = 30000;
    for(int i=0; i<N; i++){
        if(current_state & (1 << i)){
            for(int j=0; j<N; j++) min_value[j] = min(min_value[j], elec_value[i][j]);
        }
    }
    
    for(int i=0; i<N; i++){
        if(current_state & (1 << i)) continue;
        DP[current_state] = min(DP[current_state], power_plant(current_state+(1 << i), current_cnt+1) + min_value[i]);
    }
    return DP[current_state];
}

int main()
{
    string current;
    int min_value[16];
    int first_state = 0;
    int first_cnt = 0;
    
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> elec_value[i][j];
    }
    cin >> current;
    cin >> target;
    
    if(target > N){
        cout << -1;
        return 0;
    }
    
    fill(DP, DP+(1 << 16), INF);
    fill(min_value, min_value+16, 36);
    
    
    for(int i=0; i<N; i++){
        if(current[i] == 'Y'){
            first_cnt++;
            first_state += (1 << i);
        }
    }
    
    if(first_cnt == 0 && target != 0) cout << -1;
    else if(first_cnt >= target) cout << 0;
    else cout << power_plant(first_state, first_cnt);
}
