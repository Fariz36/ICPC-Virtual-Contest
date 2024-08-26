#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double

ll parse(string x){
    vector<int> st;

    ll dist = 0, sum = 0;
    for(int i = 0; i < (int)x.size(); ++i){
        if(x[i] == '('){
            st.push_back(i);
            dist++;
        }
        else if(x[i] == ')'){
            st.pop_back();
            if(x[i - 1] != x[i]){
                sum += dist - 1;
            }
            dist--;
        }
    }

    return sum;
}

void solve(){
    string s; cin >> s;

    cout << parse(s) << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int tc = 1; //cin >> tc;

    while(tc--){
        solve();
    }

    return 0;
}
