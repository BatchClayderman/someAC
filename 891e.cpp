# include <bits/stdc++.h>
using namespace std;
 const int N = 2e5 + 10;
 int totalCnt, n, a[N], dp[N], pd[N], f[N];
long long ans;


inline void upd(int i)
{
	if (n < i)
		return;
	int inc = 0, dec = n + 1;
	if (pd[i - 1] < a[i])
		inc = max(inc, a[i - 1]);
	if (a[i - 1] < a[i])
		inc = max(inc, dp[i - 1]);
	if (a[i] < dp[i - 1])
		dec = min(dec, a[i - 1]);
	if (a[i] < a[i - 1])
		dec = min(dec, pd[i - 1]);
	if (inc == dp[i] && dec == pd[i])
		return;
	dp[i] = inc, pd[i] = dec;
	f[i] = 0;
	if (dec <= n || inc){
		upd(i + 1);
		f[i] = f[i + 1] + 1;
	}
	return;
}
 
int main()
{
	ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);
 	cin >> totalCnt;
	for (int cnt = 0; cnt < totalCnt; ++cnt)
	{
		ans = 0;
		memset(a, 0, sizeof(a));
		memset(dp, 0, sizeof(dp));
		memset(pd, 0, sizeof(pd));
		memset(f, 0, sizeof(f));
		cin >> n;
		for (int i = 1; i <= n; ++ i)
			cin >> a[i];
		for (int i = n; 1 <= i; -- i)
		{
			dp[i] = n + 1;
			pd[i] = 0;
			upd(i + 1);	
			f[i] = f[i + 1] + 1;
			ans += f[i];
		}
		cout << ans << '\n';
	}
 
	return 0;
}