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
 * [3] ���ظ��ַ�����Ӵ�
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
 * [76] ��С�����Ӵ�
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
 * [239] �����������ֵ
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
	//���ַ�Ϊ������¼�ַ����ַ�����λ�� 
	// ����unorderd_set/unorderd_map
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
	//��¼��С�����ִ�����ʼ����������
	int start = 0, len = INT_MAX;
	while (right < s.size())
	{
		//c�ǽ����봰�ڵ��ַ�
		char c = s[right];
		if (need.count(c))
		{
			window[c]++;
			if (window[c] == need[c])
				valid++;
		}
		//��������
		right++;

		while (valid == need.size())
		{
			if (right - left < len)
			{
				start = left;
				len = right - left;
			}
			//d�ǽ��Ƴ����ڵ��ִ�
			char d = s[left];
			//���ƴ���
			left++;
			//�Ƿ����ִ��е�Ԫ��
			if (need.count(d))
			{
				//�����е�Ԫ�غ��ִ��е�Ԫ�ظ������
				if (window[d] == need[d])
					valid--;//���ٰ����ִ�Ԫ���ĸ���
				window[d]--;//�����е�Ԫ����������
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
	//int maxNum = INT_MIN;; // ��¼���
	 
	while (right < nums.size())
	{
		if (right < k - 1)
		{
			//�ȴ������Ѿ��е�ֵ���Ƴ������е�Сֵ
			//��֤front()ֵ���
			while(!window.empty() && window.back() < nums[right])
				window.pop_back();
			window.push_back(nums[right]);
		}
		else
		{
			//�ƶ�����
			while(!window.empty() && window.back() < nums[right])
				window.pop_back();

			window.push_back(nums[right]);
			result.push_back(window.front());
			//������д����к��д�����߽��ֵ �Ƴ��󴰿ڵ�ֵ
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
	int maxNum = INT_MIN;; // ��¼���

	while (right < nums.size())
	{
		// �ж���ര���Ƿ�Ҫ����
		while (right < nums.size() && (right - left) == (k - 1))
		{

			for (int i = left; i <= right; i++)
			{
				maxNum = max(maxNum, nums[i]);
			}
			left++;
		}
		right++;
		// ��������´�
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
