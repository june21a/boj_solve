#define MAX 100001
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int V, E;
vector<int> v[MAX];
vector<pair<int, int>> ans;
int id[MAX] = { };
int idValue = 0;

int dfs(int current, int parent){
    id[current] = ++idValue;
    
    int result = id[current];
    for(int i=0; i<v[current].size(); i++){
        int next = v[current][i];
        if(next == parent) continue;
        if(!id[next]){
            int low = dfs(next, current);
            if(low > id[current]){
                int a = min(current, next);
                int b = max(current, next);
                
                ans.push_back({a, b});
            }
            result = min(result, low);
        }
        else{
            result = min(result, id[next]);
        }
    }
    
    return result;
}

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> V >> E;
    int st, en;
    for(int i=0; i<E; i++){
        cin >> st >> en;
        v[st].push_back(en);
        v[en].push_back(st);
    }
    
    for(int i=1; i<V+1; i++){
        if(!id[i]) dfs(i, 0);
    }
    
    sort(ans.begin(), ans.end());
    auto last = unique(ans.begin(), ans.end());
    ans.erase(last, ans.end());
    cout << ans.size() << '\n';
    for(int i=0; i<ans.size(); i++) cout << ans[i].first << ' ' << ans[i].second << '\n';
}