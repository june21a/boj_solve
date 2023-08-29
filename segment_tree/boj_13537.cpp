#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int arr[100001];
vector<vector<int>> v;

vector<int> make_tree(int node, int start, int end){
    if (start == end) {
        v[node].push_back(arr[start]);
        return v[node];
    }
    
    int mid = (start + end) / 2;
    vector<int> a = make_tree(node*2, start, mid);
    vector<int> b = make_tree(node*2+1, mid+1, end);
    
    int idx_a = 0, idx_b = 0;
    while(idx_a < a.size() && idx_b < b.size()){
        if(a[idx_a] > b[idx_b]) v[node].push_back(b[idx_b++]);
        else v[node].push_back(a[idx_a++]);
    }
    
    while(idx_a < a.size()) v[node].push_back(a[idx_a++]);
    while(idx_b < b.size()) v[node].push_back(b[idx_b++]);
    return v[node];
}

int query(int node, int start, int end, int a, int b, int target){
    if(a > end || b < start) return 0;
    
    if (a <= start && end <= b) {
        int idx = upper_bound(v[node].begin(), v[node].end(), target) - v[node].begin();
        return (v[node].size() - idx);
    }
    if(start == end){
        return (v[node][0] > target ? 1:0);
    }
    
    int mid = (start + end) / 2;
    return query(node*2, start, mid, a, b, target) + query(node*2+1, mid+1, end, a, b, target);
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, M;
    int a, b, c;
    
    cin >> N;
    v.resize(pow(2, ceil(log2(N)) + 1), vector<int>(0));
    for(int i=0; i<N; i++){
        cin >> arr[i];
    }
    make_tree(1, 0, N-1);
    
    cin >> M;
    for(int i=0; i<M; i++){
        cin >> a >> b >> c;
        cout << query(1, 0, N-1, a-1, b-1, c) << '\n';
    }
}
