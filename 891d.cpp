#include <iostream>
#include <vector>
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
#ifndef INF
#define INF 0x7FFFFFFF
#endif
using namespace std;


bool checkSimple(vector<int>& a)
{
	size_t n = a.size();
	vector<int> asc, des;
	asc.push_back(EOF);
	des.push_back(INF);
	for (size_t i = 0; i < n; ++i)
	{
		int ab = asc.back(), db = des.back();
		if (ab < a[i] && db <= a[i]) // increasing subsequence only
			asc.push_back(a[i]);
		
		else if (ab >= a[i] && db > a[i]) // decreasing subsequence only
			des.push_back(a[i]);
		
		else if (ab >= a[i] && db <= a[i]) // no subsequences allowed
			return false;
		
		else//if (ab < a[i] && db > a[i]) // both subsequences allowed
		{
			if (i == n - 1)
				asc.push_back(a[i]);
			else
			{
				if (a[i] < a[i + 1])
					asc.push_back(a[i]);
				else if (a[i] > a[i + 1])
					des.push_back(a[i]);
				else
					asc.push_back(a[i]);
			}
		}
	}
	return true;
}

int countSimple(vector<int>& arr)
{
	int cnt = 0;
	for (int i = 0; i < arr.size(); ++i)
	{
		vector<int> sub_arr;
		for (int j = i; j < arr.size(); ++j)
		{
			sub_arr.push_back(arr[j]);
			if (sub_arr.size() <= 2 || checkSimple(sub_arr))
				cnt += 1;
		}
	}
	return cnt;
}



int main()
{
	int totalCnt = NULL;
	cin >> totalCnt;
	if (totalCnt <= NULL)
		return EXIT_FAILURE;
	vector<string> line;
	for (int i = 0; i < totalCnt; ++i)
	{
		int perLineCnt = NULL;
		cin >> perLineCnt;
		if (perLineCnt <= NULL)
			return EXIT_FAILURE;
		vector<int> arr(perLineCnt);
		for (int j = 0; j < perLineCnt; ++j)
			cin >> arr[j];
		cout << countSimple(arr) << endl;
	}

	return EXIT_SUCCESS;
}