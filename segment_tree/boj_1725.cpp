#include <iostream>   
#include <vector>
#include <algorithm>
#define ll long long
#define MAX_ARR_LEN 100001

using namespace std;

ll arr[MAX_ARR_LEN] = { };
vector<ll> v;
ll ans = 0;

ll make_stree(int start, int end, int node){
    if(start == end) {
        return v[node] = start;
    }
    
    int mid = (start + end) / 2;
    ll left = make_stree(start, mid, node*2);
    ll right = make_stree(mid+1, end, node*2+1);
    if(arr[left] > arr[right]) return v[node] = right;
    else return v[node] = left;
}

ll get_min_height(int start, int end, int node, int b, int c){
    if(c < start || b > end) return 0;
    if(b <= start && end <= c) return v[node];
    
    int mid = (start+end) / 2;
    ll left = get_min_height(start, mid, node*2, b, c);
    ll right = get_min_height(mid+1, end, node*2+1, b, c);
    if(arr[left] > arr[right]) return right;
    else return left;
}

void solve(int start, int end, int N){
    if(end < start) return;
    
    int min_idx = get_min_height(1, N, 1, start, end);
    ans = max(ans, arr[min_idx] * (end-start + 1));
    solve(start, min_idx-1, N);
    solve(min_idx+1, end, N);
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    
    cin >> N;
    for(int i=1; i<N+1; i++) cin >> arr[i];
    arr[0] = 1000000001;
    v.resize(N * 4, 0);
    make_stree(1, N, 1);
    solve(1, N, N);
    
    cout << ans;
}