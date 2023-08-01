#include <iostream>
#include <queue>
#define MAX_SIZE 1501

using namespace std;

struct swan{
    int y, x;
};

struct block{
    int y, x, date;
};

struct compare {
	bool operator()(const block& block_1, const block& block_2) {
		return block_1.date > block_2.date;
	}
};

int R, C;
char lake[MAX_SIZE][MAX_SIZE];
int melt_date[MAX_SIZE][MAX_SIZE] = { };
swan swans[2];
int dy[] = {1, -1, 0, 0};
int dx[] = {0, 0, 1, -1};

void check_melt_date(){
    bool visited[MAX_SIZE][MAX_SIZE] = { };
    queue<block> q;
    
    for(int i=1; i<R+1; i++){
        for(int j=1; j<C+1; j++){
            if(lake[i][j] == 'X') continue;
            
            for(int k=0; k<4; k++){
                int next_y = i+dy[k];
                int next_x = j+dx[k];
                
                if(next_y < 1 || next_x < 1 || next_x > C || next_y > R || lake[next_y][next_x] == '.' || visited[next_y][next_x]) continue;
                q.push({next_y, next_x, 1});
                melt_date[next_y][next_x]++;
                visited[next_y][next_x] = true;
            }
        }
    }
    
    while(!q.empty()){
        block cur_block = q.front();
        q.pop();
        
        for(int k=0; k<4; k++){
            int next_y = cur_block.y+dy[k];
            int next_x = cur_block.x+dx[k];
            int next_date = cur_block.date+1;
            if(next_y < 1 || next_x < 1 || next_x > C || next_y > R || lake[next_y][next_x] == '.' || visited[next_y][next_x]) continue;
            q.push({next_y, next_x, next_date});
            melt_date[next_y][next_x] = next_date;
            visited[next_y][next_x] = true;
        }
    }
}

int calc_max_date(){
    priority_queue<block, vector<block>, compare> pq;
    bool visited[MAX_SIZE][MAX_SIZE] = { };
    int ans = 0;
    int target_y = swans[1].y, target_x = swans[1].x;
    
    pq.push({swans[0].y, swans[0].x, 0});
    visited[swans[0].y][swans[0].x] = true;
    while(!pq.empty()){
        block cur_block = pq.top();
        pq.pop();
        
        for(int j=0; j<4; j++){
            int next_y = cur_block.y+dy[j];
            int next_x = cur_block.x+dx[j];
            if(next_y < 1 || next_x < 1 || next_x > C || next_y > R || visited[next_y][next_x]) continue;
            
            ans = max(ans, cur_block.date);
            if(target_y == next_y && target_x == next_x) return ans;
            
            
            pq.push({next_y, next_x, melt_date[next_y][next_x]});
            visited[next_y][next_x] = true;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    string str;
    
    cin >> R >> C;
    int idx = 0;
    for(int i=1; i<R+1; i++){
        cin >> str;
        for(int j=1; j<C+1; j++){
            lake[i][j] = str[j-1];
            if(str[j-1] == 'L') {
                swans[idx++] = {i, j};
                lake[i][j] = '.';
            }
        }
    }
    
    check_melt_date();
    cout << calc_max_date();
}