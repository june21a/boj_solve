#include <iostream>
#include <algorithm>
#include <vector>
#define max_num 1000001

using namespace std;

int arr[max_num];
vector<pair<int, int>> DP;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    int idx = 1, num;
    
    cin >> N;
    cin >> arr[0];
    DP.push_back({0, arr[0]});
    for(int i=1; i<N; i++){
        cin >> num;
        if(num > arr[idx-1]){
            arr[idx] = num;
            DP.push_back({idx, num}); 
            idx++;
        }
        else{
            int * ptr = lower_bound(arr, arr+idx, num);
            *ptr = num;
            DP.push_back({ptr - arr, num});
        }
    }
    
    
    cout << idx << '\n';
    int check_idx = idx-1;
    for(int i=DP.size()-1; i>-1; i--){
        if(DP[i].first == check_idx){
            arr[check_idx] = DP[i].second;
            check_idx--;
        }
    }
    
    for(int i=0; i<idx; i++) cout << arr[i] << ' ';
}