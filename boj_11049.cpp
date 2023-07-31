#include <iostream>
#include <vector>

using namespace std;

int N, r, c;
long long DP[501][501] = { };
vector<pair<int, int>> v;

long long my_matrix(int start, int end){
    if(start+1 > end) return 0;
    if(DP[start][end] != 0) return DP[start][end];
    DP[start][end] = 2e32 - 1;
    for(int i=start; i<end; i++){
        long long left = my_matrix(start, i);
        long long right = my_matrix(i+1, end);
        long long temp = left + right + v[start].first * v[i].second * v[end].second;
        DP[start][end] = min(DP[start][end], temp);
    }
    return DP[start][end];
}

int main()
{
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> r >> c;
        v.push_back({r, c});
    }
    cout << my_matrix(0, N-1);
}