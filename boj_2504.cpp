#include <iostream>
#include <stack>

using namespace std;

int main()
{
    string str;
    int len;
    stack<char> st;
    int result = 0;
    int tmp = 1;
    bool check = false;
    
    cin >> str;
    len = str.length();
    for(int i=0; i<len; i++){
        if(str[i] == '('){
            tmp *= 2;
            st.push('(');
            check = false;
        }
        else if(str[i] == '['){
            tmp *= 3;
            st.push('[');
            check = false;
        }
        else{
            if(st.empty() || (str[i] == ')' && st.top() != '(') || (str[i] == ']' && st.top() != '[')){
                result = 0;
                break;
            }
            else if(str[i] == ')'){
                if(!check){
                    result += (tmp);
                    check = true;
                }
                tmp /= 2;
            }
            else{
                if(!check){
                    result += (tmp);
                    check = true;
                }
                tmp /= 3;
            }
            st.pop();
        }
    }
    
    if(st.empty()) cout << result;
    else cout << 0;
}