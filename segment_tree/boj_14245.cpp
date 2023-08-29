#include <iostream>
#include <vector>
#include <cmath>
#define ll long long

using namespace std;


class lazy_seg_tree{
private:
    const int N;
    vector<ll> v;
    vector<ll> lazy;
    vector<ll> seg_tree;
    ll resize_len;
public:
    lazy_seg_tree(int N_) : N(N_), resize_len(pow(2, ceil(log2(N)) + 1))
    {
        v.resize(N+1);
        lazy.resize(resize_len);
        seg_tree.resize(resize_len);
        
        for(int i=1; i<N+1; i++) cin >> v[i];
    }
    
    ll make_seg_tree(int node, int start, int end){
        if(start == end) return seg_tree[node] = v[start];
        int mid = (start + end) / 2;
        return seg_tree[node] =  make_seg_tree(node*2, start, mid) + make_seg_tree(node*2+1, mid+1, end);
    }
    
    void update(int node, int start, int end, int t_start, int t_end, ll t_value){
        if(t_start <= start && end <= t_end) {
            lazy[node] ^= t_value;
            return;
        }
        if(t_end < start || t_start > end) return;
        
        int mid = (start + end) / 2;
        update(node*2, start, mid, t_start, t_end, t_value);
        update(node*2+1, mid+1, end, t_start, t_end, t_value);
    }
    
    ll query(int node, int start, int end, int t_start, int t_end){
        if(lazy[node]){
            seg_tree[node] ^= lazy[node];
            if(node*2 < resize_len) lazy[node*2] ^= lazy[node];
            if(node*2+1 < resize_len) lazy[node*2+1] ^= lazy[node];
            lazy[node] = 0;
        }
        if(t_start <= start && end <= t_end) return seg_tree[node];
        if(t_end < start || t_start > end) return 0;
        
        int mid = (start + end) / 2;
        return query(node*2, start, mid, t_start, t_end) + query(node*2+1, mid+1, end, t_start, t_end);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, M;
    
    cin >> N;
    lazy_seg_tree * seg_tree = new lazy_seg_tree(N);
    seg_tree->make_seg_tree(1, 1, N);
    
    int a, b, c, d;
    cin >> M;
    for(int i=0; i<M; i++){
        cin >> a;
        if(a == 1){
            cin >> b >> c >> d;
            seg_tree->update(1, 1, N, b+1, c+1, d);
        }
        else{
            cin >> b;
            cout << seg_tree->query(1, 1, N, b+1, b+1) << '\n';
        }
    }
}
