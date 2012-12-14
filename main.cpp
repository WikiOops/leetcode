#include "leetcode.h"

int main()
{
	vector<ListNode*> v;
	v.push_back(NULL);
	v.push_back(NULL);

	/*auto beg = std::chrono::system_clock::now();
	for(int i = 0; i < 13; ++i)
	{
		cout << totalNQueens(i) << " ";
	}
	auto end = std::chrono::system_clock::now();
	cout << std::chrono::duration_cast<std::chrono::microseconds>(end-beg).count() << endl;*/

	/*string s[] = {"..9748...","7........",".2.1.9...","..7...24.",".64.1.59.",".98...3..","...8.3.2.","........6","...2759.."};
	vector<string> vec(s, s+sizeof(s)/sizeof(string));
	vector<vector<char> > sudoku = generateSudoku(vec);*/
	//solveSudoku(sudoku);

	/*findSubstring("mississippi", vector<string>(1,"mississippis"));*/


	/*string str[4];
	cout << sizeof(str) << endl;
	TreeNode *root = new TreeNode(2);
	root->left = new TreeNode(0);
	root->right = new TreeNode(4);
	root->left->right = new TreeNode(3);
	root->right->left = new TreeNode(1);
	recoverTree(root);*/




	/*string s[] = {"What","must","be","shall","be."};
	vector<string> v(s, s+sizeof(s) / sizeof(string));*/
	/*vector<vector<int> > mat;
	mat.push_back(vector<int>(1,1));
	mat.push_back(vector<int>(1,0));
	uniquePathsWithObstacles(mat);*/

	/*vector<vector<int> > mat;
	vector<int> vec(2,1);vec[1] = 3;
	mat.push_back(vector<int>(1,1));
	mat.push_back(vector<int>(1,3));
	searchMatrix(mat,3);*/

	/*vector<Interval> vec;
	vec.push_back(Interval(4,5));
	vec.push_back(Interval(2,4));
	vec.push_back(Interval(4,6));
	vec.push_back(Interval(3,4));
	vec.push_back(Interval(0,0));
	vec.push_back(Interval(1,1));
	vec.push_back(Interval(3,5));
	vec.push_back(Interval(2,2));*/
	/*ListNode *p = new ListNode(1), *root = p;
	p->next = new ListNode(1); p = p->next;
	p->next = new ListNode(2); p = p->next;
	p->next = new ListNode(3); p = p->next;*/
	/*p->next = new ListNode(4); p = p->next;
	p->next = new ListNode(4); p = p->next;
	p->next = new ListNode(5); p = p->next;*/
	/*vector<int> a(2, 0); a[0] = 1; a[1] = 2;
	vector<int> b(2, 0); b[0] = 2; b[1] = 1;
	auto res = buildTree2(a, b);*/


	return 0;
}
