#include <iostream>
#include <string>
#include <vector>

using namespace std;
bool isValidPalindrome(string s, int left, int right);
string longestPalindrome(string s);


bool isValidPalindrome(string s,int left,int right)
{
	while (left < right)
	{
		if (s[left++] != s[right--])
			return false;
	}
	return true;
}

//1.暴力求解
string longestPalindrome(string s) {
	int len = s.length();
	int maxLen = 1;
	int start = 0;
	for (int i = 0; i < len; i++)
	{
		for(int j = i + 1; j < len;j++)
		{
			if (j - i + 1 > maxLen && isValidPalindrome(s, i, j))
			{
				maxLen = j - i + 1;
				start = i;
			}
		}
	}
	return s.substr(start, maxLen);
}

//2 动态规划
//对于一个子串而言，如果它是回文串，并且长度大于 2，那么将它首尾的两个字母去除之后，它仍然是个回文串。
//例如对于字符串“ababa”，如果我们已经知道“bab” 是回文串，那么 “ababa” 一定是回文串，这是因为它的首尾两个字母都是“a”。
//根据这样的思路，我们就可以用动态规划的方法解决本题。我们用 P(i,j) 表示字符串s的第 i到 j个字母组成的串（下文表示成 s[i:j]）是否为回文串：
//
//                   |   true,  如果字串 S[i,j]是回文串 
//         p(i,j) =  |                                         其他情况:1.s[i,j] 本身不是回文串 2.i > j 不合法
//					 |   false	其他情况
//
// 动态规划转移方程： p(i,j) = p(i+1,j-1) &(S[i] == S[j))
//
//注意边界情况串长度为1时和串为长度2时且连个字母都相同才是回文串
//		
//			|p(i,j) = true
//			|
//			|p(i,i+1) = （S[i] == S[i+1]) 
//注意：在状态转移方程中，我们是从长度较短的字符串向长度较长的字符串进行转移的，因此一定要注意动态规划的循环顺序
string longestPalindrome_dp(string s) {
	int n = s.length();
	vector<vector<int>>dp(n, vector<int>(n));
	string result;
	//sublen 字串的长度
	for (int sublen = 0; sublen < n; sublen++)
		for (int i = 0; i + sublen < n; i++)
		{
			int j = i + sublen;
			if (sublen == 0)
			{
				//字符串长度是1情况
				dp[i][j] = 1;
			}
			else if (sublen == 1)
			{
				//字符串长度为2的情况
				dp[i][j] = (s[i] == s[j]);
			}
			else
			{
				//p(i,j) = p(i+1,j-1) &(S[i] == S[j))
				dp[i][j] = (s[i] == s[j]) && (dp[i + 1][j - 1]);
			}
			if (dp[i][j] && sublen + 1 > result.size())
			{
				//当前子串是回文串且长度大于结果中的回文串长度
				//sublen + 1是因为sublen是从0开始的
				result = s.substr(i, sublen + 1);
			}
		}
	return result;
}
int main()
{
	int a = 5;
	string ss = "abcba";
	cout << longestPalindrome_dp(ss) << endl;
	return 0;
}