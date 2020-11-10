<!--
 * @Author: taobo
 * @Date: 2020-11-10 12:12:09
 * @LastEditTime: 2020-11-10 12:27:51
-->
# 题目
[0300. 最长上升子序列](https://leetcode-cn.com/problems/longest-increasing-subsequence/)  

[NC91. 最长递增子序列](https://www.nowcoder.com/practice/9cf027bf54714ad889d4f30ff0ae5481?tpId=117&&tqId=35013&rp=1&ru=/ta/job-code-high&qru=/ta/job-code-high/question-ranking)  

# 描述
Given an unsorted array of integers, find the length of longest increasing subsequence.
```
输入：
[2,1,5,3,6,4,8,9,7]

输出：
[1,3,4,8,9]
```
**这道题让我们求最长递增子串 Longest Increasing Subsequence 的长度，简称 LIS 的长度。**  

# 解决方法
## 1.1 动态规划法(brute force)

维护一个一维 dp 数组，其中 dp[i] 表示以 nums[i] 为结尾的最长递增子串的长度，对于每一个 nums[i]，从第一个数再搜索到i，如果发现某个数小于 nums[i]，更新 dp[i]，更新方法为 dp[i] = max(dp[i], dp[j] + 1)，即比较当前 dp[i] 的值和那个小于 num[i] 的数的 dp 值加1的大小，就这样不断的更新 dp 数组，到最后 dp 数组中最大的值就是我们要返回的 LIS 的长度，参见代码如下：
```cpp
int lengthOfLIS(vector<int>& nums) {
    vector<int> dp(nums.size(), 1);
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        res = max(res, dp[i]);
    }
    return res;
}
```
采取这种方法去解决牛客上的题目会超时。

## 1.2 二分优化
一种优化时间复杂度到 O(nlgn) 的解法，这里用到了二分查找法，所以才能加快运行时间哇。思路是先建立一个空的 dp 数组，然后开始遍历原数组，对于每一个遍历到的数字，用二分查找法在 dp 数组找第一个不小于它的数字，如果这个数字不存在，那么直接在 dp 数组后面加上遍历到的数字，如果存在，则将这个数字更新为当前遍历到的数字，最后返回 dp 数组的长度即可，**特别注意的是 dp 数组的值可能不是一个真实的 LIS**。参见代码如下：  

```cpp
void lcs(vector<int>& nums, vector<int>& res) {
    vector<int> dp, pos(nums.size(), 0);
    for (int i = 0; i < nums.size(); ++i) {
        int left = 0, right = dp.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (dp[mid] < nums[i]) left = mid + 1;
            else right = mid;
        }
        if (right >= dp.size()) {
            dp.push_back(nums[i]);
            pos[i] = dp.size();
        } else {
            dp[right] = nums[i];
            pos[i] = right+1;
        }
    }
    ///////////////////////
    int i, len = dp.size();
    res.resize(len, INT_MAX);
    for (i = nums.size()-1; i >= 0; i--) {
        if (pos[i] == len) {
            res[len-1] = min(res[len-1], nums[i]);
            len--;
        }
    }
}

vector<int> LIS(vector<int>& arr) {
    // write code here
    vector<int> res;
    lcs(arr, res);
    return res;
}
```
采取这种方法可以解决牛客上的题目。

## 1.3 lower_bound实现解法二
 C++ 中 STL 的 lower_bound 函数，lower_bound 返回数组中第一个不小于指定值的元素，跟上面的算法类似，还需要一个一维数组v，然后对于遍历到的 nums 中每一个元素，找其 lower_bound，如果没有 lower_bound，说明新元素比一维数组的尾元素还要大，直接添加到数组v中，跟解法二的思路相同了。如果有 lower_bound，说明新元素不是最大的，将其 lower_bound 替换为新元素，这个过程跟算法二的二分查找法的部分实现相同功能，最后也是返回数组v的长度。
 ```cpp
 class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> v;
        for (auto a : nums) {
            auto it = lower_bound(v.begin(), v.end(), a);
            if (it == v.end()) v.push_back(a);
            else *it = a;
        }　　　　　 　
        return v.size();
    }
};
```

# 参考
https://www.cnblogs.com/grandyang/p/4938187.html