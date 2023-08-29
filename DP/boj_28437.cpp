#include <iostream>
#include <cmath>
#include <vector>
#include <memory.h>
#define max_num 100001
#define ll long long

using namespace std;

bool check[max_num] = { };
vector<int> primes;
ll DP[max_num];
int one_check = 0;

void get_all_primes(){
    int max_iter = ceil(sqrt(max_num))+1;

    check[1] = true;
    for(int i=2; i<max_iter; i++){
        if(check[i]) continue;
        for(int j=i+1; j<max_num; j++){
            if(j % i) continue;
            check[j] = true;
        }
    }

    for(int i=2; i<max_num; i++){
        if(check[i]) continue;
        primes.push_back(i);
    }
}

ll get_long_stick(int target){
    if(DP[target] != -1) return (DP[target] + DP[1]);
    if(!check[target]) return DP[target] = (1 + DP[1]);
}

int main(){
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    
    int N, M, input;
    int arr[max_num];


    get_all_primes();
    DP[1] = 0;
    memset(DP, -1, sizeof(DP));
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> arr[i];
        if(arr[i] == 1) DP[1] = 1;
        if(!check[arr[i]]) DP[arr[i]]++;
    }
    
    cin >> M;
    for(int i=0; i<M; i++){
        cin >> input;
        ll ans = 0;
        for(int j=0; j<N; j++){
            if(input % arr[j]) continue;
            int target = (input / arr[j]);
            ans += get_long_stick(target);
        }
    }
}