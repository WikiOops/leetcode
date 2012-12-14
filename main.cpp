#include "leetcode.h"
void printSum(int candidates[], int index[], int n) {
  for (int i = 1; i <= n; i++)
    cout << candidates[index[i]] << ((i == n) ? "" : "+");
  cout << endl;
}
 
void solve(int target, int sum, int candidates[], int sz, int index[], int n) {
  if (sum > target)
    return;
  if (sum == target)
    printSum(candidates, index, n);
 
  for (int i = index[n]; i < sz; i++) {
    index[n+1] = i;
    solve(target, sum + candidates[i], candidates, sz, index, n+1);
  }
}
 
void solve(int target, int candidates[], int sz) {
  int index[10000];
  index[0] = 0;
  solve(target, 0, candidates, sz, index, 0);
}

vector<vector<char> > generateSudoku(const vector<string> &vec)
{
	vector<vector<char> > sudoku;
	for(int i = 0; i < vec.size(); ++i)
	{
		vector<char> v(&vec[i][0], &vec[i][0]+9);
		sudoku.push_back(v);
	}
	return sudoku;
}



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

/*
fourSum : �У�n^2 * logn�����Ӷȵ��㷨���д�ʵ�֣�

Anagrams : judge largeû����

grayCode : �������ر�����Լ�д�Ĵ��룻

Largest Rectangle in Histogram : �ǳ�������⣻
http://tech-queries.blogspot.jp/2011/03/maximum-area-rectangle-in-histogram.html

Longest Palindromic Substring �� ������Ŀ��leetcode������������������
http://www.leetcode.com/2011/11/longest-palindromic-substring-part-i.html
http://www.leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
http://www.akalin.cx/longest-palindrome-linear-time

Longest Substring Without Repeating Characters: leetcode�Ľ���
http://www.leetcode.com/2011/05/longest-substring-without-repeating-characters.html

Longest Valid Parentheses : һ����Ȥ����Ŀ�����Ƽ򵥣���ʵ�е���˼��

Maximal Rectangle : �ڶ���û������

Median of Two Sorted Arrays : �ο�����ϸ����
http://www.leetcode.com/2011/03/median-of-two-sorted-arrays.html
http://www.leetcode.com/2011/01/find-k-th-smallest-element-in-union-of.html
http://www.geeksforgeeks.org/archives/2105

Minimum Window Substring
http://www.leetcode.com/2010/11/finding-minimum-window-in-s-which.html

Partition List
��д�������⣬time limited�� �ɵ�д���м���caseû��

Permutations
http://wordaligned.org/articles/next-permutation#tocwhats-happe ���

//Regular Expression Matching

//Recover Binary Search Tree

//Reverse Nodes in k-Group

//Substring with Concatenation of All Words

//Roman to Integer

Same Tree:
todo, use iterative method, including LNR, NLR, LRN

Scramble String��
http://www.cs.bu.edu/teaching/cpp/string/scrambling/

Search a 2D Matrix: �򵥵�����ʵ�д�ѧ��
http://www.leetcode.com/2010/10/searching-2d-sorted-matrix.html
http://www.leetcode.com/2010/10/searching-2d-sorted-matrix-part-ii.html

Search for a Range:

Wildcard Matching:
judge largeû��
the same as regular expression matching, FYI:
http://www.leetcode.com/2011/09/regular-expression-matching.html


Unique Paths:
�ܼ򵥵���Ŀ�����ѵ���Ŀ��1.���ܳ����ٳ�������Խ�� 2.һ�߳�һ�߳������ܲ���������Ҫ�����������.��combinatorial������ʱ��Ҫע�����

Word Search
*/