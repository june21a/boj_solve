#define MAX 10001
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int V, E;
vector<int> v[MAX];
int id[MAX] = { };
int idValue = 0;
vector<int> ans;
bool visited[MAX] = { };

int dfs(int current, bool root){
    id[current] = ++idValue;
    int result = id[current];
    
    int child = 0;
    for(int i=0; i<v[current].size(); i++){
        int next = v[current][i];
        if(id[next] == 0){
            int low = dfs(next, false);
            child++;
            result = min(result, low);
            if(low >= id[current] && !root && !visited[current]){
                ans.push_back(current);
                visited[current] = true;
            }
        }
        else{
            result = min(result, id[next]);
        }
    }
    
    if(root && child >= 2 && !visited[current]){
        ans.push_back(current);
        visited[current] = true;
    }
    return result;
}

int main()
{
    cin >> V >> E;
    int st, en;
    for(int i=0; i<E; i++){
        cin >> st >> en;
        v[st].push_back(en);
        v[en].push_back(st);
    }
    
    for(int i=1; i<V+1; i++){
        if(id[i] == 0) dfs(i, true);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for(int i=0; i<ans.size(); i++) cout << ans[i] << ' ';
}