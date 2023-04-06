#include <iostream>
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif
#ifndef EOF
#define EOF (-1)
#endif
#ifndef NULL
#define NULL 0
#endif
using namespace std;
const int N = 2e5 + 10;
int totalCnt = NULL, n = NULL, a[N] = { NULL }, dp[N] = { NULL }, pd[N] = { NULL }, f[N] = { NULL };
long long int answer = NULL;


inline void update(int i)
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
	if (dec <= n || inc)
	{
		update(i + 1);
		f[i] = f[i + 1] + 1;
	}
	return;
}



int main()
{
	cin >> totalCnt;
	if (totalCnt <= NULL)
		return EXIT_FAILURE;

	for (int cnt = 0; cnt < totalCnt; ++cnt)
	{
		/* Initial */
		answer = NULL;
		memset(a, NULL, sizeof(a));
		memset(dp, NULL, sizeof(dp));
		memset(pd, NULL, sizeof(pd));
		memset(f, NULL, sizeof(f));

		/* Input per case */
		cin >> n;
		if (n <= NULL)
			return EXIT_FAILURE;

		/* Handle per case */
		for (int i = 1; i <= n; ++i)
			cin >> a[i];
		for (int i = n; 1 <= i; --i)
		{
			dp[i] = n + 1;
			pd[i] = 0;
			update(i + 1);
			f[i] = f[i + 1] + 1;
			answer += f[i];
		}
		cout << answer << endl;
	}

	return EXIT_SUCCESS;
}