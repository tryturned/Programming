<!--
 * @Author: taobo
 * @Date: 2020-10-31 14:01:42
 * @LastEditTime: 2020-10-31 14:40:43
-->
# 题目
[652. 寻找重复的子树](https://leetcode-cn.com/problems/find-duplicate-subtrees/)
# 寻找重复的子树
给定一棵二叉树，返回所有重复的子树。对于同一类的重复子树，你只需要返回其中任意一棵的根结点即可。

两棵树重复是指它们具有相同的结构以及相同的结点值。  
**示例：**  
```
        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
```
**下面是两个重复的子树：**   
```
      2
     /
    4
```
和
```
4
```
**因此，你需要以列表的形式返回上述重复子树的根结点。**
# 思路
如果想知道某一个结点为根的子树是不是重复的，是否应该被加入结果列表中，你需要知道以下两点：
- **以当前结点为根的这棵二叉树（子树）长啥样？**
- **以其他节点为根的子树都长啥样？**  

## (1) 子树结构
关于第一点如何判断以当前结点为根的这棵二叉树（子树）长啥样？可以判断本题要使用「后序遍历」框架来解决：
```java
void traverse(TreeNode root) {
    traverse(root.left);
    traverse(root.right);
    /* 解法代码的位置 */
}
```  

由于二叉树的前序/中序/后序遍历结果可以描述二叉树的结构，所以，我们可以通过拼接字符串的方式把二叉树序列化，看下代码：
```java
String traverse(TreeNode root) {
    // 对于空节点，可以用一个特殊字符表示
    if (root == null) {
        return "#";
    }
    // 将左右子树序列化成字符串
    String left = traverse(root.left);
    String right = traverse(root.right);
    /* 后序遍历代码位置 */
    // 左右子树加上自己，就是以自己为根的二叉树序列化结果
    String subTree = left + "," + right + "," + root.val;
    return subTree;
}
```
**这样第一个问题就解决了，对于每个节点，递归函数中的 subTree 变量就可以描述以该节点为根的二叉树。**
## (2) 当前子树 VS 其他子树
现在的问题时如何确定扫描到的以当前结点为根的这棵二叉树序列化后的结果是第二次出现，如果是的话直接加入到结果集中即可，为排除出现次数大于 `2` 的子树，此处可以借助 `hashmap` 来解决问题。  

**这样，这道题就完全解决了，题目本身算不上难，但是思路拆解下来还是蛮复杂的，代码如下：**  
```cpp
class Solution {
public:
    string traverse(TreeNode* root, unordered_map<string, int>& memo, vector<TreeNode*>& res) {
        if (root == nullptr)  return "#";

        string left = traverse(root->left, memo, res);
        string right = traverse(root->right, memo, res);

        string subtree = left + ',' + right + ',' + to_string(root->val);

        int freq = 0;
        if (memo.count(subtree))  freq = memo[subtree];
        memo[subtree]++;
        if (freq == 1)  res.push_back(root);
        
        return subtree;
    }
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, int> memo;
        vector<TreeNode*> res;
        traverse(root, memo, res);
        return res;
    }
};
```