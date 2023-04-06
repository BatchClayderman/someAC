#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<int> v;
        int temp;
        for (int i = 0; i < n; i++)
        {
            cin >> temp;
            v.push_back(temp);
        }

        long long sum = 0;
        long long ans = 0;
        priority_queue<int, vector<int>, greater<int>> pq1;

        for (int i = m; i < n; i++)
        {
            sum += v[i];
            if (v[i] < 0)
                pq1.push(v[i]);
            while (sum < 0)
            {
                int t1 = pq1.top();
                pq1.pop();
                sum -= 2 * t1;
                ans += 1;
            }
        }

        priority_queue<int> pq2;
        sum = 0;
        for (int i = m - 1; i >= 1; i--)
        {
            sum += v[i];
            if (v[i] > 0)
                pq2.push(v[i]);
            while (sum > 0)
            {
                int t2 = pq2.top();
                pq2.pop();
                sum -= 2 * t2;
                ans += 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}