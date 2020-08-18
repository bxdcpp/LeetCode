#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <deque>


using namespace std;
/*
 * @lc app=leetcode.cn id=3 lang=cpp
 *
 * [3] 无重复字符的最长子串
 *
 * @difficulity:Medium
 *
 * @tag:hash-table|two-pointers|string|sliding-windos
 */

 // @lc code=start

int lengthOfLongestSubstring(string s);

/*
 * @lc app=leetcode.cn id=76 lang=cpp
 *
 * [76] 最小覆盖子串
 *
 * @difficulity:Hard
 *
 * @tag:hash-table|two-pointers|string|sliding-windos
 */

 // @lc code=start
string minWindow(string s, string t);


/*
 * @lc app=leetcode.cn id=239  lang=cpp
 *
 * [239] 滑动窗口最大值
 *
 * @difficulity:Hard
 *
 * @tag:hash-table|two-pointers|string|sliding-windos
 */

 // @lc code=start
vector<int> maxSlidingWindow(vector<int>& nums, int k);
vector<int> maxSlidingWindow_violence(vector<int>& nums, int k);


int lengthOfLongestSubstring(string s)
{
	int n = s.length();
	int result = 0;
	//以字符为索引记录字符在字符串中位置 
	// 代替unorderd_set/unorderd_map
	int charIndex[256] = {0};
	for (int right = 0,left = 0; right < n; right++)
	{
		char c = s[right];
		left = max(charIndex[c], left);
		result = max(result, right - left + 1);
		charIndex[c] = right + 1;
	}
	return result;
}

string minWindow(string s, string t)
{
	unordered_map<char, int>need, window;
	for (auto c : t) need[c]++;
	int left = 0, right = 0;
	int valid = 0;
	//记录最小覆盖字串的起始索引及长度
	int start = 0, len = INT_MAX;
	while (right < s.size())
	{
		//c是将移入窗口的字符
		char c = s[right];
		if (need.count(c))
		{
			window[c]++;
			if (window[c] == need[c])
				valid++;
		}
		//窗口右移
		right++;

		while (valid == need.size())
		{
			if (right - left < len)
			{
				start = left;
				len = right - left;
			}
			//d是将移除窗口的字串
			char d = s[left];
			//左移窗口
			left++;
			//是否是字串中的元素
			if (need.count(d))
			{
				//窗口中的元素和字串中的元素个数相等
				if (window[d] == need[d])
					valid--;//减少包含字串元数的个数
				window[d]--;//窗口中的元数个数减少
			}

		}
	}
	return len == INT_MAX ? "" : s.substr(start, len);
}

vector<int> maxSlidingWindow(vector<int>& nums, int k)
{
	vector<int> result;
	deque<int> window;
	int  right = 0;
	//int maxNum = INT_MIN;; // 记录结果
	 
	while (right < nums.size())
	{
		if (right < k - 1)
		{
			//比窗口中已经有的值大，移除窗口中的小值
			//保证front()值最大
			while(!window.empty() && window.back() < nums[right])
				window.pop_back();
			window.push_back(nums[right]);
		}
		else
		{
			//移动窗口
			while(!window.empty() && window.back() < nums[right])
				window.pop_back();

			window.push_back(nums[right]);
			result.push_back(window.front());
			//如果队列窗口中含有窗口左边界的值 移除左窗口的值
			if (!window.empty() && window.front() == nums[right - k + 1])
				window.pop_front();

		}
		right++;

	}
	return result;
}

vector<int> maxSlidingWindow_violence(vector<int>& nums, int k)
{
	vector<int> window;
	int left = 0, right = left + k - 1;
	int maxNum = INT_MIN;; // 记录结果

	while (right < nums.size())
	{
		// 判断左侧窗口是否要收缩
		while (right < nums.size() && (right - left) == (k - 1))
		{

			for (int i = left; i <= right; i++)
			{
				maxNum = max(maxNum, nums[i]);
			}
			left++;
		}
		right++;
		// 在这里更新答案
		window.push_back(maxNum);
		maxNum = INT_MIN;

	}
	return window;
}

void printVec(vector<int> v)
{
	for (auto it : v)
	{
		cout << " " << it;
	}
	cout << endl;
}

int main()
{
	string caseStr = "abcabcbb";
	vector<int> numsVec{ 1,3,-1,-3,5,3,6,7 };
	int k = 3;

	cout << "----------------------------------------------------------------------------------" << endl;
	cout << "lengthOfLongestSubstring:" << lengthOfLongestSubstring(caseStr) << std::endl;
	cout << "----------------------------------------------------------------------------------" << endl;

	cout << "----------------------------------------------------------------------------------" << endl;
	printVec(maxSlidingWindow(numsVec, k));
	cout << "----------------------------------------------------------------------------------" << endl;
	
	return 0;
}
