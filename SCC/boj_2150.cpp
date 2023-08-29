#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

int V, E;
vector<int> v[10001];
vector<vector<int>> ans;
int id[10001] = { };
bool isCSS[10001] = { };
int idIndex = 0;
stack<int> st;


int dfs(int currentNode){
    id[currentNode] = ++idIndex;
    
    int result = id[currentNode];
    st.push(currentNode);
    for(int i=0; i<v[currentNode].size(); i++){
        int next = v[currentNode][i];
        if(!id[next]){
            result = min(result, dfs(next));
        }
        else if(!isCSS[next]){
            result = min(result, id[next]);
        }
    }
    
    if(result == id[currentNode]){
        vector<int> tmp;
        while(1){
            int num = st.top();
            st.pop();
            isCSS[num] = true;
            tmp.push_back(num);
            if(num == currentNode){
                sort(tmp.begin(), tmp.end());
                ans.push_back(tmp);
                break;
            }
        }
    }
    
    return result;
}

int main()
{
    int st, en;
    cin >> V >> E;
    for(int i=0; i<E; i++){
        cin >> st >> en;
        v[st].push_back(en);
    }
    for(int i=1; i<V+1; i++){
        if(!id[i]) dfs(i);
    }
    
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for(int i=0; i<ans.size(); i++){
        for(int j=0; j<ans[i].size(); j++) cout << ans[i][j] << ' ';
        cout << -1 << '\n';
    }
}