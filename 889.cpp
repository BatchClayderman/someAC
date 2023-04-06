#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> v;
        int temp;
        for (int i = 1; i <= n; i++)
        {
            cin >> temp;
            v.push_back(temp);
        }
        sort(v.begin(), v.end());
        int ans = 0;

        if (0 < v[0])
            ans++;

        for (int i = 0; i < n - 1; i++)
        {
            if (i + 1 > v[i] && i + 1 < v[i + 1])
                ans++;
        }

        if (n > v[n - 1])
            ans++;
        cout << ans << endl;
    }
    return 0;
}