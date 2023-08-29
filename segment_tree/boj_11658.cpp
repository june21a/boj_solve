#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int N;
int arr[1025][1025];
vector<vector<int>> seg_tree;
int h = 1;

void update(int x, int y, int value){
    int x1 = x+h-1, y1=y+h-1;
    seg_tree[x1][y1] = value;
    
    while(y1 > 1){
        y1 /= 2;
        seg_tree[x1][y1] = seg_tree[x1][y1*2] + seg_tree[x1][y1*2+1];
    }
    
    while(x1 > 1){
        x1 /= 2;
        y1 = y+h-1;
        seg_tree[x1][y1] = seg_tree[x1*2][y1] + seg_tree[x1*2+1][y1];
        while(y1 > 1){
            y1 /= 2;
            seg_tree[x1][y1] = seg_tree[x1][y1*2] + seg_tree[x1][y1*2+1];
        }
    }
}

int seg_query_y(int node, int start, int end, int bound1, int bound2, int cur){
    if(bound2 < start || bound1 > end) return 0;
    if(bound1 <= start && end <= bound2) return seg_tree[cur][node];
    int mid = (start + end) / 2;
    return seg_query_y(node*2, start, mid, bound1, bound2, cur) + seg_query_y(node*2+1, mid+1, end, bound1, bound2, cur);
}

int seg_query_x(int node, int start, int end, int bound_x1, int bound_y1, int bound_x2, int bound_y2){
    if(bound_x2 < start || bound_x1 > end) return 0;
    if(bound_x1 <= start && end <= bound_x2) {
        return seg_query_y(1, 1, N, bound_y1, bound_y2, node);
    }
    int mid = (start + end) / 2;
    return seg_query_x(node*2, start, mid, bound_x1, bound_y1, bound_x2, bound_y2) + seg_query_x(node*2+1, mid+1, end, bound_x1, bound_y1, bound_x2, bound_y2);
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int M;
    
    cin >> N >> M;
    while(h < N) h <<= 1;
    seg_tree.resize(h*2, vector<int>(h*2, 0));
    for(int i=1; i<N+1; i++){
        for(int j=1; j<N+1; j++) {
            cin >> arr[i][j];
            update(i, j, arr[i][j]);
        }
    }
    
    int w, c;
    int x1, y1, x2, y2;
    for(int i=0; i<M; i++){
        cin >> w;
        if(w){
            cin >> x1 >> y1 >> x2 >> y2;
            cout << seg_query_x(1, 1, N, x1, y1, x2, y2) << '\n';
        }
        else{
            cin >> x1 >> y1 >> c;
            update(x1, y1, c);
        }
    }
}