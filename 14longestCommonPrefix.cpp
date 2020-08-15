#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string subString(const string src1, const string src2)
{
	int len = min(src1.length(), src2.length());
	int index = 0;
	while (index < len && src1[index] == src2[index] )
		index++;

	return src1.substr(0,index);

}
string longestCommonPrefix(vector<string>& strs) 
{
	int size = strs.size();
	string s;
	if (strs.empty() || size == 0)
		return "";
	if (size == 1)
		return strs[0];
	s = strs[0];
	for (int i = 1; i < size; i++)
	{
		if (strs[i].empty())
			return "";
		s = subString(s, strs[i]);
	}

	return s;
}
int main()
{
	//["flower","flow","flight"]
	//vector<string> nstr = { "flower","flow","flight" };
	vector<string> nstr = { "xxower","flow","flight" };

	int a1 = 5;
	string ss = "abcba";
	cout << longestCommonPrefix(nstr) << std::endl;
	char a = '(';
	char b = ')';
	int c = a + b;
	cout << c << std::endl;
	return 0;
}