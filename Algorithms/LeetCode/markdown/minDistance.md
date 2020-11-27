<!--
 * @Author: taobo
 * @Date: 2020-11-01 15:18:00
 * @LastEditTime: 2020-11-01 16:43:18
-->
# 题目
[0072. 编辑距离](https://leetcode-cn.com/problems/edit-distance/)  
**给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。**  
你可以对一个单词进行如下三种操作：

- 插入一个字符
- 删除一个字符
- 替换一个字符

**示例：**  
```
输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')
```
# 思路
**解决两个字符串的动态规划问题，一般都是用两个指针` i,j `分别指向两个字符串的最后，然后一步步往前走，缩小问题的规模。**  

设两个字符串分别为` "rad"` 和 `"apple"`，为了把` s1 `变成` s2`，通常操作是从后向前扫描两个字符串，采取插入、替换、删除的策略使得最终两个字符串相等。  

显然base case  是` i `走完` s1 `或 `j `走完` s2`，可以直接返回另一个字符串剩下的长度。  
下面是 `Python` 代码关于上述描述的递归实现，简单易懂：
```python
def minDistance(word1, word2):
    def dp(i, j):
        # base case
        if i == -1: return j + 1
        if j == -1: return i + 1
        # dp
        if word1[i] == word2[j]:
            return dp(i - 1, j - 1)
        else:
            return min(
                dp(i, j - 1),  # insert
                dp(i - 1, j),  # delete
                dp(i - 1, j - 1)  # replace
            ) + 1

    return dp(len(word1) - 1, len(word2) - 1)
```
但显然上述实现是一个暴力回溯过程，存在大量的重叠子问题，所以需要进一步的优化。  

# 动态规划优化
## 基于备忘录进行优化(通过)
```python
def minDistance2(word1, word2):
    memo = dict()

    def dp(i, j):
        if (i, j) in memo: return memo[(i, j)]

        # base case
        if i == -1: return j + 1
        if j == -1: return i + 1
        # dp
        if word1[i] == word2[j]:
            memo[(i, j)] = dp(i - 1, j - 1)
        else:
            memo[(i, j)] = min(
                dp(i, j - 1),  # insert
                dp(i - 1, j),  # delete
                dp(i - 1, j - 1)  # replace
            ) + 1
        return memo[(i, j)]

    return dp(len(word1) - 1, len(word2) - 1)
```
## DP table 的解法(通过)
首先明确 dp 数组的含义，dp 数组是一个二维数组，长这样：  
![Bw0xIK.md.png](https://s1.ax1x.com/2020/11/01/Bw0xIK.md.png)   
```python
def minDistance(word1, word2):
    len1 = len(word1)
    len2 = len(word2)
    # initialize
    dp = [[0 for i in range(len2 + 1)] for j in range(len1 + 1)]
    for i in range(1, len1 + 1):
        dp[i][0] = dp[i - 1][0] + 1
    for j in range(1, len2 + 1):
        dp[0][j] = dp[0][j - 1] + 1
    # dp
    for i in range(1, len1 + 1):
        for j in range(1, len2 + 1):
            if word1[i - 1] == word2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                dp[i][j] = min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]) + 1
    return dp[len1][len2]
```