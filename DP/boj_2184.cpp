#include <iostream>
#include <memory.h>
#include <algorithm>

using namespace std;

int N, L;
long long D[1010] = { };
long long DP[1010][1010][2];

long long gimchi(int right, int left, int isRight, long long current){
    if(left < 2 && right > N-1) return 0;
    if(DP[left][right][isRight] != -1) return DP[left][right][isRight];
    
    long long a, b;
    if(left > 1) a = gimchi(right, left-1, 0, current-1) + current * (isRight ? (D[right]-D[left-1]):(D[left]-D[left-1]));
    else a = 2e31-1;
    if(right < N) b = gimchi(right+1, left, 1, current-1) + current * (isRight ? (D[right+1]-D[right]):(D[right+1]-D[left]));
    else b = 2e31-1;
    
    return DP[left][right][isRight] = min(a, b);
}

int main()
{
    int k = 0;
    memset(DP, -1, sizeof(DP));
    cin >> N >> L;
    for(int i=1; i<N+1; i++){
        cin >> D[i];
    }
    sort(&D[1], &D[N+1]);
    for(int i=1; i<N+1; i++){
        if(D[i] <= L) k = i;
    }
    if(D[k] == L || k > N-1) cout << gimchi(k, k, 0, N-1) + (L-D[k])*N;
    else if(k == 0){
        cout << gimchi(1, 1, 0, N-1) + (D[1]- L)*N;
    }
    else{
        cout << min(gimchi(k, k, 0, N-1) + (L-D[k])*N, gimchi(k+1, k+1, 0, N-1) + (D[k+1]-L) * N);
    }
}