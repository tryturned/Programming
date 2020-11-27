/*
 * @Author: taobo
 * @Date: 2020-10-29 11:36:46
 * @LastEditTime: 2020-10-29 12:09:52
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* constructTree(vector<int>& nums, int root) {
      // [1,2,3,-1,5,-1,4], 基于层序遍历序列建树
      if (root >= nums.size() || nums[root] == -1) return nullptr;
      TreeNode* res = new TreeNode(nums[root]);
      res->left = constructTree(nums, 2*root+1);
      res->right = constructTree(nums, 2*root+2);
      return res;
    }
    void dfs(TreeNode* root ,vector<int>& res, int depth) {
        if (!root) return;
        if (depth == res.size()) res.push_back(root->val);
        depth++;
        dfs(root->right, res, depth);
        dfs(root->left, res, depth);
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        dfs(root, res, 0);
        return res;
    }
};

int main() {
  vector<int> nums = {1,5,6,7,8,9,10,4,8,-1,-1,-1,-1,8,9};
  Solution object;
  TreeNode* root = object.constructTree(nums, 0);
  vector<int> res = object.rightSideView(root);
  for (int& v: res) cout << v << ' ';
  cout << '\n';
  return 0;
}
