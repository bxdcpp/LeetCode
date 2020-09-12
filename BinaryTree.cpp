#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

//Definition for a binary tree node.
 struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/*
 * @lc app=leetcode.cn id=105 lang=cpp
 *
 * [105] ��ǰ��������������й��������
 *
 * @difficulity:Medium
 *
 * @tags: array | tree | depth-first-search
 *
 */
 //��ָoffer07
//https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/solution/cong-qian-xu-yu-zhong-xu-bian-li-xu-lie-gou-zao-9/
 TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder);
 TreeNode* myBuildTree(const vector<int>& preorder, const vector<int>& inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right);

 //�ǵݹ�
TreeNode* buildTree_2(vector<int>& preorder, vector<int>& inorder);

 unordered_map<int, int> index;//����������� value: index
 TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
 {
	 int n = preorder.size();
	 // �����ϣӳ�䣬�������ǿ��ٶ�λ���ڵ�
	 for (int i = 0; i < n; ++i) {
		 index[inorder[i]] = i;
	 }
	 return myBuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
 }

 TreeNode* myBuildTree(const vector<int>& preorder, const vector<int>& inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right)
 {
	 if(preorder_left > preorder_right)
		return nullptr;
	 // ǰ������еĵ�һ���ڵ���Ǹ��ڵ�
	 int preorder_root = preorder_left;
	 // ����������ж�λ���ڵ�
	 int inorder_root = index[preorder[preorder_root]];
	 // �ȰѸ��ڵ㽨������
	 TreeNode* root = new TreeNode(preorder[preorder_root]);
	 // �õ��������еĽڵ���Ŀ
	 int size_left_subtree = inorder_root - inorder_left;
	 // �ݹ�ع����������������ӵ����ڵ�
	   // ��������С��� ��߽�+1 ��ʼ�� size_left_subtree����Ԫ�ؾͶ�Ӧ����������С��� ��߽� ��ʼ�� ���ڵ㶨λ-1����Ԫ��
	 root->left = myBuildTree(preorder, inorder, preorder_left + 1, preorder_left + size_left_subtree, inorder_left, inorder_root - 1);
	 // �ݹ�ع����������������ӵ����ڵ�
		// ��������С��� ��߽�+1+�������ڵ���Ŀ ��ʼ�� �ұ߽硹��Ԫ�ؾͶ�Ӧ����������С��� ���ڵ㶨λ+1 �� �ұ߽硹��Ԫ��
	 root->right = myBuildTree(preorder, inorder, preorder_left + size_left_subtree + 1, preorder_right, inorder_root + 1, inorder_right);

	 return root;

 }

 /*������������
 ˼·

	 ��������һ�ַǳ������ʵ�ַ�����

	 ����ǰ������е��������������ڵ� uu �� vv������ǰ����������̣����ǿ���֪�� uu �� vv ֻ�����ֿ��ܵĹ�ϵ��

	 vv �� uu ������ӡ�������Ϊ�ڱ����� uu ֮����һ�������Ľڵ���� uu ������ӣ��� vv��

	 uu û������ӣ����� vv �� uu ��ĳ�����Ƚڵ㣨���� uu �������Ҷ��ӡ���� uu û������ӣ���ô��һ�������Ľڵ���� uu ���Ҷ��ӡ���� uu û���Ҷ��ӣ����Ǿͻ����ϻ��ݣ�ֱ��������һ�����Ҷ��ӣ��� uu ���������Ҷ��ӵ������У��Ľڵ� u_au
	 a

	 ����ô vv ���� u_au
	 a

	 ���Ҷ��ӡ�

	 �ڶ��ֹ�ϵ����ȥ��Щ���ӡ����Ǿ�һ��������˵������ȷ�ԣ����������и������ǵĵ����㷨��

	 ����

	 ��������


	 3
	 / \
	 9  20
	 /  /  \
	 8  15   7
	 / \
	 5  10
	 /
	 4
	 Ϊ��������ǰ���������������ֱ�Ϊ


	 preorder = [3, 9, 8, 5, 4, 10, 20, 15, 7]
	 inorder = [4, 5, 8, 10, 9, 3, 15, 20, 7]
	 ������һ��ջ stack ��ά������ǰ�ڵ�����л�û�п��ǹ��Ҷ��ӵ����Ƚڵ㡹��ջ�����ǵ�ǰ�ڵ㡣Ҳ����˵��ֻ����ջ�еĽڵ�ſ�������һ���µ��Ҷ��ӡ�ͬʱ��������һ��ָ�� index ָ�����������ĳ��λ�ã���ʼֵΪ 0��index ��Ӧ�Ľڵ��ǡ���ǰ�ڵ㲻�������ߴﵽ�����սڵ㡹����Ҳ�Ƿ�����������ģ���������������Ĺ����л��������֡�

	 �������ǽ����ڵ� 3 ��ջ���ٳ�ʼ�� index ��ָ��Ľڵ�Ϊ 4��������ǰ������е�ÿ���ڵ㣬���������ж�����ջ���ڵ������ӣ�����ջ��ĳ���ڵ���Ҷ��ӡ�

	 ���Ǳ��� 9��9 һ����ջ���ڵ� 3 ������ӡ�����ʹ�÷�֤�������� 9 �� 3 ���Ҷ��ӣ���ô 3 û������ӣ�index Ӧ��ǡ��ָ�� 3����ʵ����Ϊ 4����˲�����ì�ܡ��������ǽ� 9 ��Ϊ 3 ������ӣ����� 9 ��ջ��

	 stack = [3, 9]
	 index->inorder[0] = 4
	 ���Ǳ��� 8��5 �� 4��ͬ��ɵ����Ƕ�����һ���ڵ㣨ջ���ڵ㣩������ӣ��������ǻ�������ջ��

	 stack = [3, 9, 8, 5, 4]
	 index->inorder[0] = 4
	 ���Ǳ��� 10����ʱ����Ͳ�һ���ˡ����Ƿ��� index ǡ��ָ��ǰ��ջ���ڵ� 4��Ҳ����˵ 4 û������ӣ���ô 10 ����Ϊջ��ĳ���ڵ���Ҷ��ӡ���ô����ҵ�����ڵ��أ�ջ�еĽڵ��˳���������ǰ������г��ֵ�˳����һ�µģ�����ÿһ���ڵ���Ҷ��Ӷ���û�б�����������ô��Щ�ڵ��˳�����������������г��ֵ�˳��һ�����෴�ġ�

	 ������Ϊջ�е������������ڵĽڵ㣬ǰ�߶��Ǻ��ߵ�ĳ�����ȡ���������֪����ջ�е�����һ���ڵ���Ҷ��ӻ�û�б���������˵������һ����ǰ������ӵ������еĽڵ㣬��ô���߾�����ǰ�߳�������������С�

	 ������ǿ��԰� index ���������ƶ�������ջ���ڵ���бȽϡ���� index ��Ӧ��Ԫ��ǡ�õ���ջ���ڵ㣬��ô˵������������������ҵ���ջ���ڵ㣬���Խ� index ���� 1 ������ջ���ڵ㣬ֱ�� index ��Ӧ��Ԫ�ز�����ջ���ڵ㡣���������Ĺ��̣����ǵ��������һ���ڵ� x ���� 10 ��˫�׽ڵ㣬������Ϊ 10 �������� x �� x ��ջ�е���һ���ڵ���������֮�䣬��� 10 ���� x ���Ҷ��ӡ�

	 �ص����ǵ����ӣ����ǻ����δ�ջ������ 4��5 �� 8�����ҽ� index �����ƶ������Ρ����ǽ� 10 ��Ϊ��󵯳��Ľڵ� 8 ���Ҷ��ӣ����� 10 ��ջ��

	 stack = [3, 9, 10]
	 index->inorder[3] = 10
	 ���Ǳ��� 20��ͬ��index ǡ��ָ��ǰջ���ڵ� 10����ô���ǻ����δ�ջ������ 10��9 �� 3�����ҽ� index �����ƶ������Ρ����ǽ� 20 ��Ϊ��󵯳��Ľڵ� 3 ���Ҷ��ӣ����� 20 ��ջ��

	 stack = [20]
	 index->inorder[6] = 15
	 ���Ǳ��� 15���� 15 ��Ϊջ���ڵ� 20 ������ӣ����� 15 ��ջ��

	 stack = [20, 15]
	 index->inorder[6] = 15
	 ���Ǳ��� 7��index ǡ��ָ��ǰջ���ڵ� 15����ô���ǻ����δ�ջ������ 15 �� 20�����ҽ� index �����ƶ������Ρ����ǽ� 7 ��Ϊ��󵯳��Ľڵ� 20 ���Ҷ��ӣ����� 7 ��ջ��

	 stack = [7]
	 index->inorder[8] = 7
	 ��ʱ�������������Ǿ͹��������ȷ�Ķ�������

	 �㷨

	 ���ǹ��ɳ����������е��㷨���̣�

	 ������һ��ջ��һ��ָ�븨�����ж������Ĺ��졣��ʼʱջ�д���˸��ڵ㣨ǰ������ĵ�һ���ڵ㣩��ָ��ָ����������ĵ�һ���ڵ㣻

	 ��������ö��ǰ������г��˵�һ���ڵ������ÿ���ڵ㡣��� index ǡ��ָ��ջ���ڵ㣬��ô���ǲ��ϵص���ջ���ڵ㲢�����ƶ� index��������ǰ�ڵ���Ϊ���һ�������Ľڵ���Ҷ��ӣ���� index ��ջ���ڵ㲻ͬ�����ǽ���ǰ�ڵ���Ϊջ���ڵ������ӣ�

	 ��������һ�������������󶼽���ǰ�Ľڵ���ջ��

	 ���õ��Ķ�������Ϊ�𰸡�*/

 TreeNode* buildTree_2(vector<int>& preorder, vector<int>& inorder) {
	 if (!preorder.size()) {
		 return nullptr;
	 }
	 TreeNode* root = new TreeNode(preorder[0]);
	 stack<TreeNode*> stk;
	 stk.push(root);
	 int inorderIndex = 0;
	 for (int i = 1; i < preorder.size(); ++i) {
		 int preorderVal = preorder[i];
		 TreeNode* node = stk.top();
		 if (node->val != inorder[inorderIndex]) {
			 node->left = new TreeNode(preorderVal);
			 stk.push(node->left);
		 }
		 else {
			 while (!stk.empty() && stk.top()->val == inorder[inorderIndex]) {
				 node = stk.top();
				 stk.pop();
				 ++inorderIndex;
			 }
			 node->right = new TreeNode(preorderVal);
			 stk.push(node->right);
		 }
	 }
	 return root;
 }

 void printBinTree(TreeNode* root)
 {
	 if (root)
	 {
		 cout << root->val << ",";
		 printBinTree(root->left);
		 printBinTree(root->right);
	 }
 }


int main()
{
	//std::vector<int> preorder = { 3, 9, 8, 5, 4, 10, 20, 15, 7 };
	//std::vector<int> inorder = { 4, 5, 8, 10, 9, 3, 15, 20, 7 };
	std::vector<int> preorder = { 3, 6, 9, 2, 5, 4 };
	std::vector<int> inorder = { 3, 6, 2, 9, 5, 4 };
	cout << "�ǵݹ鷽ʽ" << std::endl;
	TreeNode* head = buildTree_2(preorder, inorder);
	printBinTree(head);
	std::cout << std::endl;
	cout << "�ݹ鷽ʽ" << std::endl;
	head = buildTree(preorder, inorder);
	printBinTree(head);
	std::cout << std::endl;

	return 0;
}