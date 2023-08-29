#include <iostream>

using namespace std;


int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    int arr[10000];
    int cost[4] = {0, 3, 5, 7};
    int sum = 0;
    
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> arr[i];
    }
    
    for(int i=3; i>0; i--){
        for(int j=0; j<N-i+1; j++){
            int num = 10001;
            for(int k=0; k<i; k++) num = min(num, arr[j+k]);
            if(i == 3) {
                while(num && (arr[j] + arr[j+2] - 2 * num) < arr[j+1] - num) num--;
            }
            for(int k=0; k<i; k++) arr[j+k] -= num;
            sum += num * cost[i];
        }
    }
    
    cout << sum;
}
