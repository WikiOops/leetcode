/*
author: Chao Zhou;
Graduated Student@EECS.PKU
Intern@IEG.MSRA
*/

#include<hash_map>
#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<limits>
#include<cmath>
#include<string>
#include<map>
#include<cassert>
#include<stack>
#include<chrono>
#include<queue>
#include<functional>
#include<set>
using namespace std;

//old version
//template<class ForwardIterator>
//vector<int> unique_count(ForwardIterator first, ForwardIterator last)
//{
//	vector<int> count;
//	ForwardIterator iter = first;
//	while(iter != last)
//	{
//		int n = 1;
//		while(++iter != last && *iter == *first) ++n;
//		count.push_back(n);
//		if(iter == last) break;
//		iter_swap(iter, ++first);
//	}
//	return count;
//}
struct TreeLinkNode
{
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

template<class ForwardIterator>
vector<int> unique_count(ForwardIterator first, ForwardIterator last)
{
	vector<int> res;
	if(first == last) return res;
	ForwardIterator iter = first;
	int count = 1;
	while(++first != last)
	{
		if(*first == *iter)
			++count;
		else
		{
			res.push_back(count);
			count = 1;
			*(++iter) = *first;
		}
	}
	res.push_back(count);
	return res;
}

int lcm(int a, int b)
{
	if(a < b)
		return lcm(b, a);
	if(0 == b) return a;
	if(a & 1 && b & 1)
		return lcm(a-b, b);
	else if(a & 1)
		return lcm(a, b >> 1);
	else if(b & 1)
		return lcm(a >> 1, b);
	else
		return 2 * lcm(a >> 1, b >> 1);
}

int lcm2(int a, int b)
{
	if(0 == a) return b;
	if(0 == b) return a;
	if(a < b)
	{
		a ^= b;
		b ^= a;
		a ^= b;
	}
	if(a > b << 1)  // prevent recursion stack overflow
	{
		a -= (a/b)*b;
		return lcm(b, a);
	}
	return lcm(a-b, b);
}

//Definition for binary tree
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

struct RandomNode {
	int val;
	RandomNode *next;
	RandomNode *random;
	RandomNode(int x) : val(x), next(NULL), random(NULL) {}
};

void nextPermutation(vector<int> &num);

#define e numeric_limits<int>::min()
//initialize serialized tree
//   1
//  / \
// 2   3
//    /
//   4
//    \
//     5
//The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}".

//level-order deserialization
template<typename TreeType>
vector<int> serialization(TreeType *root)
{
	vector<int> res;
	queue<TreeType*> q;
	q.push(root);
	while(!q.empty())
	{
		TreeType *a = q.front();
		q.pop();
		if(!a)
			res.push_back(e);
		else
		{
			res.push_back(a->val);
			q.push(a->left);
			q.push(a->right);
		}
	}
	return res;
}

//level-order deserialization
template<typename TreeType>
TreeType* initializeTree(const vector<int> &v)
{
	if(0 == v.size()) return NULL;
	queue<TreeType*> q;
	TreeType *head = new TreeType(v[0]);
	q.push(head);
	int index = 1;
	while(!q.empty())
	{
		TreeType *p = q.front();
		q.pop();
		if(index < v.size() && v[index] != e)
		{
			p->left = new TreeType(v[index]);
			q.push(p->left);
		}
		++index;
		if(index < v.size() && v[index] != e)
		{
			p->right = new TreeType(v[index]);
			q.push(p->right);
		}
		++index;
	}
	return head;
}

//pre-order serialization
template<typename TreeType>
void serialization_preorder(vector<int> &res, TreeType *root)
{
	if(!root)
		res.push_back(e);
	else
	{
		res.push_back(root->val);
		serialization_preorder(res, root->left);
		serialization_preorder(res, root->right);
	}
}

template<typename TreeType>
vector<int> serialization_preorder(TreeType *root)
{
	vector<int> res;
	serialization_preorder(res, root);
	return res;
}

//pre-order deserialization
template<typename TreeType>
TreeType* initializeTree_preorder(const vector<int> &v, int &start)
{
	if(start >= v.size())
		return NULL;
	if(v[start] == e)
		return NULL;
	else
	{
		TreeType *p = new TreeType(v[start]);
		++start;
		p->left = initializeTree_preorder(v, start);
		p->right = initializeTree_preorder(v, start);
		return p;
	}
}

template<typename TreeType>
TreeType* initializeTree_preorder(const vector<int> &v)
{
	return initializeTree_preorder(v, 0);
}
