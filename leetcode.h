/*
author: Chao Zhou;
Graduated Student@EECS.PKU
Intern@IEG.MSRA
*/
#include "leetcodeCommon.h"

//ZigZag Conversion
//to do: nRows-based iteration
string convert(string s, int nRows)
{
	if(1 == nRows) return s;
	vector<string> vec(nRows, "");
	int base = (nRows-1)<<1;
	for(int i = 0; i < s.size(); ++i)
	{
		int index = i % base;
		index = (index < nRows) ? index : base - index;
		vec[index].append(1, s[i]);
	}
	//return accumulate(vec.begin(), vec.end(), "");
	string res;
	for(vector<string>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
		res += *iter;
	return res;
}

//Word Search

void nextDirection(int &x, int &y, int i)
{
	if(0 == i) ++x;
	else if(1 == i) ++y;
	else if(2 == i) --x;
	else --y;
}

bool dfs2(vector<vector<char> > &board, const string &word, int x, int y, int k)
{
	if(k == word.size()) return true;
	for(int i = 0; i < 4; ++i)
	{
		int nx = x, ny = y;
		nextDirection(nx, ny, i);
		if(nx < 0 || ny < 0 || nx >= board.size() || ny >= board[0].size())
			continue;
		if(board[nx][ny] == word[k])
		{
			char c = board[nx][ny];
			board[nx][ny] = '#';
			if(dfs2(board, word, nx, ny, k+1)) return true;
			board[nx][ny] = c;
		}
	}
	return false;
}

bool exist2(vector<vector<char> > &board, string word)
{
	if(0 == word.size()) return true;
	for(int x = 0; x < board.size(); ++x)
	{
		for(int y = 0; y < board[0].size(); ++y)
		{
			if(board[x][y] == word[0])
			{
				char c = board[x][y];
				board[x][y] = '#';
				if(dfs2(board, word, x, y, 1)) return true;
				board[x][y] = c;
			}
		}
	}
	return false;
}

bool validNextStep(vector<vector<char> > &board, char c, int direction, int &x, int &y)
{
	if(0 == direction) ++x;
	else if(1 == direction) --x;
	else if(2 == direction) ++y;
	else --y;
	if(x < 0 || x >= board.size() || y < 0 || y >= board[0].size()) return false;
	if(board[x][y] == c) return true;
	return false;
}

bool dfs(vector<vector<char> > &board, const string &s, int index, int i, int j)
{
	if(index >= s.size())
		return true;
	for(int direction = 0; direction < 4; ++direction)
	{
		int x = i, y = j;
		if(!validNextStep(board, s[index], direction, x, y))
			continue;
		char c = board[x][y];
		board[x][y] = '#';
		if(dfs(board, s, index+1, x, y))
			return true;
		board[x][y] = c;
	}
	return false;
}

bool exist(vector<vector<char> > &board, string word)
{
	if(0 == word.size()) return true;
	int m = board.size();
	if(0 == m) return false;
	int n = board[0].size();

	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			if(board[i][j] != word[0])
				continue;
			char c = board[i][j];
			board[i][j] = '#';
			if(dfs(board, word, 1, i, j))
				return true;
			board[i][j] = c;
		}
	}
	return false;
}

//Wildcard Matching
vector<string> extractPatterns(const char *p)
{
	string s(p);
	vector<string> res;
	int i = 0;
	while(i < s.size())
	{
		while(i < s.size() && s[i] == '*') ++i;
		int j = s.find('*', i);
		if(j == string::npos) j = s.size();
		if(j != i) res.push_back(s.substr(i, j-i));
		i = j;
	}
	return res;
}

bool easyMatch(const char* a, const string &s)
{
	int i = 0;
	while(a[i] && i < s.size() && (a[i] == s[i] || s[i] == '?')) ++i;
	return i == s.size();
}
bool isWildcardMatch2(const char *s, const char *p)
{
	int m =strlen(s), n = strlen(p);
	if(0 == n) return 0 == m;
	vector<string> v = extractPatterns(p);
	if(1 == v.size() && p[0] != '*' && p[n-1] != '*' && v[0].size() != m) return false;
	if(0 == v.size()) return true;
	int i = 0;
	vector<string>::iterator iter = v.begin();
	while(iter != v.end())
	{
		while(s[i])
		{
			if(easyMatch(s+i, *iter))
			{
				i += iter->size();
				++iter;
				break;
			}
			else
				++i;
		}
		if(!s[i]) break;
	}
	if(iter != v.end()) return false;
	if(p[0] != '*')
		if(!easyMatch(s, v[0])) return false;
	if(p[n-1] != '*')
		if(!easyMatch(s+m-v.back().size(), v.back())) return false;
	if(s[i] && p[n-1] != '*') return false;
	return true;
}

bool isWildcardMatch(const char *s, const char *p)
{
	if(0 == strlen(s) && 0 == strlen(p)) return true;
	int i = 0, j = 0;
	while(p[j])
	{
		if('*' == p[j])
		{
			const char *t = &s[i];
			while(*t)
			{
				if(isWildcardMatch(t, &p[j+1]))
					return true;
				++t;
			}
			if(isWildcardMatch(t, &p[j+1]))
					return true;
			return false;
		}
		else if(!s[i])
		{
			return false;
		}
		else if('?' == p[j] || s[i] == p[j])
		{
			++i;
			++j;
		}
		else
			return false;
	}
	return s[i] ? false : true;
}

//Validate Binary Search Tree
//wonder if how iterative method is
bool isValidBST(TreeNode *root, int lowerBound, int upperBound)
{
	if(NULL == root) return true;
	if(root->val > lowerBound && root->val < upperBound)
		return isValidBST(root->left, lowerBound, root->val) && isValidBST(root->right, root->val, upperBound);
	return false;
}

bool isValidBST(TreeNode *root)
{
	return isValidBST(root, numeric_limits<int>::min(), numeric_limits<int>::max());
}

//Valid Sudoku
vector<char> GetValidValueList(const vector<vector<char> > &board, int i, int j)
{
	assert(board[i][j] == '.');
	vector<bool> flags(9, true);
	for(int x = 0; x < 9; ++x)
	{
		if(board[i][x] <='9' && board[i][x] >= '1')
			flags[board[i][x]-'1'] = false;
		if(board[x][j] <='9' && board[x][j] >= '1')
			flags[board[x][j]-'1'] = false;
	}
	int x = (i/3)*3, y = (j/3)*3;
	for(int m = 0; m < 3; ++m)
	{
		for(int n = 0; n < 3; ++n)
		{
			if(board[x+m][y+n] <='9' && board[x+m][y+n] >= '1')
				flags[board[x+m][y+n]-'1'] = false;
		}
	}
	vector<char> vec;
	for(int i = 0; i < 9; ++i)
	{
		if(flags[i])
			vec.push_back(i + '1');
	}
	return vec;
}

//Question: if a sudoku board is valid, it that meas there must be a solution? of course not, but not case reflect it
bool isValidSudoku(vector<vector<char> > &board)
{
	for(int i = 0; i < 9; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{
			if(board[i][j] <='9' && board[i][j] >= '1')
			{
				char c = board[i][j];
				board[i][j] = '.';
				vector<char> vec = GetValidValueList(board, i, j);
				if(vec.end() == find(vec.begin(), vec.end(), c))
					return false;
				board[i][j] = c;
			}
		}
	}
	return true;
}

//Valid Parentheses
bool isValid(string s)
{
	stack<string::iterator> stk;
	for(string::iterator iter = s.begin(); iter != s.end(); ++iter)
	{
		switch (*iter)
		{
		case '(': case '[' : case '{':
			stk.push(iter);
			break;
		case ')':
			if(stk.empty() || *stk.top() != '(')
				return false;
			stk.pop();
			break;
		case ']':
			if(stk.empty() || *stk.top() != '[')
				return false;
			stk.pop();
			break;
		case '}':
			if(stk.empty() || *stk.top() != '{')
				return false;
			stk.pop();
			break;
		default:
			return false;
			break;
		}
	}
	return stk.empty();
}

//Valid Number
bool isNumber(const char *s)
{
	return false;
}

//Unique Paths II
int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid)
{
	int m = obstacleGrid.size();
	if(0 == m) return 0;
	int n = obstacleGrid[0].size();
	vector<int> vec(n, 0);
	vec[0] = 1;
	for(int i = 0; i < m; ++i)
	{
		vec[0] = (1 == obstacleGrid[i][0]) ? 0 : vec[0];
		for(int j = 1; j < n; ++j)
			vec[j] = (1 == obstacleGrid[i][j]) ? 0 : vec[j] + vec[j-1];
	}
	return vec[n-1];
}

//Unique Paths
//很简单的题目，很难的题目。1.不能乘完再除，否则越界 2.一边乘一边除，可能不能整除，要处理这种情况.用combinatorial方法的时候要注意溢出
int uniquePaths(int m, int n)
{
	int result = 1;
	if(--m < --n)
	{
		m ^= n;
		n ^= m;
		m ^= n;
	}
	for(int i = 1; i <= n; ++i)
	{
		int dividend = m + n - i + 1;
		if(result % i == 0)
		{
			result /= i;
			result *= dividend;
		}
		else
		{
			int q = lcm(result, i);
			result /= q;
			result *= (dividend/(i/q));
		}
	}
	return result;
}

int uniquePaths2(int m, int n)
{
	int result = 1;
	if(--m < --n)
	{
		m ^= n;
		n ^= m;
		m ^= n;
	}
	for(int i = 1; i <= n; ++i)
	{
		int dividend = m + n - i + 1;
		if(result % i == 0)
			result /= i;
		else if(dividend % i == 0)
			dividend /= i;
		result *= dividend;
	}
	return result;
}

//Unique Binary Search Trees II
vector<TreeNode *> generateTrees(int beg, int end)
{
	if(beg > end) return vector<TreeNode *>(1, NULL);
	vector<TreeNode *> trees;
	for(int i = beg; i <= end; ++i)
	{
		vector<TreeNode *> left = generateTrees(beg, i-1);
		vector<TreeNode *> right = generateTrees(i+1, end);
		for(vector<TreeNode *>::iterator leftTree = left.begin(); 
			leftTree != left.end(); ++leftTree)
		{
			for(vector<TreeNode *>::iterator rightTree = right.begin(); 
				rightTree != right.end(); ++rightTree)
			{
				TreeNode *root = new TreeNode(i);
				root->left = *leftTree;
				root->right = *rightTree;
				trees.push_back(root);
			}
		}
	}
	return trees;
}
vector<TreeNode *> generateTrees(int n)
{
	return generateTrees(1, n);
}

//Unique Binary Search Trees
int numTrees(int n)
{
	//Catalan Numbers
	if(0 == n || 1 == n) return 1;
	vector<int> res(n+1, 0);
	fill(res.begin(), res.begin()+2, 1);
	for(int i = 2; i <= n; ++i)
	{
		for(int j = 0; j < i/2; ++j)
		{
			res[i] += (res[j] * res[i-1-j]) << 1;
		}
		res[i] += (i&1) ? res[i/2] * res[i/2] : 0;
	}
	return res[n];
}

//Two Sum
vector<int> twoSum(vector<int> &numbers, int target)
{
	vector<int> result(2, -1);
	int n = numbers.size();
	for(int i = 0; i < n - 1; ++i)
		for(int j = i + 1; j < n; ++j)
			if(numbers[i] + numbers[j] == target)
			{
				result[0] = i + 1;
				result[1] = j + 1;
				return result;
			}
			return result;
}

vector<int> twoSum2(vector<int> &numbers, int target)
{
	vector<int> res(2, -1);
	hash_map<int ,int> m;
	for(int i = 0; i < numbers.size(); ++i)
	{
		hash_map<int, int>::iterator iter = m.find(target-numbers[i]);
		if(m.end() != iter)
		{
			res[0] = iter->second;
			res[1] = i+1;
		}
		else
			m[numbers[i]] = i+1;
	}
	return res;
}

//Triangle
int minimumTotal(vector<vector<int> > &triangle)
{
	if(0 == triangle.size()) return 0;
	vector<int> v(triangle.size(), 0);
	v[0] = triangle[0][0];
	for(int i = 1; i < triangle.size(); ++i)
	{
		for(int j = i; j >= 0; --j)
		{
			if(j == i)
				v[j] = v[j-1];
			else if(j != 0)
				v[j] = min(v[j], v[j-1]);
			v[j] += triangle[i][j];
		}
	}
	return  *min_element(v.begin(), v.end());
}

//Trapping Rain Water
int trap(int A[], int n)
{
	if(n < 3) return 0;
	int water = 0, pit = 0;
	int i = 0, j = 1;
	while(j < n)
	{
		if(A[i] <= A[j])
		{
			water += pit;
			pit = 0;
			i = j;
		}
		else
			pit += A[i] - A[j];
		++j;
	}
	int top = i;
	i = n-1; j = n-2; pit = 0;
	while(j >= top)
	{
		if(A[j] >= A[i])
		{
			water += pit;
			pit = 0;
			i = j;
		}
		else
			pit +=	A[i] - A[j];
		--j;
	}
	return water;
}

//Text Justification
vector<string> fullJustify(vector<string> &words, int L)
{
	vector<string> res;
	vector<string>::iterator iter = words.begin();
	while(iter != words.end())
	{
		int len = iter->size();
		vector<string>::iterator pos = iter + 1;
		while(pos != words.end() && len + pos->size() + 1 <= L)
		{
			len = len + pos->size() + 1;
			++pos;
		}
		int currWords = pos - iter;
		string s = *iter;
		if(1 == currWords || pos == words.end())
		{
			for(vector<string>::iterator jter = iter + 1; jter != pos; ++jter)
				s = s + " " + *jter;
			s.resize(L, ' ');
		}
		else if(1 < currWords)
		{
			int rightSlots = 1 + (L - len) / (currWords - 1);
			int leftSlotsCount = L - len - (rightSlots-1) * (currWords - 1);
			for(vector<string>::iterator jter = iter + 1; jter != pos; ++jter)
			{
				s.append(rightSlots, ' ');
				if(jter - iter <= leftSlotsCount)
					s.append(1, ' ');
				s += *jter;
			}
		}
		res.push_back(s);
		iter = pos;
	}
	return res;
}

//Symmetric Tree
//recursive method
bool isSymmetric(TreeNode *l, TreeNode *r)
{
	if(!l && !r) return true;
	if(!l || !r) return false;
	if(l->val != r->val) return false;
	return isSymmetric(l->right, r->left) && isSymmetric(l->left, r->right);
}

bool isSymmetric(TreeNode *root)
{
	if(NULL == root) return true;
	return isSymmetric(root->left, root->right);
}

//iterative method
bool isSymmetric2(TreeNode *l, TreeNode *r)
{
	if(!l && !r) return true;
	if(!l || !r) return false;
	queue<TreeNode*> left, right;
	left.push(l); right.push(r);
	int count = 1;
	while(!left.empty() && !right.empty())
	{
		l = left.front();
		r = right.front();
		left.pop();
		right.pop();
		if(l->val != r->val) return false;
		if(l->right && r->left)
		{
			left.push(l->right);
			right.push(r->left);
		}
		else if(l->right || r->left)
			return false;
		if(l->left && r->right)
		{
			left.push(l->left);
			right.push(r->right);
		}
		else if(l->left || r->right)
			return false;
	}
	return true;
}

bool isSymmetric2(TreeNode *root)
{
	if(NULL == root) return true;
	return isSymmetric2(root->left, root->right);
}

//Swap Nodes in Pairs
ListNode *swapPairs(ListNode *head)
{
	if(NULL == head) return NULL;
	ListNode *zero = new ListNode(0);
	zero->next = head;
	ListNode *first = head, *second = head->next;
	head = zero;
	while(NULL != second)
	{
		head->next = second;
		first->next = second->next;
		second->next = first;
		head = first;
		first = first->next;
		if(NULL == first) break;
		second = first->next;
	}
	head = zero->next;
	delete zero;
	return head;
}

ListNode *swapPairs2(ListNode *head)
{
	ListNode *zero = new ListNode(0);
	zero->next = head;
	ListNode *p = zero;
	while(head && head->next)
	{
		p->next = head->next;
		head->next = head->next->next;
		p->next->next = head;
		p = head;
		head = head->next;
	}
	p = zero;
	zero = p->next;
	delete p;
	return zero;
}

//Sudoku Solver
bool solveSudoku(vector<vector<char> > &board, int k)
{
	if(81 == k) return true;
	int x = k / 9, y = k % 9;
	if(board[x][y] <= '9' && board[x][y] >= '1')
		return solveSudoku(board, k+1);
	vector<char> vec = GetValidValueList(board, x, y);
	for(int i = 0; i < vec.size(); ++i)
	{
		board[x][y] = vec[i];
		if(solveSudoku(board, k+1))
			return true;
		board[x][y] = '.';
	}
	return false;
}

void solveSudoku(vector<vector<char> > &board)
{
	solveSudoku(board, 0);
}


//bool ValidSudoku(vector<vector<char> > &board)
//{
//	for(int i = 0; i < 9; ++i)
//	{
//		for(int j = 0; j < 9; ++j)
//		{
//			if('.' != board[i][j])
//				continue;
//			vector<char> vec = GetValidValueList(board, i, j);
//			for(vector<char>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
//			{
//				board[i][j] = *iter;
//				if(ValidSudoku(board))
//					return true;
//				board[i][j] = '.';
//			}
//			return false;
//		}
//	}
//	return true;
//}

//Substring with Concatenation of All Words
vector<int> findSubstring(string S, vector<string> &L)
{
	vector<int> res;
	map<string, int> table;
	map<string, int> temp;

	int n = L.size();
	if(0 == n || L[0].size() * L.size() > S.size()) return res;
	int len = L[0].size();
	for(vector<string>::iterator iter = L.begin(); iter != L.end(); ++iter)
		table[*iter]++;
	for(int i = 0, j; i <= S.size()-len*n; ++i)
	{
		temp.clear();
		for(j = 0; j < n; ++j)
		{
			string sub = S.substr(i+len*j, len);
			if(table.end() == table.find(sub))
				break;
			temp[sub]++;
			if(temp[sub] > table[sub])
				break;
		}
		if(j == n)
			res.push_back(i);
	}
	return res;
}

//Subsets II
void generateSubsets(vector<vector<int> > &res, const vector<int> &S, const vector<int> &count, int index)
{
	assert(S.size() == count.size());
	if(index >= S.size()) return;
	if(0 == res.size()) res.push_back(vector<int>());
	int oldSize = res.size();
	for(int i = 1; i <= count[index]; ++i)
	{
		for(int j = 0; j < oldSize; ++j)
		{
			vector<int> temp = res[j];
			temp.insert(temp.end(), i, S[index]);
			res.push_back(temp);
		}
	}
	generateSubsets(res, S, count, index+1);
}

vector<vector<int> > subsetsWithDup(vector<int> &S)
{
	sort(S.begin(), S.end());
	vector<int> count = unique_count(S.begin(), S.end());
	vector<vector<int> > res;
	S.resize(count.size());
	generateSubsets(res, S, count, 0);
	return res;
}

//Subsets
vector<vector<int> > subsets(vector<int> &S)
{
	sort(S.begin(), S.end());
	int n = S.size(), num = 1 << n;
	vector<vector<int> > res;
	for(int i = 0; i < num; ++i)
	{
		vector<int> item;
		for(int j = 0; j < n; ++j)
		{
			int mask = 1 << j;
			if(i & mask)
				item.push_back(S[j]);
		}
		res.push_back(item);
	}
	return res;
}

vector<vector<int> > subsets2(vector<int> &S)
{
	sort(S.begin(), S.end());
	vector<vector<int> > res;
	vector<int> count(S.size(), 1);
	generateSubsets(res, S, count, 0);
	return res;
}

//String to Integer (atoi)
int atoi(const char *str)
{
	assert(NULL != str);
	while(' ' == *str)
		str++;
	bool sym = true;
	if('+' == *str || '-' == *str)
	{
		sym = '-' == *str ? false : true;
		++str;
	}
	int res = 0;
	while(*str <= '9' && *str >= '0')
	{
		if((sym ? res : -res) & 0x70000000) //when the most significant three bits are all 1, it would be overflow after multipled by 10
			return sym ? numeric_limits<int>::max() : numeric_limits<int>::min();
		res *= 10;
		int temp = *str - '0';
		res += sym ? temp : -temp;
		++str;
	}
	if(sym && res < 0)
		return numeric_limits<int>::max();
	if(!sym && res > 0)
		return numeric_limits<int>::min();
	return res;
}

//Sqrt(x)
int sqrt(int x)
{
	if(0 == x) return 0;
	if(1 == x) return 1;
	int s = sqrt(x >> 2) << 1;
	int p = (s + 1) * (s + 1);
	if(p <= x && p > s) return s + 1;
	return s;
}

//Spiral Matrix II
void generateMatrix(vector<vector<int> > &res, int index, int start, int n)
{
	if(index >= res.size() / 2)
	{
		if(res.size() & 1)
			res[index][index] = start;
		return;
	}
	int row = index, col = index;
	for(; col < n-1-index; ++col) res[row][col] = start++;
	for(; row < n-1-index; ++row) res[row][col] = start++;
	for(; col > index; --col) res[row][col] = start++;
	for(; row > index; --row) res[row][col] = start++;
	generateMatrix(res, index + 1, start, n);
}

vector<vector<int> > generateMatrix(int n)
{
	vector<vector<int> > res(n, vector<int>(n, 0));
	generateMatrix(res, 0, 1, n);
	return res;
}

vector<vector<int> > generateMatrix2(int n)
{
	int left = 0, right = n - 1, upper = 0, lower = n - 1;
	vector<vector<int> > result(n, vector<int>(n, 0));
	int row = 0, col = 0, k = 1;
	while(true)
	{
		while(col <= right)
			result[row][col++] = k++;
		--col; ++row; ++upper;
		if(row > lower) break;
		while(row <= lower)
			result[row++][col] = k++;
		--row; --col; --right;
		if(col < left) break;
		while(col >= left)
			result[row][col--] = k++;
		++col; --row; --lower;
		if(row < upper) break;
		while(row >= upper)
			result[row--][col] = k++;
		++row; ++col; ++left;
		if(col > right) break;
	}
	return result;
}

//Spiral Matrix
vector<int> spiralOrder(vector<vector<int> > &matrix)
{
	vector<int> res;
	int m = matrix.size();
	if(0 == m) return res;
	int n = matrix[0].size();
	if(0 == n) return res;
	int x = 0, y = 0;
	while(true)
	{
		for(int i = 0; i < n; ++i) res.push_back(matrix[y][x++]);
		--m; if(m <= 0) break; --x; ++y;
		for(int i = 0; i < m; ++i) res.push_back(matrix[y++][x]);
		--n; if(n <= 0) break; --x; --y;
		for(int i = 0; i < n; ++i) res.push_back(matrix[y][x--]);
		--m; if(m <= 0) break; ++x; --y;
		for(int i = 0; i < m; ++i) res.push_back(matrix[y--][x]);
		--n; if(n <= 0) break; ++x; ++y;
	}
	return res;
}

vector<int> spiralOrder2(vector<vector<int> > &matrix)
{
	int left = 0, upper = 0;
	int lower = matrix.size() - 1;
	if(-1 == lower) return vector<int>(0, 0);
	int right = matrix[0].size() - 1;
	int row = 0, col = 0;
	vector<int> result;
	while(true)
	{
		while(col <= right)
			result.push_back(matrix[row][col++]);
		--col; ++row; ++upper;
		if(row > lower) break;
		while(row <= lower)
			result.push_back(matrix[row++][col]);
		--row; --col; --right;
		if(col < left) break;
		while(col >= left)
			result.push_back(matrix[row][col--]);
		++col; --row; --lower;
		if(row < upper) break;
		while(row >= upper)
			result.push_back(matrix[row--][col]);
		++row; ++col; ++left;
		if(col > right) break;
	}
	return result;
}

//Sort Colors
void sortColors(int A[], int n)
{//Dijkstra's Dutch National Flag Problem
	int top = -1, bottom = n;
	for(int i = 0; i < bottom;)
	{
		if(A[i] == 0)
		{
			if(++top < i)
			{
				A[top] = 0;
				A[i] = 1;
			}
			++i;
		}
		else if(A[i] == 2)
		{
			if(--bottom > i)
			{
				A[i] = A[bottom];
				A[bottom] = 2;
			}
		}
		else
			++i;
	}
}

void sortColors2(int A[], int n)
{
	int i = 0, j = n-1, k = 0;
	while(k <= j)
	{
		if(A[k] == 0)
		{
			iter_swap(A+k, A+i);
			++k; ++i;
		}
		else if(A[k] == 2)
		{
			iter_swap(A+k, A+j);
			--j;
		}
		else
			++k;
	}
}

//Simplify Path
string simplifyPath(string path)
{
	vector<string> v;
	int pos = path.find('/');
	while(string::npos != pos)
	{
		int nextpos = path.find('/', pos+1);
		string temp = path.substr(pos+1, nextpos-pos-1);
		if(0 == temp.compare(".."))
		{
			if(v.size() > 0)
				v.pop_back();
		}
		else if(temp.size() > 0 && 0 != temp.compare("."))
			v.push_back(temp);
		pos = nextpos;
	}
	string res;
	for(int i = 0; i < v.size(); ++i)
		res = res + '/' + v[i];
	if(0 == v.size())
		res = "/";
	return res;
}

//Set Matrix Zeroes
void setZeroes(vector<vector<int> > &matrix)
{//该题亮点在如何用O（1）空间实现
	int m = matrix.size();
	if(0 == m) return;
	int n = matrix[0].size();
	bool flag = false;
	for(int j = 0; j < n; ++j)
		if(0 == matrix[0][j])
			flag = true;
	for(int i = 1; i < m; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			if(0 == matrix[i][j])
			{
				matrix[0][j] = 0;
				matrix[i][0] = 0;
			}
		}
	}
	for(int i = 1; i < m; ++i)
	{
		if(0 == matrix[i][0])
			matrix[i].assign(matrix[i].size(), 0);
	}
	
	for(int j = 0; j < n; ++j)
	{
		if(0 != matrix[0][j])
			continue;
		for(int i = 1; i < m; ++i)
		{
			matrix[i][j] = 0;
		}
	}
	if(flag) matrix[0].assign(matrix[0].size(), 0);
}

//Search Insert Position
int searchInsert(int A[], int n, int target)
{
	for(int i = 0, j = n; i < j;)
	{
		int mid = (i+j)/2;
		if(A[mid] < target)
			i = mid + 1;
		else if(A[mid] > target)
			j = mid;
		else
			return mid;
	}
	return -1;
}

int searchInsert2(int A[], int n, int target)
{
	int i = 0, j = n;
	while(i < j)
	{
		int mid = i + (j-i)/2;
		if(A[mid] < target)
			i = mid+1;
		else
			j = mid;
	}
	return i;
}


//Search in Rotated Sorted Array II
bool searchDup(int A[], int n, int target)
{
	int i = 0, j = n-1;
	while(i <= j)
	{
		if(A[i] == A[j])
		{
			if(target == A[i++])
				return true;
			else
				--j;
			continue;
		}
		int mid = (i+j)/2;
		if(A[mid] < target)
		{
			if(A[mid] >= A[i])
				i = mid+1;
			else if(target <= A[j])
				i = mid + 1;
			else
				j = mid-1;
		}
		else if(A[mid] > target)
		{
			if(A[mid] <= A[j])
				j = mid-1;
			else if(target >= A[i])
				j = mid-1;
			else
				i = mid+1;
		}
		else
			return true;
	}
	return false;
}

//Search in Rotated Sorted Array
int search(int A[], int n, int target)
{
	int i = 0, j = n-1;
	while(i <= j)
	{
		int mid = (i+j)/2;
		if(A[mid] < target)
		{
			if(A[mid] >= A[i])
				i = mid+1;
			else if(target <= A[j])
				i = mid + 1;
			else
				j = mid-1;
		}
		else if(A[mid] > target)
		{
			if(A[mid] <= A[j])
				j = mid-1;
			else if(target >= A[i])
				j = mid-1;
			else
				i = mid+1;
		}
		else
			return mid;
	}
	return -1;
}

//Search for a Range
vector<int> searchRange(int A[], int n, int target)
{
	int i = 0, j = n-1, mid;
	vector<int> res(2, -1);
	while(i <= j)
	{
		mid = (i+j) >> 1;
		if(A[mid] > target)
			j = mid-1;
		else if(A[mid] < target)
			i = mid+1;
		else
			break;
	}
	if(i > j) return res;
	int t = mid;
	while(i < t)
	{
		int a = i + (t-i)/2;
		if(A[a] < target)
			i = a + 1;
		else
			t = a;
	}
	res[0] = i;
	t = mid;
	while(t < j)
	{
		int a = t + (j-t+1)/2;
		if(A[a] > target)
			j = a-1;
		else
			t = a;
	}
	res[1] = j;
	return res;
}

//Search a 2D Matrix
bool searchMatrix(vector<vector<int> > &matrix, int target)
{
	int m = matrix.size();
	if(0 == m) return false;
	int n = matrix[0].size();
	if(0 == n) return false;
	int i = -1, j = m-1;
	while(i < j)
	{
		int mid = (i+j+1)/2;
		if(-1 == mid) return false;
		if(matrix[mid][0] < target)
			i = mid;
		else if(matrix[mid][0] > target)
			j = mid-1;
		else
			return true;
	}
	int loc = i;
	if(-1 == loc) return false;
	i = 1; j = n-1;
	while(i <= j)
	{
		int  mid = (i+j)/2;
		if(matrix[loc][mid] < target)
			i = mid+1;
		else if(matrix[loc][mid] > target)
			j = mid-1;
		else
			return true;
	}
	return false;
}

bool searchMatrix2(vector<vector<int> > &matrix, int target)
{
	int m = matrix.size();
	if(0 == m) return false;
	int n = matrix[0].size();
	if(0 == n) return false;

	int i = 0, j = n-1;
	while(i<m && j >= 0)
	{
		if(matrix[i][j] < target)
			++i;
		else if(matrix[i][j] > target)
			--j;
		else
			return true;
	}
	return false;
}


//Scramble String
bool isSameSet(const string &s1, const string &s2)
{
	vector<int> vec(26, 0);
	if(s1.size() != s2.size()) return false;
	for(int i = 0; i < s1.size(); ++i)
	{
		vec[s1[i]-'a']++;
		vec[s2[i]-'a']--;
	}
	for(int i = 0; i < vec.size(); ++i)
		if(0 != vec[i])
			return false;
	return true;
}
bool isScramble(string s1, string s2)
{
	if(s1.size() != s2.size()) return false;
	if(!isSameSet(s1, s2)) return false;
	if(s1.size() < 4) return true;
	for(int i = 1; i < s1.size(); ++i)
	{
		if(isScramble(s1.substr(0, i), s2.substr(0, i)) && 
			isScramble(s1.substr(i, s1.size()-i), s2.substr(i, s1.size()-i)))
			return true;
		if(isScramble(s1.substr(0, i), s2.substr(s2.size()-i, i)) &&
			isScramble(s1.substr(i, s1.size()-i), s2.substr(0, s1.size()-i)))
			return true;
	}
	return false;
}


//Same Tree
bool isSameTree(TreeNode *p, TreeNode *q)
{
	if(p && q)
		return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	if(!p && !q)
		return true;
	return false;
}

bool isSameTree2(TreeNode *p, TreeNode *q)
{
	if(!p && !q) return true;
	if(!p || !q) return false;
	queue<TreeNode*> l, r;
	l.push(p); r.push(q);
	while(!l.empty() && !r.empty())
	{
		p = l.front(); q = r.front();
		l.pop(); r.pop();
		if(p->val != q->val) return false;
		if(p->left && q->left)
		{
			l.push(p->left);
			r.push(q->left);
		}
		else if(p->left || q->left)
			return false;
		if(p->right && q->right)
		{
			l.push(p->right);
			r.push(q->right);
		}
		else if(p->right || q->right)
			return false;
	}
	return true;
}

//Rotate List
ListNode *rotateRight(ListNode *head, int k)
{
	if(NULL == head) return NULL;
	assert(k >= 0);
	ListNode *tail = head;
	int loop = 1;
	while(tail->next != NULL)
	{
		++loop;
		tail = tail->next;
	}
	tail->next = head;
	k %= loop;
	k = loop - k;
	for(int i = 1; i < k; ++i)
	{
		head = head->next;
	}
	tail = head->next;
	head->next = NULL;
	return tail;
}

//Rotate Image
void rotate(vector<vector<int> > &matrix)
{
	int n = matrix.size();
	for(int i = 0; i < (n+1)/2; ++i)
	{
		for(int j = 0; j < n/2; ++j)   //notice the difference between the range of i and j
		{
			int temp = matrix[i][j];
			matrix[i][j] = matrix[n-j-1][i];
			matrix[n-j-1][i] = matrix[n-i-1][n-j-1];
			matrix[n-i-1][n-j-1] = matrix[j][n-i-1];
			matrix[j][n-i-1] = temp;
		}
	}
}

//Roman to Integer

//Reverse Nodes in k-Group
ListNode *reverseKGroup(ListNode *head, int k)
{//自我感觉这是一个优良条目
	if(k < 2) return head;
	ListNode *zero = new ListNode(0);
	ListNode *p = zero;
	ListNode *successor = head;
	zero->next = head;
	int r = 0;
	while(successor)
	{
		r = 0;
		while(successor && r < k)
		{
			successor = successor->next;
			r++;
		}
		if(r != k)
			break;
		ListNode *s = head->next;
		ListNode *t = s->next;
		while(t != successor)
		{
			s->next = head;
			head = s;
			s = t;
			t = t->next;
		}
		s->next = head;
		t = p->next;
		p->next = s;
		t->next = successor;
		p = t;
		head = successor;
	}
	p = zero;
	zero = zero->next;
	delete p;
	return zero;
}

ListNode *reverseListRange(ListNode *head, ListNode *last)
{
	ListNode *p = head, *prev = last;
	while(p != last)
	{
		ListNode *q = p->next;
		p->next = prev;
		prev = p;
		p = q;
	}
	return prev;
}

ListNode *reverseKGroup2(ListNode *head, int k)
{
	ListNode *zero = new ListNode(0);
	zero->next = head;
	ListNode *p = head, *prev = zero;
	while(head)
	{
		int i = 0;
		while(p && i < k)
		{
			p = p->next;
			++i;
		}
		if(i == k)
		{
			prev->next = reverseListRange(head, p);
			prev = head;
		}
		else
			prev->next = head;
		head = p;
	}
	head = zero->next;
	delete zero;
	return head;
}

//Reverse Linked List II
ListNode *reverseBetween(ListNode *head, int m, int n)
{
	ListNode *p = new ListNode(0), *prev = p;
	p->next = head;
	while(prev->next && m > 1)
	{
		--m; --n;
		prev = prev->next;
	}
	if(n <= 1) return head;
	head = prev->next;
	ListNode *tail = head->next;
	while(tail && n > 2)
	{
		--n;
		ListNode *temp = tail->next;
		tail->next = head;
		head = tail;
		tail = temp;
	}
	prev->next->next = tail->next;
	tail->next = head;
	prev->next = tail;
	head = p->next;
	delete p;
	return head;
}

ListNode *reverseBetween2(ListNode *head, int m, int n)
{
	ListNode *zero = NULL, *curr = head, *p = head;
	while(curr && m > 1)
	{
		zero = curr;
		curr = curr->next;
		--m;
		--n;
	}
	if(m > 1 || n < 1) return head;
	ListNode *prev = curr;
	while(curr && n > 0)
	{
		prev = prev->next;
		--n;
	}
	ListNode *last= prev;
	while(curr != last)
	{
		p = curr->next;
		curr->next = prev;
		prev = curr;
		curr = p;
	}
	if(zero)
	{
		zero->next = prev;
		return head;
	}
	return prev;
}

ListNode *reverseBetween3(ListNode *head, int m, int n)
{
	ListNode *p = new ListNode(0), *prev = p, *last = NULL;
	p->next = head;
	while(m > 1)
	{
		prev = prev->next;
		--m; --n;
	}
	last = prev->next;
	while(n > 0)
	{
		last = last->next;
		--n;
	}
	head = prev->next;
	prev->next = reverseListRange(head, last);
	head = p->next;
	delete p;
	return head;
}

//The iterative  and recursive way of reverse listed node:
//void reverse(Node*& head) {
//  if (!head) return;
//  Node* prev = NULL;
//  Node* curr = head;
//  while (curr) {
//    Node* next = curr->next;
//    curr->next = prev;
//    prev = curr;
//    curr = next;
//  }
//  head = prev;
//}
//
//void reverse(Node*& p) {
//  if (!p) return;
//  Node* rest = p->next;
//  if (!rest) return;
//  reverse(rest);
//  p->next->next = p;
//  p->next = NULL;
//  p = rest;
//}

//Reverse Integer
int reverse(int x)
{
	bool sym = true;
	if(x < 0) x = -x, sym = !sym;
	int q;
	for(q = 1; x / q >= 10; q *= 10);
	int p = 1, res = 0;
	while(q >= 1)
	{
		res += p * ((x/q) % 10);
		p *= 10; q /= 10;
	}
	return sym ? res : -res;
}

//Restore IP Addresses
bool isValidIP(string s)
{
	switch (s.size())
	{
	case 1:
		if(s[0] <= '9' && s[0] >= '0')
			return true;
		break;
	case 2:
		if(s[0] <= '9' && s[0] >= '1' && s[1] <= '9' && s[1] >= '0')
			return true;
	case 3:
		if(s[0] == '1' && s[1] <= '9' && s[1] >= '0' && s[2] <= '9' && s[2] >= '0')
			return true;
		else if(s[0] == '2' && s[1] <= '4' && s[1] >= '0' && s[2] <= '9' && s[2] >= '0')
			return true;
		else if(s[0] == '2' && s[1] == '5' && s[2] <= '5' && s[2] >= '0')
			return true;
	}
	return false;
}

void restoreIpAddresses(vector<string> &res, const string &s, string item, int count)
{
	if(s.size() < count || s.size() > count * 3) return;
	if(0 == count)
	{
		if(s.size() == 0)
			res.push_back(item);
		return;
	}
	for(int len = 1; len <= 3; ++len)
	{
		if(len > s.size()) return;
		string temp = s.substr(0, len);
		if(isValidIP(temp))
			restoreIpAddresses(res, string(s.begin()+len, s.end()), item + ((4 == count) ? "" : ".") + temp, count-1);
	}
}

vector<string> restoreIpAddresses(string s)
{
	vector<string> res;
	string item;
	restoreIpAddresses(res, s, item, 4);
	return res;
}

//Remove Nth Node From End of List
ListNode *removeNthFromEnd(ListNode *head, int n)
{
	ListNode *p = head, *q = head;
	while(n > 0 && q)
	{
		q = q->next;
		--n;
	}
	if(n != 0) return NULL;
	if(NULL == q)
	{
		q = head;
		head = head->next;
		delete q;
		return head;
	}
	while(q->next)
	{
		p = p->next;
		q = q->next;
	}
	q = p->next;
	p->next = q->next;
	delete q;
	return head;
}

//Remove Element
int removeElement(int A[], int n, int elem)
{
	for(int i = 0; i < n;)
	{
		if(A[i] == elem)
			A[i] = A[--n];
		else
			++i;
	}
	return n;
}

//Remove Duplicates from Sorted List II
//old version
ListNode *deleteDuplicates2(ListNode *head)
{
	if(NULL == head || NULL == head->next) return head;
	ListNode *zero = new ListNode(0);
	zero->next = head;
	ListNode *p = head->next;
	ListNode *shift = zero;
	while(NULL != p)
	{
		while(NULL != p && p->val == head->val)
			p = p->next;
		if(p == head->next)
		{
			shift = head;
			head = p;
			p = p->next;
		}
		else
		{
			do
			{
				shift->next = head->next;
				delete head;
				head = shift->next;
			}while(head != p);
			if(NULL == p)
				break;
			p = p->next;
		}
	}
	p = zero;
	zero = p->next;
	delete p;
	return zero;
}

//new version 27th Oct 2012, no delete
ListNode *deleteDuplicates3(ListNode *head)
{
	ListNode *zero = new ListNode(0);
	zero->next = head;
	ListNode *q = zero;
	while(head)
	{
		ListNode *p = head->next;
		while(p && p->val == head->val)
			p = p->next;
		if(p == head->next)
			q = head;
		else
			q->next = p;
		head = p;
	}
	q = zero->next;
	delete zero;
	return q;
}


//Remove Duplicates from Sorted List
ListNode *deleteDuplicates(ListNode *head)
{
	if(NULL == head) return head;
	ListNode *p = head;
	while(p->next)
	{
		if(p->val == p->next->val)
			p->next = p->next->next;
		else
			p = p->next;
	}
	return head;
}

//Remove Duplicates from Sorted Array II
int removeDuplicates2_2(int A[], int n)
{
	if(0 == n) return 0;
	int i = 1, j = 1, val = A[0], count = 1;
	while(j < n)
	{
		if(A[j] == val)
		{
			if(++count <= 2)
			{
				A[i++] = A[j++];
			}
			else
				++j;
		}
		else
		{
			val = A[j];
			A[i++] = A[j++];
			count = 1;
		}
	}
	return i;
}

int removeDuplicates2(int A[], int n)
{
	if(0 == n) return 0;
	int prev = 1, curr = 1, val = A[0];
	bool count = false;
	while(prev < n)
	{
		if(A[prev] == val)
		{
			if(!count)
			{
				count = true;
				A[curr++] = A[prev];
			}
		}
		else
		{
			count = false;
			val = A[prev];
			A[curr++] = A[prev];
		}
		prev++;
	}
	return curr;
}

//Remove Duplicates from Sorted Array
int removeDuplicates(int A[], int n)
{
	if(0 == n) return 0;
	int prev = 1, curr = 1, val = A[0];
	while(prev < n)
	{
		if(A[prev] == val)
			prev++;
		else
		{
			val = A[prev];
			A[curr++] = A[prev++];
		}
	}
	return curr;
}

//Regular Expression Matching
//keep your logic clear
bool isMatch(char a, char b)
{
	return ('.' == b) ? a != '\0' : a == b;
}

//my new solution
bool isMatch3(const char *s, const char *p)
{
	assert(s && p);
	if(!*p) return !*s;
	if(*(p+1) != '*')
		return isMatch(*s, *p) && isMatch3(s+1, p+1);
	else
	{
		if(isMatch3(s, p+2))
			return true;
		while(*s)
		{
			if(!isMatch(*s, *p)) break;
			if(isMatch3(s+1, p+2)) return true;
			++s;
		}
	}
	return false;
}

//1337c0d3r's solution
bool isMatch2(const char *s, const char *p)
{
	assert(s && p);
	if (*p == '\0') return *s == '\0';

	// next char is not '*': must match current character
	if (*(p+1) != '*') {
		assert(*p != '*');
		return ((*p == *s) || (*p == '.' && *s != '\0')) && isMatch2(s+1, p+1);
	}
	// next char is '*'
	while ((*p == *s) || (*p == '.' && *s != '\0')) {
		if (isMatch2(s, p+2)) return true;
		s++;
	}
	return isMatch2(s, p+2);
}

bool isMatch(const char *s, const char *p)
{
	if(0 == strlen(p) && 0 == strlen(s)) return true;
	int i = 0, j = 0;
	while(p[j])
	{
		if(p[j+1] == '*')
		{
			if(isMatch(&s[i], &p[j+2]))
				return true;
			for(const char *t = &s[i+1]; *(t-1) && isMatch(*(t-1), p[j]); ++t)
			{
				if(isMatch(t, &p[j+2]))
					return true;
			}
			return false;
		}
		else
		{
			if(!s[i])
				return false;
			else if(isMatch(s[i], p[j]))
			{
				++i;
				++j;
			}
			else
				return false;
		}
	}
	if(!s[i] && !p[j])
		return true;
	return false;
}

//Recover Binary Search Tree
void InOrder(TreeNode *root, vector<TreeNode*> &vec)
{
	stack<TreeNode*> stk;
	while(root || !stk.empty())
	{
		if(root)
		{
			stk.push(root);
			root = root->left;
		}
		else
		{
			root = stk.top();
			stk.pop();
			vec.push_back(root);
			root = root->right;
		}
	}
}

void recoverTree(TreeNode *root)
{
	vector<TreeNode*> vec;
	InOrder(root, vec);
	TreeNode *first = NULL, *second = NULL;
	for(int i = 0; i < vec.size()-1; ++i)
	{
		if(vec[i]->val > vec[i+1]->val)
		{
			first = vec[i];
			break;
		}
	}
	for(int i = vec.size()-1; i > 0; --i)
	{
		if(vec[i]->val < vec[i-1]->val)
		{
			second = vec[i];
			break;
		}
	}
	int temp = first->val;
	first->val = second->val;
	second->val = temp;
}

//Pow(x, n)
//Recursion
double pow1(double x, int n)
{
	if(0 == n) return 1;
	if(0 == x) return 0;
	bool reciprocal = false;
	if(n < 0)
	{
		n = -n;
		reciprocal = true;
	}
	double a = pow1(x, n >> 1);
	a *= a;
	if(n & 1) a *= x;
	return reciprocal ? 1 / a : a;
}

//Iteration
double pow2(double x, int n)
{
	if(0 == n) return 1;
	if(0.0 == x) return 0.0;
	if(1.0 == x) return 1.0;
	if(-1.0 == x && (n & 1)) return -1.0;
	if(-1.0 == x && !(n & 1)) return 1.0;
	if(n < 0) return 1 / pow2(x, -n);
	double result = 1.0;
	while (n)
	{
		if (n&1) result *= x;
		x *= x;
		n >>= 1;
	}
	return result;
}

//Populating Next Right Pointers in Each Node II
//You may only use constant extra space.
void connectII2(TreeLinkNode *root)
{
	if(!root) return;
	root->next = NULL;
	while(root)
	{
		TreeLinkNode *nextFirst = NULL, *zero = NULL;
		while(root)
		{
			if(root->left && root->right)
			{
				root->left->next = root->right;
				if(zero) zero->next = root->left;
				zero = root->right;
				if(!nextFirst) nextFirst = root->left;
			}
			else if(root->left)
			{
				if(zero) zero->next = root->left;
				zero = root->left;
				if(!nextFirst) nextFirst = root->left;
			}
			else if(root->right)
			{
				if(zero) zero->next = root->right;
				zero = root->right;
				if(!nextFirst) nextFirst = root->right;
			}
			root = root->next;
		}
		root = nextFirst;
	}
}

void connectII(TreeLinkNode *root)
{
	if(!root) return;
	root->next = NULL;
	while(root)
	{
		TreeLinkNode *nextFirst = NULL, *zero = NULL;
		while(root)
		{
			TreeLinkNode *l = root->left ? root->left : root->right, *r = root->right ? root->right : root->left;
			if(l && l != r)
				l->next = r;
			if(!nextFirst)
				nextFirst = l;
			if(zero)
				zero->next = l;
			if(r)
				zero = r;
			root = root->next;
		}
		root = nextFirst;
	}
}

//Populating Next Right Pointers in Each Node
//You may only use constant extra space.
//You may assume that it is a perfect binary tree
void connect(TreeLinkNode *root)
{
	if(!root) return;
	root->next = NULL;
	while(root->left)
	{
		TreeLinkNode *nextLevel = root->left;
		while(root)
		{
			TreeLinkNode *succ = root->next;
			root->left->next = root->right;
			root->right->next = succ ? succ->left : NULL;
			root = succ;
		}
		root = nextLevel;
	}
}

//Plus One
vector<int> plusOne(vector<int> &digits)
{
	vector<int>::iterator iter = digits.end()-1;
	while(iter >= digits.begin() && 9 == *iter) --iter;
	if(iter < digits.begin())
	{
		digits.assign(digits.size()+1, 0);
		digits[0] = 1;
	}
	else
	{
		++*iter;
		while(++iter != digits.end()) *iter = 0;
	}
	return digits;
}

//Permutations II
vector<vector<int> > permuteUnique(vector<int> &num)
{
	vector<int> first(num);
	vector<vector<int> > result;
	do
	{
		result.push_back(num);
		nextPermutation(num);
	}while(num != first);
	return result;
}

//Permutations
vector<vector<int> > permute(vector<int> &num)
{
	int perm = 1;
	for(int n = num.size(); n > 1; --n)
		perm *= n;
	vector<vector<int> > result;
	for(int i = 0; i < perm; ++i)
	{
		result.push_back(num);
		nextPermutation(num);
	}
	return result;
}

//Permutation Sequence
string getPermutation(int n, int k)
{
	int factorial = 1;
	string result;
	for(int i = 1; i < n; ++i)
		factorial *= i;
	--k;
	vector<bool> flag(n, false);
	for(int i = n - 1; i >= 0; --i)
	{
		int index = k / factorial;
		for(int j = 0; j < n && index >= 0; ++j)
		{
			if(!flag[j])
			{
				if(0 == index)
				{
					flag[j] = true;
					result.append(1, j + '1');
				}
				--index;
			}
		}
		k %= factorial;
		if(i > 0)
			factorial /= i;
	}
	return result;
}
//Path Sum II
//recursive
void pathSum(vector<vector<int> > &res, vector<int> item, TreeNode *root, int sum)
{
	if(!root) return;
	item.push_back(root->val);
	if(!root->left && !root->right && root->val == sum)
	{
		res.push_back(item);
		return;
	}
	if(root->left) pathSum(res, item, root->left, sum - root->val);
	if(root->right) pathSum(res, item, root->right, sum - root->val);
}

vector<vector<int> > pathSum(TreeNode *root, int sum)
{
	vector<vector<int> > res;
	vector<int> item;
	pathSum(res, item, root, sum);
	return res;
}

//iterative
vector<vector<int> > pathSum2(TreeNode *root, int sum)
{
	vector<vector<int> > res;
	//vector<int> item;
	return res;
}

//Path Sum
//recursive
bool hasPathSum(TreeNode *root, int sum)
{
	if(!root) return false;
	if(!root->left && !root->right) return sum == root->val;
	if(root->left && hasPathSum(root->left, sum - root->val)) return true;
	if(root->right && hasPathSum(root->right, sum - root->val)) return true;
	return false;
}

//iterative
bool hasPathSum2(TreeNode *root, int sum)
{
	//stack<TreeNode*> s;
	//TreeNode *prev = NULL;
	//while(!s.empty() || root)
	//{
	//	if(root)
	//	{
	//		if(!root->left && !root->right && sum == root->val) return true;
	//		sum -= root->val;
	//		s.push(root);
	//		root = root->left;
	//	}
	//	else if(s.top()->right == prev)
	//	{
	//		prev = s.top();
	//		s.pop();
	//	}
	//	else
	//	{
	//		root = s.top()->right;
	//		prev = NULL;
	//	}
	//}
	return false;
}

//Pascal's Triangle II
vector<int> getRow(int rowIndex)
{
	vector<int> res(rowIndex+1, 1);
	for(int i = 1; i < rowIndex; ++i)
	{
		if(i < rowIndex-i+1)
		{
			int a = lcm(res[i-1], i);
			res[i] *= res[i-1] / a;
			int b = i / a;
			res[i] *= (rowIndex-i+1) / b;
		}
		else
			res[i] = res[rowIndex-i];
	}
	return res;
}

//Pascal's Triangle
vector<vector<int> > generate(int numRows)
{
	vector<vector<int> > res;
	if(0 == numRows) return res;
	res.push_back(vector<int>(1, 1));
	res.resize(numRows);
	for(int i = 1; i < numRows; ++i)
	{
		res[i].resize(i+1, 1);
		for(int j = 1; j < i; ++j)
			res[i][j] = res[i-1][j-1] + res[i-1][j];
	}
	return res;
}

//Partition List
ListNode *partition2(ListNode *head, int x)
{
	if(NULL == head) return NULL;
	ListNode *less = new ListNode(0), *more = new ListNode(0);;
	ListNode *p = less, *q= more;
	while(NULL != head)
	{
		if(head->val < x)
		{
			p->next = head;
			p = p->next;
		}
		else
		{
			q->next = head;
			q = q->next;
		}
		head = head->next;
	}
	p->next = more->next;
	q->next = NULL;
	p = less->next;
	delete less;
	delete more;
	return p;
}

ListNode *partition(ListNode *head, int x)
{
	ListNode *less, *more, *p, *q;
	less = more = p = q = NULL;
	while(head)
	{
		if(head->val < x)
		{
			if(!less)
			{
				less = head;
				p = less;
			}
			else
			{
				p->next = head;
				p = head;
			}
		}
		else
		{
			if(!more)
			{
				more = head;
				q = more;
			}
			else
			{
				q->next = head;
				q = head;
			}
		}
		head = head->next;
	}
	if(p) p->next = NULL;
	if(q) q->next = NULL;
	if(less)
	{
		p->next = more;
		return less;
	}
	else
		return more;
}

//Palindrome Number
bool isPalindrome(int x)
{
	if(x < 0) return false;
	int a = 1; int b = 1;
	for(; x / b >= 10; b *= 10);
	while(a <= b)
	{
		if((x / a) % 10 != (x / b) % 10)
			return false;
		a *= 10; b /= 10;
	}
	return true;
}

bool isPalindrome2(int x)
{//本题不适合用递归方法，corner case诸如301103
	if(x < 0) return false;
	int div = 1;
	while(x / div >= 10)
	{
		div *= 10;
	}
	while(x != 0)
	{
		if(x / div != x % 10) return false;
		x = (x % div) / 10;
		div /= 100;
	}
	return true;
}

//Next Permutation
void nextPermutation(vector<int> &num)
{
	vector<int>::iterator pos = num.end()-1;
	while(pos > num.begin() && *(pos-1) >= *pos) pos--;
	if(num.begin() == pos)
		reverse(num.begin(), num.end());
	else
	{
		vector<int>::iterator j = num.end()-1;
		while(j >= pos && *j <= *(pos-1)) j--;
		iter_swap(pos-1, j);
		reverse(pos, num.end());
	}
}

//N-Queens II
bool isValidBoard(const vector<int> &pos, int row, int col)
{
	for(int i = 0; i < row; ++i)
	{
		if(col == pos[i] || row - i == abs(col - pos[i]))
			return false;
	}
	return true;
}

void getBoard(vector<int> &pos, int n, int row, int &count)
{
	if(row == n)
	{
		count++;
		return;
	}
	for(int i = 0; i < n; ++i)
	{
		if(isValidBoard(pos, row, i))
		{
			pos[row] = i;
			getBoard(pos, n, row+1, count);
		}
	}
}

int totalNQueens(int n)
{
	vector<int> pos(n, -1); // position for each row
	int count = 0;
	getBoard(pos, n, 0, count);
	return count;
}

//below is NQueens using array, much faster than vector, about six times 1second-6seconds

//bool isValidBoard(int *pos, int row, int col)
//{
//	for(int i = 0; i < row; ++i)
//	{
//		if(col == pos[i] || row - i == abs(col - pos[i]))
//			return false;
//	}
//	return true;
//}
//
//void getBoard(int *pos, int n, int row, int &count)
//{
//	if(row == n)
//	{
//		count++;
//		return;
//	}
//	for(int i = 0; i < n; ++i)
//	{
//		if(isValidBoard(pos, row, i))
//		{
//			pos[row] = i;
//			getBoard(pos, n, row+1, count);
//		}
//	}
//}
//
//int totalNQueens(int n)
//{
//	int * pos = new int[n]; // position for each row
//	int count = 0;
//	getBoard(pos, n, 0, count);
//	return count;
//}

//N-Queens
//recursive method
void generateBoard(vector<vector<string> > &res, vector<int> &pos)
{
	vector<string> item;
	for(int i = 0; i < pos.size(); ++i)
	{
		string s(pos.size(), '.');
		s[pos[i]] = 'Q';
		item.push_back(s);
	}
	res.push_back(item);
}

void getBoard(vector<vector<string> > &res, vector<int> &pos, int n, int row)
{
	if(row == n)
	{
		generateBoard(res, pos);
		return;
	}
	for(int i = 0; i < n; ++i)
	{
		if(isValidBoard(pos, row, i))
		{
			pos[row] = i;
			getBoard(res, pos, n, row+1);
		}
	}
}

vector<vector<string> > solveNQueens(int n)
{
	vector<int> pos(n, 0); // position for each row
	vector<vector<string> > res;
	getBoard(res, pos, n, 0);
	return res;
}

//iterative method 1
//this iterative method take advantage of std::next_permutation
int getErrorPos(const vector<int> &pos)
{
	for(int i = 1; i < pos.size(); ++i)
	{
		for(int j = 0; j < i; ++j)
		{
			if(i - j == abs(pos[j] - pos[i]))
				return i;
		}
	}
	return pos.size();
}

vector<vector<string> > solveNQueens2(int n)
{
	vector<vector<string> > res;
	vector<int> pos(n, 0);
	for(int i = 0; i < n; ++i)
		pos[i] = i;
	do
	{
		int errorPos = getErrorPos(pos);
		if(errorPos == n)
			generateBoard(res, pos);
		else
			sort(pos.begin()+errorPos+1, pos.end(), greater<int>());
	}
	while(next_permutation(pos.begin(), pos.end()));
	return res;
}

//Multiply Strings
string multiply(string num1, string num2)
{
	vector<int> res(num1.size() + num2.size(), 0);
	for(int i = 0; i < num1.size(); ++i)
	{
		int a = num1[num1.size()-1-i] - '0';
		for(int j = 0; j < num2.size(); ++j)
		{
			int b = num2[num2.size()-1-j] - '0';
			res[i+j] += a * b;
		}
	}
	string s; int carry = 0;
	for(vector<int>::iterator iter = res.begin(); iter != res.end(); ++iter)
	{
		*iter += carry;
		char c = '0' + *iter % 10;
		carry = *iter / 10;
		s = string(1, c) + s;
	}
	int k = 0;
	while(k < s.size() && '0' == s[k]) ++k;
	s = s.substr(k, s.size()-k);
	if(0 == s.size()) return "0";
	return s;
}

//Minimum Window Substring
string minWindow(string S, string T)
{
	vector<int> v(256, 0);
	for(int i = 0; i < T.size(); ++i)
		v[T[i]]++;
	int i = 0, j = 0, minSize = numeric_limits<int>::max(), count = 0, mini = 0, minj = -1;
	vector<int> w(256, 0);
	for(j = 0; j < S.size(); ++j)
	{
		if(0 == v[S[j]]) continue;
		if(++w[S[j]] <= v[S[j]])
			++count;
		if(count == T.size())
		{
			for(; i < j; ++i)
			{
				if(0 == v[S[i]]) continue;
				if(w[S[i]] == v[S[i]]) break;
				--w[S[i]];
			}
			if(j - i < minSize)
			{
				minSize = j - i;
				mini = i;
				minj = j;
			}
		}
	}
	return S.substr(mini, minj-mini+1);
}

//Minimum Path Sum
int minPathSum(vector<vector<int> > &grid)
{
	int m = grid.size();
	vector<int> minVec(grid[0]);
	int n = minVec.size();
	for(vector<int>::iterator iter = minVec.begin() + 1; iter < minVec.end(); ++iter)
	{
		*iter += *(iter - 1);
	}
	for(size_t i = 1; i < m; ++i)
	{
		minVec[0] += grid[i][0];
		for(size_t j = 1; j < n; ++j)
		{
			minVec[j] = (minVec[j - 1] < minVec[j]) ? minVec[j - 1] : minVec[j];
			minVec[j] += grid[i][j];
		}
	}
	return minVec.back();
}

//Minimum Depth of Binary Tree
//recursive
int minDepth(TreeNode *root)
{
	if(!root) return 0;
	if(!root->left && !root->right) return 1;
	if(root->left && root->right) return min(minDepth(root->left), minDepth(root->right)) + 1;
	if(root->left) return minDepth(root->left) + 1;
	if(root->right) return minDepth(root->right) + 1;
}

//Merge Two Sorted Lists
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
	ListNode *head = new ListNode(0);
	ListNode *result = head;
	while(l1 && l2)
	{
		ListNode *&temp = (l1->val < l2->val) ? l1 : l2;
		result->next = temp;
		result = temp;
		temp = temp->next;
	}
	if(l1) result->next = l1;
	else if(l2) result->next = l2;
	result = head->next;
	delete head;
	return result;
}

//Merge Sorted Array
void merge(int A[], int m, int B[], int n)
{
	while(n > 0)
	{
		if(m > 0 && A[m-1] > B[n-1])
			A[m+n-1] = A[--m];
		else
			A[m+n-1] = B[--n];
	}
}

class mycomparison
{
public:
  bool operator() (const pair<int, int> &a, const pair<int, int> &b) const
  {
	  return a.first > b.first;
  }
};

ListNode *mergeKLists(vector<ListNode *> &lists)
{
	ListNode *zero = new ListNode(0), *p = zero;
	//priority_queue<pair<int, int>, greater<int>()> q;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	int count = 0;
	for(int i = 0; i < lists.size(); ++i)
	{
		if(lists[i])
			q.push(make_pair(lists[i]->val, i));
		else
			++count;
	}
	while(count < lists.size())
	{
		pair<int, int> item = q.top();
		q.pop();
		p->next = lists[item.second];
		p = p->next;
		lists[item.second] = lists[item.second]->next;
		if(!lists[item.second])
			++count;
		else
			q.push(make_pair(lists[item.second]->val, item.second));
	}
	p = zero->next;
	delete zero;
	return p;
}

ListNode *mergeKLists2(vector<ListNode *> &lists)
{
	if(0 == lists.size()) return NULL;
	ListNode *head = new ListNode(0);
	ListNode *result = head;
	while(true)
	{
		int min = numeric_limits<int>::max();
		vector<ListNode *>::iterator miniter;
		for(vector<ListNode *>::iterator iter = lists.begin(); iter != lists.end(); ++iter)
		{
			if(*iter == NULL)
				continue;
			if((*iter)->val < min)
			{
				min = (*iter)->val;
				miniter = iter;
			}
		}
		if(numeric_limits<int>::max() == min)
			break;
		result->next = new ListNode(min);
		result = result->next;
		*miniter = (*miniter)->next;
	}
	result = head->next;
	delete head;
	return result;
}

//Merge Intervals
class intervalComparison
{
public:
	bool operator()(const Interval &a, const Interval &b) const
	{
		return a.start < b.start;
	}
} intervalComparisonObject;

vector<Interval> merge(vector<Interval> &intervals)
{
	sort(intervals.begin(), intervals.end(), intervalComparisonObject);
	int res = 0;
	for(int i = 1; i < intervals.size(); ++i)
	{
		if(intervals[res].end < intervals[i].start)
		{
			intervals[++res] = intervals[i];
		}
		else
			intervals[res].end = max(intervals[res].end, intervals[i].end);
	}
	if(0 < intervals.size()) intervals.resize(res+1);
	return intervals;
}

vector<Interval> merge2(vector<Interval> &intervals)
{
	sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b)->bool
	{
		return a.start < b.start;
	});
	vector<Interval> result;
	for(vector<Interval>::iterator iter = intervals.begin(); iter != intervals.end(); ++iter)
	{
		if(result.empty()) result.push_back(*iter);
		else if(iter->start <= result.back().end)
			result.back().end = max(iter->end, result.back().end);
		else
			result.push_back(*iter);
	}
	return result;
}

//Median of Two Sorted Arrays
int findKthSmallest(int A[], int m, int B[], int n, int k) {
  assert(m >= 0); assert(n >= 0); assert(k > 0); assert(k <= m+n);
 
  int i = (int)((double)m / (m+n) * (k-1));
  int j = (k-1) - i;
 
  assert(i >= 0); assert(j >= 0); assert(i <= m); assert(j <= n);
  // invariant: i + j = k-1
  // Note: A[-1] = -INF and A[m] = +INF to maintain invariant
  int Ai_1 = ((i == 0) ? INT_MIN : A[i-1]);
  int Bj_1 = ((j == 0) ? INT_MIN : B[j-1]);
  int Ai   = ((i == m) ? INT_MAX : A[i]);
  int Bj   = ((j == n) ? INT_MAX : B[j]);
 
  if (Bj_1 < Ai && Ai < Bj)
    return Ai;
  else if (Ai_1 < Bj && Bj < Ai)
    return Bj;
 
  assert((Ai > Bj && Ai_1 > Bj) ||
         (Ai < Bj && Ai < Bj_1));
 
  // if none of the cases above, then it is either:
  if (Ai < Bj)
    // exclude Ai and below portion
    // exclude Bj and above portion
    return findKthSmallest(A+i+1, m-i-1, B, j, k-i-1);
  else /* Bj < Ai */
    // exclude Ai and above portion
    // exclude Bj and below portion
    return findKthSmallest(A, i, B+j+1, n-j-1, k-j-1);
}

double findMedianSortedArrays(int A[], int m, int B[], int n)
{
	int s = m + n;
	if(s & 1)
		return findKthSmallest(A, m, B, n, (s + 1) >> 1);
	//else
	//	return static_cast<double>(findKthSmallest(A, m, B, n, s >> 1) + findKthSmallest(A, m, B, n, (s + 2) >> 1)) / 2;
}

//Maximum Subarray
int maxSubArray(int A[], int n)
{
	int max = numeric_limits<int>::min();
	int sum = 0;
	for(int i = 0; i < n; ++i)
	{
		sum += A[i];
		if(sum > max)
			max = sum;
		if(sum < 0)
			sum = 0;
	}
	return max;
}

//Maximum Depth of Binary Tree
int maxDepth(TreeNode *root)
{
	if(!root) return 0;
	if(!root->left && !root->right) return 1;
	if(root->left && root->right) return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	if(root->left) return maxDepth(root->left) + 1;
	if(root->right) return maxDepth(root->right) + 1;
}

//Maximal Rectangle
//best solution is O(M^N) by processing each col as largest rectangle in histogram
//a more optimized one with complexity of O(M^2 * N)
int maximalRectangle(vector<vector<char> > &matrix)
{
	int m = matrix.size();
	if(0 == m) return 0;
	int n = matrix[0].size();
	vector<vector<int> > accu(m, vector<int>(n, 0));
	for(int j = 0; j < m; ++j) accu[j][n-1] = matrix[j][n-1] - '0';
	for(int i = n-2; i >= 0; --i)
	{
		for(int j = 0; j < m; ++j)
		{
			if(matrix[j][i] != '0')
				accu[j][i] = accu[j][i+1] + 1;
		}
	}
	int maxArea = 0;
	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			if(matrix[i][j] == '0')
				continue;
			int minMargin = accu[i][j];
			if(maxArea >= (m-i) * minMargin)
				continue;
			for(int x = i; x < m; ++x)
			{
				minMargin = min(minMargin, accu[x][j]);
				int area = (x-i+1)*minMargin;
				maxArea = area > maxArea ? area : maxArea;
			}
		}
	}
	return maxArea;
}

//a optimized one, with still O(M^2 * N^2) complexity
int maximalRectangle2(vector<vector<char> > &matrix)
{
	int m = matrix.size();
	if(0 == m) return 0;
	int n = matrix[0].size();
	int maxArea = 0;
	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			if(matrix[i][j] == '0')
				continue;
			if(maxArea >= (m-i) * (n-j))
				continue;
			int maxRight = n;
			for(int x = i; x < m; ++x)
			{
				if(maxArea >= (maxRight-j)*(m-i)) break;
				int y;
				for(y = j; y < maxRight; ++y)
				{
					if(matrix[x][y] == '0') break;
				}
				maxRight = y;
				int area = (y-j)*(x-i+1);
				maxArea = area > maxArea ? area : maxArea;
			}
		}
	}
	return maxArea;
}

//又是一个DP问题，实现了简单的DP方法O(M^2 * N^2),KO  cont
//还有O(M^2 * N)和O(M * N)方法
//http://www.drdobbs.com/database/184410529
int maximalRectangle3(vector<vector<char> > &matrix)
{//采用较简单的DP方法，复杂度为O(M^2 * N^2)，还有更好的方法待实现
	int m = matrix.size();
	if(0 == m) return 0;
	int n = matrix[0].size();
	int maxArea = 0;
	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			int ry = j;
			int rmax = m;
			while(ry < n)
			{
				if('0' == matrix[i][ry])
					break;
				int rx = i + 1;
				while(rx < rmax)
				{
					if('0' == matrix[rx][ry])
						break;
					++rx;
				}
				if(rmax > rx)
					rmax = rx;
				int area = (rx - i) * (ry - j + 1);
				if(maxArea < area)
					maxArea = area;
				++ry;
			}
		}
	}
	return maxArea;
}

//Longest Valid Parentheses
//one scan from left to right with a stack
int longestValidParentheses(string s)
{
	int maxlen = 0;
	stack<int> stk;
	stk.push(-1);
	for(int i = 0; i < s.size(); ++i)
	{
		if(s[i] == '(')
			stk.push(i);
		else
		{
			if(stk.size() > 1 && s[stk.top()] == '(')
			{
				stk.pop();
				maxlen = i - stk.top() > maxlen ? i - stk.top() : maxlen;
			}
			else
				stk.push(i);
		}
	}
	return maxlen;
}

//double scan from two end
int longestValidParentheses2(string s)
{
	int n = s.size();
	if(n < 2) return 0;
	int i = 0;
	int maxlen = 0;
	int count = 0;
	int begin = 0;
	//if the total number of left > right, only this loop is fine.
	while(i < n)
	{
		if(s[i] =='(')
			++count;
		if(s[i] ==')')
			--count;
		++i;
		if(0 == count)
			maxlen = max(maxlen, i - begin);
		if(0 > count)
		{
			begin = i;
			count = 0;
		}
	}
	i = begin = n - 1;
	count = 0;
	//if the total number of right < left, only this loop is fine.
	while(i >= 0)
	{
		if(s[i] =='(')
			--count;
		if(s[i] ==')')
			++count;
		--i;
		if(0 == count)
			maxlen = max(maxlen, begin - i);
		if(0 > count)
		{
			begin = i;
			count = 0;
		}
	}
	return maxlen;
}

//Longest Substring Without Repeating Characters
//within a O(n) one-time linear scan by using a extra table to record the character that have appeared
int lengthOfLongestSubstring(string s)
{
	vector<bool> v(256, false);
	int maxlen = 0;
	int i = 0, j = 0;
	for(; j < s.size(); ++j)
	{
		if(v[s[j]])
		{
			maxlen = max(j - i, maxlen);
			while(s[i] != s[j])
			{
				v[s[i]] = false;
				++i;
			}
			++i;
		}
		else
			v[s[j]] = true;
	}
	maxlen = max(j - i, maxlen);
	return maxlen;
}

int lengthOfLongestSubstring2(string s)
{
	int n = s.size();
	if(n < 2) return n;
	vector<int> result(n, 1); //result[i]存储以s[i]为最右端元素的最长子串
	for(size_t i = 1; i < n; ++i)
	{
		int j = i - 1;
		while(i - j <= result[i - 1])
		{
			if(s[j] == s[i])
				break;
			--j;
		}
		result[i] = i - j;
	}
	int max = 1;
	for(vector<int>::iterator iter = result.begin(); iter != result.end(); ++iter)
	{
		if(max < *iter)
			max = *iter;
	}
	return max;
}

//Longest Palindromic Substring
string longestPalindrome(string s)
{//使用传统的DP方法O(n^2)，还有效率更高的Manacher算法时间达到O(n)
	int n = s.size();
	if(n < 3) return s;
	int maxLeft = 0;
	int maxLen = 1;
	vector<vector<bool> > flag(n, vector<bool>(n, false));
	for(size_t i = 0; i < n - 1; ++i)
	{
		flag[i][i] = true;
	}
	for(size_t i = 0; i < n - 1; ++i)
	{
		if(s[i] == s[i + 1])
		{
			flag[i][i + 1] = true;
			maxLeft = i;
			maxLen = 2;
		}
	}
	flag[n - 1][n - 1] = true;
	for(int len = 3; len <= n; ++len)
	{
		for(int i = 0; i + len - 1 < n; ++i)
		{
			int j = i + len - 1;
			if(s[i] == s[j] && flag[i + 1][j - 1])
			{
				flag[i][j] = true;
				if(maxLen < len)
				{
					maxLen = len;
					maxLeft = i;
				}
			}
		}
	}
	return s.substr(maxLeft, maxLen);
}

//Longest Common Prefix
string longestCommonPrefix(vector<string> &strs)
{
	string result = "";
	if(0 == strs.size()) return result;
	if(1 == strs.size()) return strs[0];
	size_t index = 0;
	while(true)
	{
		if(index + 1 > strs[0].size())
			return result;
		char c = strs[0][index];
		for(size_t i = 1; i < strs.size(); ++i)
		{
			if(index + 1 > strs[i].size() || c != strs[i][index])
				return result;
		}
		result.append(1, c);
		++index;
	}
}

//Letter Combinations of a Phone Number
void letterCombinations(const string &digits, int index, string &item, 
						vector<string> &result, const vector<string> &alphabetMap)
{
	if(digits.size() == index)
	{
		result.push_back(item);
		return;
	}
	int num = digits[index] - '0';
	for(size_t i = 0; i < alphabetMap[num].size(); ++i)
	{
		item[index] = alphabetMap[num][i];
		letterCombinations(digits, index + 1, item, result, alphabetMap);
	}
}

vector<string> letterCombinations(string digits)
{
	vector<string> alphabetMap;
	vector<string> result;
	string item(digits.size(), ' ');
	alphabetMap.push_back("");
	alphabetMap.push_back("");
	alphabetMap.push_back("abc");
	alphabetMap.push_back("def");
	alphabetMap.push_back("ghi");
	alphabetMap.push_back("jkl");
	alphabetMap.push_back("mno");
	alphabetMap.push_back("pqrs");
	alphabetMap.push_back("tuv");
	alphabetMap.push_back("wxyz");
	letterCombinations(digits, 0, item, result, alphabetMap);
	return result;
}
	

//Length of Last Word
int lengthOfLastWord(const char *s)
{
	int n = strlen(s);
	if(0 == n) return 0;
	int end = n - 1;
	while(end >= 0 && s[end] == ' ') --end;
	int beg = end;
	while(beg >= 0 && s[beg] != ' ') --beg;
	return end - beg;
}

//Largest Rectangle in Histogram
//29th Oct 2012
int largestRectangleArea(vector<int> &height)
{
	int n = height.size();
	vector<int> leftBound(n, -1);
	vector<int> rightBound(n, n);
	for(int i = 1; i < n; ++i)
	{
		int j = i - 1;
		while(j >= 0)
		{
			if(height[j] < height[i])
				break;
			else
				j = leftBound[j];
		}
		leftBound[i] = j;
	}
	for(int i = n - 2; i >= 0; --i)
	{
		int j = i + 1;
		while(j < n)
		{
			if(height[j] < height[i])
				break;
			else
				j = rightBound[j];
		}
		rightBound[i] = j;
	}
	int maxArea = 0;
	for(int i = 0; i < n; ++i)
	{
		int area = (rightBound[i] - leftBound[i] - 1) * height[i];
		maxArea = max(maxArea, area);
	}
	return maxArea;
}

//optimized version
int largestRectangleArea2(vector<int> &height)
{
	if(0 == height.size()) return 0;
	if(1 == height.size()) return height[0];
	vector<int> leftBound(height.size(), 0);
	for(int i = 1; i < height.size(); ++i)
	{
		int j = i - 1;
		while(j >= 0)
		{
			if(height[j] < height[i])
				break;
			else
				j = leftBound[j] - 1;
		}
		leftBound[i] = j + 1;
	}
	vector<int> rightBound(height.size(), height.size()-1);
	for(int i = height.size() - 2; i >= 0; --i)
	{
		int j = i + 1;
		while(j < height.size())
		{
			if(height[j] < height[i])
				break;
			else
				j = rightBound[j] + 1;
		}
		rightBound[i] = j - 1;
	}
	int max = 0;
	for(int i = 0; i < height.size(); ++i)
	{
		int area = rightBound[i] - leftBound[i] + 1;
		area *= height[i];
		if(max < area)
			max = area;
	}
	return max;
}

//easy logic, but not scalable, O(N^2) on the worst case
int largestRectangleArea3(vector<int> &height)
{
	if(0 == height.size()) return 0;
	if(1 == height.size()) return height[0];
	vector<int> leftBound(height.size(), 0);
	for(int i = 1; i < height.size(); ++i)
	{
		for(int j = i - 1; j >= 0; --j)
			if(height[j] < height[i])
			{
				leftBound[i] = j + 1;
				break;
			}
	}
	vector<int> rightBound(height.size(), height.size()-1);
	for(int i = height.size() - 2; i >= 0; --i)
	{
		for(int j = i + 1; j < height.size(); ++j)
			if(height[j] < height[i])
			{
				rightBound[i] = j - 1;
				break;
			}
	}
	int max = 0;
	for(int i = 0; i < height.size(); ++i)
	{
		int area = rightBound[i] - leftBound[i] + 1;
		area *= height[i];
		if(max < area)
			max = area;
	}
	return max;
}

//Jump Game II
int jump(int A[], int n)
{
	if(1 == n) return 0;
	int k = 0, i = 0, step = 0, right = 0;
	while(true)
	{
		while(i <= k)
		{
			right = max(right, i + A[i]);
			++i;
		}
		if(right >= n-1 || right == k) break;
		++step;
		k = right;
	}
	if(right < n-1) return -1;
	return step;
}

int jump2(int A[], int n)
{
	int max = 0;
	int first = 0;
	int last = 0;
	int step = 0;
	if(1 == n) return 0;
	while(true)
	{
		for(int i = first; i <= last; ++i)
		{
			if(max < A[i] + i)
				max = A[i] + i;
		}
		if(max == last)
			return -1;
		first = last + 1;
		last = max;
		++step;
		if(max >= n - 1)
			break;
	}
	return step;
}

//Jump Game
bool canJump(int A[], int n)
{
	int k = 0, i;
	for(i = 0; i <= k && i < n; ++i)
	{
		k = max(k, i+A[i]);
		if(k >= n-1) return true;
	}
	return i == n;
}

bool canJump2(int A[], int n)
{
	int max = 0;
	for(int i = 0; i < n && i <= max; ++i)
	{
		if(max < i + A[i])
			max = i + A[i];
		if(max >= n - 1) return true;
	}
	return false;
}


//Interleaving String
//wow! extremly elegant code!
bool isInterleave(const string &s1, int a, const string &s2, int b, const string &s3, int c)
{
	if(0 == c) return true;
	if(0 == a || 0 == b) return s1.substr(0, a) + s2.substr(0, b) == s3.substr(0, c);
	return (s3[c-1] == s1[a-1] ? isInterleave(s1, a-1, s2, b, s3, c-1) : false) || (s3[c-1] == s2[b-1] ? isInterleave(s1, a, s2, b-1, s3, c-1) : false);
}

bool isInterleave(string s1, string s2, string s3)
{
	int a = s1.size(), b = s2.size(), c = s3.size();
	if(a + b != c) return false;
	return isInterleave(s1, a, s2, b, s3, c);
}

//Integer to Roman

//Insert Interval
vector<Interval> insert(vector<Interval> &intervals, Interval newInterval)
{
	vector<Interval> res;
	int i = 0;
	for(; i < intervals.size() && intervals[i].end < newInterval.start; ++i)
		res.push_back(intervals[i]);
	if( i == intervals.size())
	{
		res.push_back(newInterval);
		return res;
	}
	newInterval.start = min(newInterval.start, intervals[i].start);
	for(; i < intervals.size(); ++i)
	{
		if(intervals[i].start > newInterval.end) break;
		newInterval.end = max(newInterval.end, intervals[i].end);
	}
	res.push_back(newInterval);
	res.insert(res.end(), intervals.begin() + i, intervals.end());
	return res;
}

vector<Interval> insert2(vector<Interval> &intervals, Interval newInterval)
{
	vector<Interval> result;
	vector<Interval>::iterator iter = intervals.begin();
	for(;iter != intervals.end() && iter->end < newInterval.start; ++iter)
		result.push_back(*iter);
	if(iter == intervals.end())
	{
		result.push_back(newInterval);
		return result;
	}
	else if(iter->start <= newInterval.end)
	{
		result.push_back(Interval(min(iter->start, newInterval.start), max(iter->end, newInterval.end)));
		++iter;
	}
	else
	{
		result.push_back(newInterval);
		result.insert(result.end(), iter, intervals.end());
		return result;
	}

	while(iter != intervals.end())
	{
		if(iter->start > result.back().end)
			break;
		result.back().end = max(result.back().end, iter->end);
		++iter;
	}

	result.insert(result.end(), iter, intervals.end());

	return result;
}

vector<Interval> insert3(vector<Interval> &intervals, Interval newInterval)
{
	vector<Interval> result;
	if(intervals.empty())
	{
		result.push_back(newInterval);
		return result;
	}
	vector<Interval>::iterator iter;
	bool flag = false;
	for(iter = intervals.begin(); iter != intervals.end(); ++iter)
	{
		if(flag) break;
		if(iter->end < newInterval.start)
			result.push_back(*iter);
		else if(iter->end == newInterval.start)
		{
			result.push_back(Interval(iter->start, newInterval.end));
			flag = true;
		}
		else
		{
			if(newInterval.end < iter->start)
			{
				result.push_back(newInterval);
				result.push_back(*iter);
				flag = true;
			}
			else
			{
				int low, high;
				low = iter->start < newInterval.start ? iter->start : newInterval.start;
				high = iter->end < newInterval.end ? newInterval.end : iter->end;
				result.push_back(Interval(low, high));
				flag = true;
			}
		}
	}
	if(!flag)
		result.push_back(newInterval);
	flag = false;
	while(iter != intervals.end())
	{
		if(flag)
			result.push_back(*iter);
		else if(iter->start > result.back().end)
		{
			result.push_back(*iter);
			flag = true;
		}
		else if(iter->end > result.back().end)
			result.back().end = iter->end;
		++iter;
	}
	return result;
}

//Implement strStr()
char *strStr(char *haystack, char *needle)
{
	if(NULL == needle || '\0' == *needle) return haystack;
	if(NULL == haystack) return NULL;
	while(*haystack != '\0')
	{
		char *p = haystack;
		char *q = needle;
		while(*p == *q)
		{
			++p; ++q;
			if('\0' == *q)
				return haystack;
			if('\0' == *p)
				return NULL;
		}
		++haystack;
	}
	return NULL;
}

char *StrStr2(char *str, char *target)
{//version by ihasleetcode
	if (!*target) return str;
	char *p1 = (char*)str;
	while (*p1) {
		char *p1Begin = p1, *p2 = (char*)target;
		while (*p1 && *p2 && *p1 == *p2) {
			p1++;
			p2++;
		}
		if (!*p2)
			return p1Begin;
		p1 = p1Begin + 1;
	}
	return NULL;
}
char* StrStr(char *str, char *target)
{//version by ihasleetcode
	if (!*target) return str;
	char *p1 = (char*)str, *p2 = (char*)target;
	char *p1Adv = (char*)str;
	while (*++p2)
		p1Adv++;
	while (*p1Adv) {
		char *p1Begin = p1;
		p2 = (char*)target;
		while (*p1 && *p2 && *p1 == *p2) {
			p1++;
			p2++;
		}
		if (!*p2)
			return p1Begin;
		p1 = p1Begin + 1;
		p1Adv++;
	}
	return NULL;
}

//Gray Code
vector<int> grayCode(int n)
{
	vector<int> result;
	result.push_back(0);
	n = 2 << n - 1;
	for(int i = 1; i < n; ++i)
	{
		int temp = i & 3;
		if(0 == temp || 3 == temp)
			result.push_back(result[i >> 1] << 1);
		else
			result.push_back((result[i >> 1] << 1) + 1);
	}
	return result;
}

vector<int> grayCode2(int n)
{
	vector<int> res;
	n = 1 << n;
	for(int i = 0; i < n; ++i)
		res.push_back(i ^ (i >> 1));
	return res;
}

vector<int> grayCode3(int n)
{
	vector<int> res;
	res.push_back(0);
	int base = 1;
	while(n > 0)
	{
		for(int i = res.size()-1; i >= 0; --i)
			res.push_back(base+res[i]);
		base <<= 1;
		--n;
	}
	return res;
}



//Generate Parentheses
void generateParenthesis(vector<string> &res, string item, int left, int right)
{
	if(0 == right)
	{
		res.push_back(item);
		return;
	}
	if(left > 0)
		generateParenthesis(res, item + "(", left-1, right);
	if(right > left)
		generateParenthesis(res, item + ")", left, right-1);
}

vector<string> generateParenthesis(int n)
{
	vector<string> res;
	string item;
	generateParenthesis(res, item, n, n);
	return res;
}

void generateParenthesis2(vector<string> &result, string item, int left, int right)
{
	if(0 == right && 0 == left)
		result.push_back(item);
	else
	{
		if(left > 0)
		{
			item.append(1, '(');
			generateParenthesis2(result, item, left - 1, right);
			if(left != right)
			{
				item[item.size() - 1] = ')';
				generateParenthesis2(result, item, left, right - 1);
			}
		}
		else if(0 == left)
		{
			item.append(right, ')');
			result.push_back(item);
		}
	}
}

vector<string> generateParenthesis2(int n)
{
	vector<string> result;
	string item;
	generateParenthesis2(result, item, n, n);
	return result;
}

void generateParenthesis3(vector<string> &result, string item, int left, int right, int count)
{
	if(0 == left && 0 == right)
	{
		result.push_back(item);
		return;
	}
	if(left > 0)
	{
		item[count] = '(';
		generateParenthesis3(result, item, left - 1, right, count + 1);
	}
	if(right > left)
	{
		item[count] = ')';
		generateParenthesis3(result, item, left, right - 1, count + 1);
	}
}

vector<string> generateParenthesis3(int n)
{
	vector<string> result;
	string item(n << 1, ' ');
	generateParenthesis3(result, item, n, n, 0);
	return result;
}

//Flatten Binary Tree to Linked List
//recursive
TreeNode *flatten(TreeNode *root, TreeNode *succ)
{
	if(!root) return NULL;
	if(!root->left && !root->right)
	{
		root->right = succ;
		return root;
	}
	TreeNode *l = flatten(root->left, root->right ? root->right : succ);
	TreeNode *r = flatten(root->right, succ);
	root->left = NULL;
	root->right = l ? l : r;
	return root;
}

void flatten(TreeNode *root)
{
	flatten(root, NULL);
}

//First Missing Positive
//the key idea is to put every element in A such that A[i] = i + 1
int firstMissingPositive(int A[], int n)
{
	int i = 0, j = 0;
	while(i < n)
	{
		if(A[i] < 1 || A[i] > n || i == A[i] - 1) //越界或者刚好在位
			++i;
		else if(i > A[i] - 1) //该位应该在前面，因为前面数据都处理过了，没必要swap再处理
			A[A[i]- 1] = A[i++];
		else if(A[A[i] -1] != A[i]) //和后面某位交换，无需++i
			iter_swap(A + i, A + A[i] - 1);
		else      //后面那位刚好在位，无需交换
			++i;
	}
	for(int i = 0; i < n; ++i)
	{
		if(A[i] != i + 1)
			return i + 1;
	}
	return n + 1;
}

//using extra space
int firstMissingPositive2(int A[], int n)
{
	vector<int> vec(n, 0);
	for(int i = 0; i < n; ++i)
	{
		if(A[i] > 0 && A[i] <= n)
			vec[A[i]-1] = A[i];
	}
	for(int i = 0; i < n; ++i)
		if(vec[i] != i + 1) return i + 1;
	return n + 1;
}

//原地
int firstMissingPositive3(int A[], int n)
{
	int index = 0;
	while(index < n)
	{
		if(A[index] < 1 || A[index] > n)
			++index;
		else if(A[index] != index + 1)
		{
			if(A[A[index] - 1] == A[index])
			{
				++index;
				continue;
			}
			int temp = A[A[index] - 1];
			A[A[index] - 1] = A[index];
			A[index] = temp;
		}
		else
			++index;
	}
	for(int i = 0; i < n; ++i)
	{
		if(A[i] != i + 1)
			return i + 1;
	}
	return n + 1;
}

//Edit Distance
int minDistance(string word1, string word2)
{
	int m = word1.size(), n = word2.size();
	vector<vector<int> > distanceMap(m + 1, vector<int>(n + 1, 0));
	for(int i = 0; i <= m; ++i)
		distanceMap[i][0] = i;
	for(int j = 0; j <= n; ++j)
		distanceMap[0][j] = j;
	for(int i = 1; i <= m; ++i)
		for(int j = 1; j <= n; ++j)
		{
			if(word1[i-1] == word2[j-1])
				distanceMap[i][j] = distanceMap[i-1][j-1];
			else
			{
				distanceMap[i][j] = min(distanceMap[i-1][j], distanceMap[i][j-1]);
				distanceMap[i][j] = min(distanceMap[i][j], distanceMap[i-1][j-1]);
				++distanceMap[i][j];
			}
		}
		return distanceMap[m][n];
}

//Divide Two Integers
void divide(int dividend, int divisor, int &q, int &r)
{ 
	if(dividend < divisor)  //还有一个case没过，即MIN_INT32, 3
	{
		q = 0;
		r = dividend;
		return;
	}
	divide(dividend >> 1, divisor, q, r);
	q = q << 1; r = r << 1;
	if(dividend & 1) ++r;
	if(r >= divisor)
	{
		r = r - divisor;
		++q;
	}
}

int divide(int dividend, int divisor)
{
	bool flag = true;
	int q = 0, r = 0;
	if(1 == divisor) return dividend;
	if(-1 == divisor) return -dividend;
	if(2 == divisor) return dividend >> 1;
	if(-2 == divisor) return -dividend >> 1;
	if(dividend == divisor) return 1;
	if(dividend + divisor == 0) return -1;
	if(dividend < 0)
	{
		dividend = -dividend;
		flag = !flag;
	}
	if(divisor < 0)
	{
		divisor = -divisor;
		flag = !flag;
	}
	divide(dividend, divisor, q, r);
	return flag ? q : -q;
}

//Distinct Subsequences
//iterative method with O(n) space
int numDistinct2(string S, string T)
{
	vector<int> v(S.size() + 1, 1);
	for(int i = 1; i <= T.size(); ++i)
	{
		int prev = v[i-1];
		fill(v.begin(), v.begin() + i, 0);	
		for(int j = i; j <= S.size(); ++j)
		{
			int curr = v[j];
			v[j] = v[j-1] + (S[j-1] == T[i-1] ? prev : 0);
			prev = curr;
		}
 	}
	return v.back();
}

//recursive method, TLE when judge large
int numDistinct(const string &S, int a, const string &T, int b)
{
	if(a < b) return 0;
	if(0 == b) return 1;
	if(S[a-1] != T[b-1]) return numDistinct(S, a-1, T, b);
	return numDistinct(S, a-1, T, b-1) + numDistinct(S, a-1, T, b);
}

int numDistinct(string S, string T)
{
	int a = S.size(), b = T.size();
	return numDistinct(S, a, T, b);
}

//Decode Ways
bool decodable(char c)
{
	if('9' >= c && '1' <= c)
		return true;
	return false;
}

bool decodable(char c, char next)
{
	if('1' == c && '0' <= next && '9' >= next)
		return true;
	else if('2' == c && '0' <= next && '6' >= next)
		return true;
	return false;
}

int numDecodings(string s)
{
	int n = s.size();
	if(0 == n) return 0;
	int prev = 1;
	int curr = decodable(s[0]) ? 1 : 0;
	if(1 == n) return curr;
	
	for(int i = 1; i < n; ++i)
	{
		int temp = decodable(s[i]) ? curr : 0;
		temp += decodable(s[i - 1], s[i]) ? prev : 0;
		prev = curr;
		curr = temp;
	}
	return curr;
}

//Count and Say
string countAndSay(int n)
{
	string curr = "1";
	string next;
	while(n > 1)
	{
		next.clear();
		string::iterator iter = curr.begin();
		while(iter != curr.end())
		{
			string::iterator jter = iter + 1;
			while(jter != curr.end() && *jter == *iter) ++jter;
			char c = '0';
			c += jter - iter;
			next.append(1, c);
			next.append(1, *iter);
			iter = jter;
		}
		--n;
		curr = next;
	}
	return curr;
}

//Convert Sorted List to Binary Search Tree
TreeNode *sortedListToBST(ListNode *head, ListNode *last)
{
	if(head == last) return NULL;
	if(head->next == last) return new TreeNode(head->val);
	ListNode *p = head, *q = head;
	while(q != last)
	{
		q = q->next;
		if(q == last) break;
		q = q->next;
		p = p->next;
	}
	TreeNode *root = new TreeNode(p->val);
	root->left = sortedListToBST(head, p);
	root->right = sortedListToBST(p->next, last);
	return root;
}

TreeNode *sortedListToBST(ListNode *head)
{
	return sortedListToBST(head, NULL);
}

//Convert Sorted Array to Binary Search Tree
TreeNode *sortedArrayToBST(const vector<int> &num, int i, int j)
{
	if(i > j) return NULL;
	int mid = i + (j - i) / 2;
	TreeNode *root = new TreeNode(num[mid]);
	root->left = sortedArrayToBST(num, i, mid-1);
	root->right = sortedArrayToBST(num, mid+1, j);
	return root;
}

TreeNode *sortedArrayToBST(vector<int> &num)
{
	return sortedArrayToBST(num, 0 , num.size()-1);
}

//Container With Most Water
int maxArea(vector<int> &height)
{
	if(height.size() < 2) return 0;
	int i = 0, j = height.size()-1;
	int maxArea = (j - i) * min(height[i], height[j]);
	int left = height[i], right = height[j];
	while(i < j)
	{
		if(left <= right)
		{
			while(++i < j && height[i] <= left);
			left = height[i];
		}
		else
		{
			while(i < --j && height[j] <= right);
			right = height[j];
		}
		int area = (j - i) * min(height[i], height[j]);
		maxArea = max(maxArea, area);
	}
	return maxArea;
}

int maxArea2(vector<int> &height)
{
	vector<int>::iterator iter = height.begin();
	vector<int>::iterator jter = height.end() - 1;
	int max = *iter < *jter ? *iter : *jter;
	max *= jter - iter;
	int left = *iter, right = *jter;
	int area;
	while(iter < jter)
	{
		if(left <= right)
		{
			while(iter < jter && *++iter <= left);
			left = *iter;
		}
		else
		{
			while(iter < jter && *--jter <= right);
			right = *jter;
		}
		area = left < right ? left : right;
		area *= jter - iter;
		if(area > max)
			max = area;
	}
	return max;
}

//Construct Binary Tree from Inorder and Postorder Traversal
//recursive
TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder, int i, int j, int len)
{
	if(0 == len) return NULL;
	if(1 == len) return new TreeNode(inorder[i]);
	int k = postorder[j+len-1];
	vector<int>::iterator pos = find(inorder.begin()+i, inorder.begin()+i+len, k);
	int llen = pos- i - inorder.begin(), rlen = len - llen - 1;
	TreeNode *root = new TreeNode(*pos);
	root->left = buildTree(inorder, postorder, i, j, llen);
	root->right = buildTree(inorder, postorder, i+llen+1, j + llen, rlen);
	return root;
}

TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
{
	assert(inorder.size() == postorder.size());
	return buildTree(inorder, postorder, 0, 0, inorder.size());
}

//Construct Binary Tree from Preorder and Inorder Traversal
//recursive
TreeNode *buildTree2(vector<int> &preorder, vector<int> &inorder, int i, int j, int len)
{
	if(0 == len) return NULL;
	if(1 == len) return new TreeNode(inorder[j]);
	int k = preorder[i];
	vector<int>::iterator pos = find(inorder.begin()+j, inorder.begin()+j+len, k);
	int llen = pos- j - inorder.begin(), rlen = len - llen - 1;
	TreeNode *root = new TreeNode(*pos);
	root->left = buildTree2(preorder, inorder, i+1, j, llen);
	root->right = buildTree2(preorder, inorder, i+llen+1, j+1+llen, rlen);
	return root;
}

TreeNode *buildTree2(vector<int> &preorder, vector<int> &inorder)
{
	assert(inorder.size() == preorder.size());
	return buildTree2(preorder, inorder, 0, 0, inorder.size());
}

//Combinations
void combine(vector<vector<int> > &result, vector<int> &item, int beg, int end, int k)
{
	if(0 == k)
	{
		result.push_back(item);
		return;
	}
	if(beg + k <= end)
	{
		combine(result, item, beg + 1, end, k);
		item[item.size() - k] = beg;
		combine(result, item, beg + 1, end, k - 1);
	}
}

vector<vector<int> > combine(int n, int k)
{
	vector<vector<int> > result;
	vector<int> item(k, 0);
	combine(result, item, 1, n + 1, k);
	return result;
}

//Combination Sum II
void combinationSum2(vector<int> &candidates, int target, int n, vector<int> itemVec, vector<vector<int> > &result)
{
	if(0 == target)
	{
		result.push_back(itemVec);
		return;
	}
	if(target > 0 && n < candidates.size())
	{
		int k;
		for(k = n + 1; k < candidates.size() && candidates[k] == candidates[n]; ++k);
		combinationSum2(candidates, target, k, itemVec, result);
		itemVec.push_back(candidates[n]);
		combinationSum2(candidates, target - candidates[n], n + 1, itemVec, result);
	}
	return;
}

vector<vector<int> > combinationSum2(vector<int> &candidates, int target)
{
	sort(candidates.begin(), candidates.end());
	vector<vector<int> > result;
	vector<int> itemVec;
	combinationSum2(candidates, target, 0, itemVec, result);
	return result;
}

//Combination Sum
void combinationSum(vector<int> &candidates, int target, int n, vector<int> itemVec, vector<vector<int> > &result)
{
	if(0 == target)
	{
		result.push_back(itemVec);
		return;
	}
	if(target >= 0 && n < candidates.size())
	{
		combinationSum(candidates, target, n + 1, itemVec, result);
		itemVec.push_back(candidates[n]);
		combinationSum(candidates, target - candidates[n], n, itemVec, result);
	}
	return;
}

vector<vector<int> > combinationSum(vector<int> &candidates, int target)
{
	sort(candidates.begin(), candidates.end());
	vector<vector<int> > result;
	vector<int> itemVec;
	combinationSum(candidates, target, 0, itemVec, result);
	return result;
}

//Climbing Stairs
int climbStairs(int n)
{
	if(n < 0) return -1;
	if(0 == n || 1 == n)
		return 1;
	int pre = 1, curr = 1;
	for(int i = 2; i <= n; ++i)
	{
		int tmp = pre + curr;
		pre = curr;
		curr = tmp;
	}
	return curr;
}

//Binary Tree Zigzag Level Order Traversal
vector<vector<int> > zigzagLevelOrder(TreeNode *root)
{
	vector<vector<int> > res;
	if(!root) return res;
	queue<TreeNode*> q;
	q.push(root);
	int curr = 1, next = 0;
	vector<int> v;
	bool direction = false;
	while(!q.empty())
	{
		root = q.front();
		q.pop();
		v.push_back(root->val);
		if(root->left) {q.push(root->left); ++next;}
		if(root->right) {q.push(root->right); ++next;}
		if(--curr == 0)
		{
			if(direction) reverse(v.begin(), v.end());
			res.push_back(v);
			curr = next;
			next = 0;
			v.clear();
			direction = !direction;
		}
	}
	return res;
}

//Binary Tree Maximum Path Sum
void maxPathSum(TreeNode *root, int &m, int &mr)
{
	m = mr = 0;
	if(!root) return;
	int lm, rm, lmr, rmr;
	maxPathSum(root->left, lm, lmr);
	maxPathSum(root->right, rm, rmr);
	if(root->left && root->right)
	{
		m = max(lm, rm);
		m = max(m, root->val + max(lmr, 0) + max(rmr, 0));
		mr = root->val;
		mr += max(0, max(lmr, rmr));
	}
	else if(root->left)
	{
		mr = root->val + max(0, lmr);
		m = max(mr, lm);
	}
	else if(root->right)
	{
		mr = root->val + max(0, rmr);
		m = max(mr, rm);
	}
	else
		m = mr = root->val;
}

int maxPathSum(TreeNode *root)
{
	int m, mr;
	maxPathSum(root, m, mr);
	return m;
}

//Binary Tree Level Order Traversal
//vector<vector<int> > levelOrderBottom(vector<vector<int> > &res, TreeNode *root, int level)
//{
//	if(!root) return;
//	levelOrderBottom(res, root->left, level+1);
//	levelOrderBottom(res, root->right, level+1);
//}
//
//vector<vector<int> > levelOrderBottom(TreeNode *root)
//{
//	vector<vector<int> > res;
//	if(!root) return res;
//	levelOrderBottom(res, root, 1);
//	return res;
//}

//Binary Tree Level Order Traversal II
//a little bit revision on former version
vector<vector<int> > levelOrderBottom2(TreeNode *root)
{
	vector<vector<int> > res;
	if(!root) return res;
	queue<TreeNode*> q;
	q.push(root);
	int curr = 1, next = 0;
	vector<int> v;
	while(!q.empty())
	{
		root = q.front();
		q.pop();
		v.push_back(root->val);
		if(root->left) {q.push(root->left); ++next;}
		if(root->right) {q.push(root->right); ++next;}
		if(--curr == 0)
		{
			res.push_back(v);
			curr = next;
			next = 0;
			v.clear();
		}
	}
	reverse(res.begin(), res.end());
	return res;
}

//Binary Tree Level Order Traversal
vector<vector<int> > levelOrder(TreeNode *root)
{
	vector<vector<int> > res;
	if(!root) return res;
	queue<TreeNode*> q;
	q.push(root);
	int curr = 1, next = 0;
	vector<int> v;
	while(!q.empty())
	{
		root = q.front();
		q.pop();
		v.push_back(root->val);
		if(root->left) {q.push(root->left); ++next;}
		if(root->right) {q.push(root->right); ++next;}
		if(--curr == 0)
		{
			res.push_back(v);
			curr = next;
			next = 0;
			v.clear();
		}
	}
	return res;
}

//Binary Tree Inorder Traversa
vector<int> inorderTraversal(TreeNode *root)
{
	vector<int> result;
	stack<TreeNode*> s;
	TreeNode *p = root;
	while(p || !s.empty())
	{
		if(p)
		{
			s.push(p);
			p = p->left;
		}
		else
		{
			p = s.top();
			result.push_back(p->val);
			s.pop();
			p = p->right;
		}
	}
	return result;
}

//Best Time to Buy and Sell Stock
int maxProfit(vector<int> &prices)
{
	if(2 > prices.size()) return 0; 
	int currMin = prices[0], profit = 0;
	for(int i = 1; i < prices.size(); ++i)
	{
		if(prices[i] > currMin)
			profit = max(profit, prices[i]-currMin);
		else
			currMin = prices[i];
	}
	return profit;
}

//Best Time to Buy and Sell Stock II
int maxProfitII(vector<int> &prices)
{
	if(2 > prices.size()) return 0;
	int profit = 0;
	for(int i = 1; i < prices.size(); ++i)
	{
		int p = prices[i] - prices[i-1];
		profit += p > 0 ? p : 0;
	}
	return profit;
}

//Best Time to Buy and Sell Stock III
int maxProfitIII(vector<int> &prices)
{
	if(prices.size() < 2) return 0;
	vector<int> v(prices.size(), 0), w(prices.size(), 0);
	int mi = prices[0], ma = prices.back();
	for(int i = 1; i < v.size(); ++i)
	{
		if(prices[i] < mi)
			mi = prices[i];
		v[i] = max(v[i-1], prices[i] - mi);
	}
	for(int i = prices.size() - 2; i >= 0; --i)
	{
		if(prices[i] > ma)
			ma = prices[i];
		w[i] = max(w[i+1], ma - prices[i]);
	}
	int m = 0;
	for(int i = 0; i < prices.size(); ++i)
	{
		m = max(m, v[i] + w[i]);
	}
	return m;
}

//Balanced Binary Tree
// one-pass traverse
bool isBalanced2(TreeNode *root, int &height)
{
	height = 0;
	if(!root) return true;
	int lh = 0, rh = 0;
	if(!isBalanced2(root->left, lh)) return false;
	if(!isBalanced2(root->right, rh)) return false;
	height = (lh > rh ? lh : rh) + 1;
	return abs(lh - rh) <= 1;
}

bool isBalanced2(TreeNode *root)
{
	int height = 0;
	return isBalanced2(root, height);
}

//repetitive traverse, low efficiency
int height(TreeNode *root)
{
	if(!root) return 0;
	int l = height(root->left);
	int r = height(root->right);
	return (l > r ? l : r) + 1;
}

bool isBalanced(TreeNode *root)
{
	if(!root) return true;
	return isBalanced(root->left) && isBalanced(root->right) && abs(height(root->left)-height(root->right)) <= 1;
}


//Anagrams
//new version 31th OCt 2012
vector<string> anagrams(vector<string> &strs)
{
	vector<string> res;
	map<string, vector<int> > m;
	for(int i = 0; i < strs.size(); ++i)
	{
		string s(strs[i]);
		sort(s.begin(), s.end());
		m[s].push_back(i);
	}
	for(map<string, vector<int> >::iterator iter = m.begin(); iter != m.end(); ++iter)
	{
		if(iter->second.size() > 1)
		{
			for(int i = 0; i < iter->second.size(); ++i)
				res.push_back(strs[iter->second[i]]);
		}
	}
	return res;
}

//small judge is ok but Time Limit Exceeded in judge large.
vector<string> anagrams2(vector<string> &strs)
{
	vector<string> result;
	vector<string> tmp(strs);
	for(vector<string>::iterator iter = tmp.begin(); iter != tmp.end(); ++iter)
	{
		sort((*iter).begin(), (*iter).end());
	}
	vector<bool> flag(strs.size(), false);
	for(size_t i = 0; i < strs.size(); ++i)
	{
		if(flag[i])
			continue;
		for(size_t j = i + 1; j < strs.size(); ++j)
		{
			if(flag[j])
				continue;
			if(tmp[i] == tmp[j])
			{
				flag[i] = true;
				flag[j] = true;
			}
		}
	}
	for(size_t i = 0; i < strs.size(); ++i)
	{
		if(flag[i])
			result.push_back(strs[i]);
	}
	return result;
}


//Add Two Numbers
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
	ListNode *p = l1, *q = l2;
	ListNode *result = NULL;
	ListNode *pre = NULL;
	bool carry = false;
	while(p || q || carry)
	{
		int sum = 0;
		if(p)
		{
			sum += p->val;
			p = p->next;
		}
		if(q)
		{
			sum += q->val;
			q = q->next;
		}
		if(carry)
			++sum;
		carry = sum / 10;
		sum %= 10;
		ListNode *curr = new ListNode(sum);
		if(result == NULL)
		{
			result = curr;
			pre = result;
		}
		else
		{
			pre->next = curr;
			pre = curr;
		}
	}
	return result;
}

//Add Binary
string addBinary(string a, string b)
{
	bool carry = false;
	int sa = a.size(), sb = b.size();
	string result;
	for(int i = 0; i < sa || i < sb; ++i)
	{
		int temp = 0;
		if(i < sa && a[sa - 1 - i] == '1')
			++temp;
		if(i < sb && b[sb - 1 - i] == '1')
			++temp;
		if(carry)
			++temp;
		string t = (temp & 1) ? "1" : "0";
		result = t + result;
		carry = (temp & 2);
	}
	if(carry) result = "1" + result;
	return result;
}

//4Sum
//The problem is potentially solvable within O(n^2Logn).
//First sort all pairs based on their sum, then do a binary search.
//I’m just lazy here, and wrote a O(n^3) algorithm as follows.
vector<vector<int> > fourSum(vector<int> &num, int target)
{
	hash_map<int, vector<pair<int, int> > > m;
	hash_map<int, int> g;
	for(int i = 0; i < num.size(); ++i)
	{
		for(int j = i+1; j < num.size(); ++j)
		{
			m[num[i]+num[j]].push_back(make_pair(i, j));
		}
	}
	set<vector<int> > s;
	for(int i = 0; i < num.size(); ++i)
	{
		for(int j = i+1; j < num.size(); ++j)
		{
			int sum = target - num[i] - num[j];
			if(m.end() == m.find(sum))
				continue;
			for(int k = 0; k < m[sum].size(); ++k)
			{
				int a = m[sum][k].first, b = m[sum][k].second;
				if(a==i || b==i || a==j || b==j) continue;
				vector<int> v(4, 0);
				v[0] = num[i]; v[1] = num[j]; v[2] = num[a]; v[3] = num[b];
				sort(v.begin(), v.end());
				s.insert(v);
			}
		}
	}
	vector<vector<int> > res(s.size());
	copy(s.begin(), s.end(), res.begin());
	return res;
}

vector<vector<int> > fourSum2(vector<int> &num, int target)
{    //Runtime Error
	sort(num.begin(), num.end());
	vector<vector<int> > result;
	if(num.size() < 4) return result;
	int t;
	vector<int>::iterator ater = num.begin();
	while(ater + 3 != num.end())
	{
		vector<int>::iterator bter = ater + 1;
		while(bter + 2 != num.end())
		{
			vector<int>::iterator cter = bter + 1;
			vector<int>::iterator dter = num.end() - 1;
			while(cter < dter)
			{
				int sum = *ater + *bter + *cter + *dter;
				if(sum == target)
				{
					vector<int> tmpVec;
					tmpVec.push_back(*ater);
					tmpVec.push_back(*bter);
					tmpVec.push_back(*cter);
					tmpVec.push_back(*dter);
					result.push_back(tmpVec);

				}
				if(sum <= target)
				{
					t = *cter;
					while(cter < dter && *++cter == t);
				}
				if(sum >= target)
				{
					t = *dter;
					while(cter < dter && *--dter == t);
				}
			}
			t = *bter;
			while(bter + 2 != num.end() && *++bter == t);
		}
		t = *ater;
		while(ater + 3 != num.end() && *++ater == t);
	}
	return result;
}

//3Sum Closest
int threeSumClosest(vector<int> &num, int target)
{
	sort(num.begin(), num.end());
	int mindif = std::numeric_limits<int>::max();
	int closestSum = 0;
	vector<int>::iterator ater = num.begin();
	while(ater + 2 < num.end())
	{
		vector<int>::iterator bter = ater + 1, cter = num.end() - 1;
		while(bter < cter)
		{
			int temp = *ater + *bter + *cter;
			int dif = abs(temp - target);
			if(dif < mindif)
			{
				mindif = dif;
				closestSum = temp;
			}
			if(target < temp)
			{
				--cter;
			}
			else if(target > temp)
			{
				++bter;
			}
			else
				return target;
		}
		++ater;
	}
	return closestSum;
}


//3Sum
vector<vector<int> > threeSum(vector<int> &num)
{
	vector<vector<int> > result;
	sort(num.begin(), num.end());
	vector<int>::iterator ater = num.begin();
	while(ater + 2 < num.end())
	{
		vector<int>::iterator bter = ater + 1, cter = num.end() - 1;
		while(bter < cter)
		{
			int sum = *ater + *bter + *cter;

			if(0 == sum)
			{
				vector<int> temp;
				temp.push_back(*ater);
				temp.push_back(*bter);
				temp.push_back(*cter);
				result.push_back(temp);
			}
			if(0 >= sum)
			{
				int t = *bter;
				while(bter < cter && *++bter == t);
			}
			if(0 <= sum)
			{
				int t = *cter;
				while(bter < cter && *--cter == t);
			}
		}
		int t = *ater;
		while(ater + 2 < num.end() && *++ater == t);
	}
	return result;
}