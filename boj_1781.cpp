#include <iostream>
#include <queue>
#define ll long long

using namespace std;

struct homework{
    ll deadline;
    ll cupramen;
};

struct compare_1 {
	bool operator()(const homework& hw1, const homework& hw2) {
	    return hw1.cupramen < hw2.cupramen;
	}
};

struct compare_2 {
	bool operator()(const homework& hw1, const homework& hw2) {
	    return hw1.deadline < hw2.deadline;
	}
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    ll dl, cup;
    priority_queue<homework, vector<homework>, compare_2> d_pq;
    priority_queue<homework, vector<homework>, compare_1> c_pq;
    ll ans = 0;
    
    
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> dl >> cup;
        d_pq.push({dl, cup});
    }
    while(N){
        while(!d_pq.empty() && d_pq.top().deadline == N){
            c_pq.push(d_pq.top());
            d_pq.pop();
        }
        
        if(!c_pq.empty()){
            ans += c_pq.top().cupramen;
            c_pq.pop();
        }
        N--;
    }
    
    
    cout << ans;
    return 0;
}