#include <bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline")
using namespace std;
int mod=998244353;
int T,n,a[100005],f[350*350*2+1000],g[350*350*2+1000],vis[350*350*2+1000];
queue<int> q,p; 
int main()
{
	scanf("%d",&T);
	int d=122500;
	while (T--)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;++i)	scanf("%d",&a[i]);
		
		f[a[2]+d]=1;
		q.push(a[2]);
		for (int i=2;i<n;++i)
		{
			int len=q.size();
			for (int j=1;j<=len;++j) 
			{
				int x=q.front(); q.pop();
				int y=a[i+1]+x;
				int z=a[i+1]-x;
				if (x==0) 
				{
					if (!vis[y+d]) 
					{
					q.push(y);
					p.push(y);
					vis[y+d]=1;
					}
					g[y+d]=(g[y+d]+f[x+d]);
					if (g[y+d]>=mod) g[y+d]-=mod;
				}
				else
				{
					if (!vis[y+d])
					{
						q.push(y);
						p.push(y);
						vis[y+d]=1;
					}
					g[y+d]=(g[y+d]+f[x+d]);
					if (g[y+d]>=mod) g[y+d]-=mod;
					if (!vis[z+d])
					{
						q.push(z);
						p.push(z);
						vis[z+d]=1;
					}
					g[z+d]=(g[z+d]+f[x+d]);
					if (g[z+d]>=mod) g[z+d]-=mod;
				}
				f[x+d]=0;
			}
			while (p.size())
			{
				int x=p.front();
				p.pop();
				if (g[x+d])
				f[x+d]=g[x+d];
				g[x+d]=0;
				vis[x+d]=0;
			}
		}
		int ans=0;
		for (int i=0;i<=350*350*2;++i)	{ ans=(ans+f[i]); if (ans>=mod) ans-=mod; f[i]=g[i]=vis[i]=0; } 
		while (q.size()) q.pop();
		while (p.size()) p.pop(); 
		printf("%d\n",ans);
	}
	return 0;
}
