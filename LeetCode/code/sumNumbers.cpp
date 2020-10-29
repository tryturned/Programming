/*
 * @Author: taobo
 * @Date: 2020-10-29 12:08:43
 * @LastEditTime: 2020-10-29 12:10:35
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
    int sumNumbers(TreeNode* root) {
        
    }
};

int main() {
  vector<int> nums = {1,5,6,7,8,9,10,4,8,-1,-1,-1,-1,8,9};
  Solution object;
  TreeNode* root = object.constructTree(nums, 0);
  int res = object.sumNumbers(root);
  cout << res << '\n';
  return 0;
}