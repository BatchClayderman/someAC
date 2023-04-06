#include <iostream>
#include <string>
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


/* handle input string */
vector<int> parseLine(const string& _line, char sep)
{
	vector<int> v;
	string line = "";
	for (int i = 0; i < _line.size(); ++i)
		if ((_line[i] >= '0' && _line[i] <= '9') || (_line[i] == sep && (line.size() > 0 && line[line.size() - 1] != sep)))
			line += _line[i];
	if (line.size() <= 0)
		return v;
	while (line[line.size() - 1] == sep)
		line = line.substr(0, line.size() - 1);
	if (line.size() <= 0)
		return v;
	size_t pos = 0, pos2 = 0, len = line.length();
	while (pos < len)
	{
		pos2 = line.find(sep, pos);
		if (pos2 == -1)
			pos2 = len;
		v.push_back(atoi(line.substr(pos, pos2 - pos).c_str()));
		pos = pos2 + 1;
	}
	return v;
}


/* handle problem LIS */
vector<int> getdp2(vector<int>& arr)
{
	vector<int> dp(arr.size(), 0);
	vector<int> ends(arr.size(), 0);
	ends[0] = arr[0];
	dp[0] = 1;
	int right = 0, l = 0, r = 0, m = 0;
	for (int i = 1; i < arr.size(); ++i)
	{
		l = 0;
		r = right;
		while (l <= r)
		{
			m = (l + r) / 2;
			if (arr[i] > ends[m])
				l = m + 1;
			else
				r = m - 1;
		}
		right = max(right, l);
		ends[l] = arr[i];
		dp[i] = l + 1;
	}
	return dp;
}

vector<int> generateLIS(vector<int>& arr, vector<int>& dp)
{
	int len = 0, index = 0;
	for (int i = 0; i < dp.size(); ++i)
		if (dp[i] > len)
		{
			len = dp[i];
			index = i;
		}
	vector<int> lis(len, 0);
	lis[--len] = arr[index];
	for (int i = index; i >= 0; --i)
		if (arr[i] < arr[index] && dp[i] == dp[index] - 1) // find subarray from back to front
		{
			lis[--len] = arr[i];
			index = i;
		}
	return lis;
}


/* Handle current problem */
bool checkDecreasing(vector<int>& arr, vector<int>& increasingArray)
{
	int lastRemain = INF;
	size_t j = 0;
	for (int i = 0; i < arr.size(); ++i)
		if (j < increasingArray.size() && arr[i] == increasingArray[j])
			++j;
		else if (arr[i] <= lastRemain) // check for decreasing ( = means not severe control)
			lastRemain = arr[i];
		else
			return false;
	return true;
}

bool checkSimple(vector<int>& arr)
{
	vector<int> dp = getdp2(arr);
	vector<int> increasingArray = generateLIS(arr, dp);
	if (increasingArray.size() <= 0)
		return false;
	else if (checkDecreasing(arr, increasingArray))
		return true;
	else
		return false;
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
			if (checkSimple(sub_arr))
				cnt += 1;
		}
	}
	return cnt;
}



int main()
{
	rewind(stdin);
	fflush(stdin);
	int totalCnt = 0;
	cin >> totalCnt;
	if (totalCnt <= 0)
		return EXIT_FAILURE;
	vector<string> line;
	for (int i = 0; i < totalCnt; ++i)
	{
		line.push_back("");
		rewind(stdin);
		fflush(stdin);
		getline(cin, line[i]);
		rewind(stdin);
		fflush(stdin);
		getline(cin, line[i]);
	}
	for (int i = 0; i < totalCnt; ++i)
	{
		vector<int> arr = parseLine(line[i], ' ');
		cout << countSimple(arr) << endl;
	}

	return EXIT_SUCCESS;
}