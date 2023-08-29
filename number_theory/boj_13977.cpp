#include <iostream>
#define ll long long
#define mod 1000000007

using namespace std;

ll factorial[4000001];

ll get_b_rev(ll current, ll num, ll cnt){
    while(cnt){
        if(cnt % 2) {
            current = ((current % mod) * num) % mod;
            cnt--;
        }
        else{
            num = ((num % mod) * (num % mod)) % mod;
            cnt /= 2;
        }
    }
    
    return current;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, K, T;
    
    cin >> T;
    factorial[0] = 1; factorial[1] = 1;
    for(int i=2; i<4000001; i++) factorial[i] = ((factorial[i-1] % mod) * i) % mod;
    while(T--){
        cin >> N >> K;
        cout << (factorial[N] % mod) * get_b_rev(1, ((factorial[N-K] % mod) * (factorial[K] % mod) % mod), mod-2) % mod << '\n';
    }
}