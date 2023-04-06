#include"bits/stdc++.h"
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define int long long
#define endl '\n'
#define maxn 200010
#define PII pair<int,int>
#define PIII pair<int,PII>
#define mod 998244353
int dp[maxn];
signed main(void){
    IOS
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        string s;
        cin>>s;
        s=" "+s;
        dp[1]=1;
        for(int i=2;i<=n;i++){
            //cout<<dp[i]<<" "<<dp[i-1]<<endl;
            dp[i]=s[i]==s[i-1]?2*dp[i-1]:1;
            dp[i]%=mod;
        }
        int res=0;
        for(int i=1;i<=n;i++){
            res+=dp[i];
            res%=mod;
        }
        cout<<res<<endl;
    }
    return 0;
}
