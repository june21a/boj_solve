#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#define pi acos(-1)

using namespace std;

void FFT(vector<complex<double>> &f, complex<double> c) {
    int N = f.size();
    if(N == 1) return;
    
    vector<complex<double>> even(N/2), odd(N/2);
    for(int i=0; i<N; i++) {
        (i%2 ? odd:even)[i/2] = f[i];
    }
    
    FFT(even, c*c);
    FFT(odd, c*c);
    
    complex<double> cp(1, 0);
    for(int i=0; i<N/2; i++){
        f[i] = even[i] + cp*odd[i];
        f[i+N/2] = even[i] - cp*odd[i];
        cp *= c;
    }
}

vector<complex<double>> convolution(vector<complex<double>> f1, vector<complex<double>> f2) {
    int n = 1;
    int f_size = f1.size();
    
    while(n <= f_size) n *= 2;
    n *= 2;
    f1.resize(n); f2.resize(n); 
    vector<complex<double>> result(n);
    complex<double> c(cos(2 * pi / n), sin(2 * pi / n));
    
    FFT(f1, c);
    FFT(f2, c);
    for(int i=0; i<n; i++) result[i] = f1[i] * f2[i];
    
    complex<double> cp(1, 0);
    FFT(result, cp / c);
    
    for(int i=0; i<n; i++){
        result[i] /= complex<double>(n, 0);
        result[i] = complex<double>(round(result[i].real()), round(result[i].imag()));
    }
    return result;
}

int get_comp_vector(vector<complex<double>> &v){
    string str;
    cin >> str;
    int l = str.length();
    for(int i=0; i<l; i++){
        complex<double> c(str[i]-'0', 0);
        v[i] = c;
    }
    
    return l;
}

vector<complex<double>> v_1;
vector<complex<double>> v_2;

int main()
{
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int N, input;
    v_1.resize(300000);
    v_2.resize(300000);
    
    int max_l = -1;
    max_l += get_comp_vector(v_1);
    max_l += get_comp_vector(v_2);
    vector<complex<double>> res = convolution(v_1, v_2);
    
    vector<int> ans;
    int last_num = 0, current;
    int l = res.size()-1;
    for(int i=l; i>-1; i--){
        current = int(res[i].real()) + last_num;
        ans.push_back(current % 10);
        last_num = current /= 10;
    }
    
    if(last_num) cout << last_num;
    for(int i = ans.size()-1; i > ans.size()-max_l-1; i--) cout << ans[i];
}