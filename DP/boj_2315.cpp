#include <iostream>
#include <memory.h>

using namespace std;

int N, M, sum = 0;
pair<int, int> garo[1001];
int check[1001] = { };
long long DP[1001][1001] = { };

long long solve(int pl, int num, long long curCost){
    if(num < 1) return 0;
    if(DP[pl][num] != -1) return DP[pl][num];
    check[pl] = 1;
    
    int left = -1, right = -1;
    for(int i = pl+1; i<N+1; i++){
        if(!check[i]){
            right = i;
            break;
        }
    }
    
    for(int i = pl-1; i> 0; i--){
        if(!check[i]){
            left = i;
            break;
        }
    }
    
    if(right == -1){
        DP[pl][num] = solve(left, num-1, curCost - garo[left].second) + curCost * (garo[pl].first - garo[left].first);
    }
    else if(left == -1){
        DP[pl][num] = solve(right, num-1, curCost - garo[right].second) + curCost * (garo[right].first - garo[pl].first);
    }
    else{
        DP[pl][num] = min(solve(left, num-1, curCost - garo[left].second) + curCost * (garo[pl].first - garo[left].first), solve(right, num-1, curCost - garo[right].second) + curCost * (garo[right].first - garo[pl].first));
    }
    check[pl] = 0;
    return DP[pl][num];
}

int main()
{
    cin >> N >> M;
    for(int i=1; i<N+1; i++){
        cin >> garo[i].first >> garo[i].second;
        sum += garo[i].second;
    }
    memset(DP, -1, sizeof(DP));
    cout << solve(M, N, sum - garo[M].second);
}