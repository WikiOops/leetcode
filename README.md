leetcode
========

My personal understanding of leetcode

=====================================
建树和序列化树

initialize serialized tree
   1
  / \
 2   3
    /
   4
    \
     5
The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}".
The above binary tree is pre_order serialized as "{1,2,#,#,3,4,#,5}".

1.1可以这么建树：
int num[] = {1,2,3,e,e,4,e,e,5};
vector<int> vec(num, num+sizeof(num)/sizeof(int));
TreeNode *root = initializeTree<TreeNode>(vec);

1.2如果你的编译器支持initializor list(vs 2012至今不支持，但是gcc在4.4就支持了)，那就可以这么写：
vector<int> vec = {1,2,3,e,e,4,e,e,5};
TreeNode *root = initializeTree<TreeNode>(vec);

1.3你也可以通过pre_order的序列化来建树。
vector<int> vec = {1,2,#,#,3,4,#,5};
TreeNode *root = initializeTree<TreeNode>(vec);

1.4可以用serialization和serialization_preorder来序列化树。
vector<int> res;
serialization<TreeNode>(res, root);
