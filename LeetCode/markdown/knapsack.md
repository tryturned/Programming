<!--
 * @Author: taobo
 * @Date: 2020-11-09 18:50:20
 * @LastEditTime: 2020-11-09 18:53:18
-->
# 0-1背包
<font style="font-family:宋体" size="4">给你一个可装载重量为 W 的背包和 N 个物品，每个物品有重量和价值两个属性。其中第 i 个物品的重量为 wt[i]，价值为 val[i]，现在让你用这个背包装物品，最多能装的价值是多少？</font>  
**这个题目中的物品不可以分割，要么装进包里，要么不装，不能说切成两块装一半。**  
## 第一步: 明确两点，「状态」和「选择」
- <font style="font-family:宋体" size="4">状态有两个，就是 **「背包的容量」** 和 **「可选择的物品」**。
- 选择就是 **「装进背包」** 或者 **「不装进背包」** </font>    

明白了状态和选择,只需要按照如下所示的框架来编码即可：
```shell
for 状态1 in 状态1的所有取值：
    for 状态2 in 状态2的所有取值：
        for ...
            dp[状态1][状态2][...] = 择优(选择1，选择2...)
```
## 第二步: 明确dp数组的定义
<font style="font-family:宋体" size="4" >「状态」有两个，也就是说我们需要一个二维dp数组，一维表示可选择的物品，一维表示背包的容量。  
<font color="red">
**dp[i][w]的定义如下：对于前i个物品，当前背包的容量为w，这种情况下可以装的最大价值是dp[i][w]。**</font>

比如说，如果 dp[3][5] = 6，其含义为：对于给定的一系列物品中，若只对前 3 个物品进行选择，当背包容量为 5 时，最多可以装下的价值为 6。  
</font>  
```shell
int dp[N+1][W+1]
dp[0][..] = 0
dp[..][0] = 0

for i in [1..N]:
    for w in [1..W]:
        dp[i][w] = max(
            把物品 i 装进背包,
            不把物品 i 装进背包
        )
return dp[N][W]
```
## 第三步: 根据「选择」，思考状态转移的逻辑
**简单说就是，上面伪码中「把物品i装进背包」和「不把物品i装进背包」怎么用代码体现出来呢？**  
<font style="font-family:宋体" size="4" color="red">  
- **如果你没有把这第i个物品装入背包**，那么很显然，最大价值dp[i][w]应该等于dp[i-1][w]。你不装嘛，那就继承之前的结果。
- **如果你把这第i个物品装入了背包**，那么dp[i][w]应该等于dp[i-1][w-wt[i-1]] + val[i-1]。
</font>
## 最后一步: 把伪码翻译成代码，处理一些边界情况。  

```cpp
int knapsack(int W, int N, vector<int>& wt, vector<int>& val) {
    // vector 全填入 0，base case 已初始化
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= N; i++) {
        for (int w = 1; w <= W; w++) {
            if (w - wt[i-1] < 0) {
                // 当前背包容量装不下，只能选择不装入背包
                dp[i][w] = dp[i - 1][w];
            } else {
                // 装入或者不装入背包，择优
                dp[i][w] = max(dp[i - 1][w - wt[i-1]] + val[i-1], 
                               dp[i - 1][w]);
            }
        }
    }

    return dp[N][W];
}
```

# 子集背包
[源leetcode 416](https://leetcode-cn.com/problems/partition-equal-subset-sum/)  
<font style="font-family:宋体" size="4">
给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。  
```c
输入: [1, 5, 11, 5]
输出: true

解释: 数组可以分割成 [1, 5, 5] 和 [11].
```
那么对于这个问题，我们可以先对集合求和，得出 sum，把问题转化为背包问题：  
**给一个可装载重量为 sum / 2 的背包和 N 个物品，每个物品的重量为 nums[i]。现在让你装物品，是否存在一种装法，能够恰好将背包装满？**  
## 1. 明确两点，「状态」和「选择」
<font color=red>状态就是「背包的容量」和「可选择的物品」，选择就是「装进背包」或者「不装进背包」。</font>
## 2. 明确 dp 数组的定义
**dp[i][j] = x 表示，对于前 i 个物品，当前背包的容量为 j 时，若 x 为 true，则说明可以恰好将背包装满，若 x 为 false，则说明不能恰好将背包装满。**  

比如说，如果 dp[4][9] = true，其含义为：对于容量为 9 的背包，若只是用前 4 个物品，可以有一种方法把背包恰好装满。  

根据这个定义，我们想求的最终答案就是 dp[N][sum/2]，base case 就是 `dp[..][0] = true 和 dp[0][..] = false`，因为背包没有空间的时候，就相当于装满了，而当没有物品可选择的时候，肯定没办法装满背包。
## 3. 根据「选择」，思考状态转移的逻辑
<font color=red> **如果不把 nums[i] 算入子集，** 或者说你不把这第 i 个物品装入背包，那么是否能够恰好装满背包，取决于上一个状态 `dp[i-1][j]`，继承之前的结果。  
**如果把 nums[i] 算入子集，** 或者说你把这第 i 个物品装入了背包，那么是否能够恰好装满背包，取决于状态 `dp[i-1][j-nums[i-1]]`。</font>
## 4. 把伪码翻译成代码，处理一些边界情况
```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        if (nums.empty()) return false;
        int n = nums.size(), sum = 0;
        for (int& v:nums) sum += v;
        if (sum % 2) return false;
        sum /= 2;
        vector<vector<bool>> dp(n+1, vector<bool>(sum+1, false));
        // base case
        for (int i = 0; i <= n; ++i) dp[i][0] = true;
        // 状态转移
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= sum; ++j) {
                if (j - nums[i-1] < 0) dp[i][j] = dp[i-1][j];
                else dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]];
            }
        }
        return dp[n][sum];
    }
};
```
## 4. 状态压缩
```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        if (nums.empty()) return false;
        int n = nums.size(), sum = 0;
        for (int& v:nums) sum += v;
        if (sum % 2) return false;
        sum /= 2;
        vector<bool> dp(sum+1, false);
        // base case
        dp[0] = true;
        // 状态转移
        for (int i = 1; i <= n; ++i) {
            for (int j = sum; j >= 0; --j) {
                if (j - nums[i-1] >= 0)
                    dp[j] = dp[j] || dp[j-nums[i-1]];
            }
        }
        return dp[sum];
    }
};
```
    
    
**<font color=reed>至此，子集切割的问题就完全解决了，时间复杂度 O(n\*sum)，空间复杂度 O(sum)</font>**  

# 完全背包
[源leetcode 518](https://leetcode-cn.com/problems/coin-change-2/)  
<font style="font-family:宋体" size="4">
给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。 
```
输入: amount = 5, coins = [1, 2, 5]
输出: 4
解释: 有四种方式可以凑成总金额:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
```  
PS：至于 Coin Change 1，[源leetcode 322](https://leetcode-cn.com/problems/coin-change/)  。
## 1. 明确两点，「状态」和「选择」
**状态有两个，就是「背包的容量」和「可选择的物品」，选择就是「装进背包」或者「不装进背包」**  
## 2. 明确 dp 数组的定义
`dp[i][j] `的定义如下：
若只使用前 i 个物品，当背包容量为 j 时，有 `dp[i][j]` 种方法可以装满背包。  
base case 为` dp[0][..] = 0， dp[..][0] = 1`。因为如果不使用任何硬币面值，就无法凑出任何金额；如果凑出的目标金额为 0，那么“无为而治”就是唯一的一种凑法。  

**我们最终想得到的答案就是 dp[N][amount]，其中 N 为 coins 数组的大小.**
## 3. 根据「选择」，思考状态转移的逻辑
<font color=red size=3>注意，我们这个问题的特殊点在于==物品的数量是无限的==，所以这里和之前写的背包问题文章有所不同。</font>    

**如果不把这第 i 个物品装入背包**，也就是说你不使用 coins[i] 这个面值的硬币，那么凑出面额 j 的方法数 dp[i][j] 应该等于 dp[i-1][j]，继承之前的结果。  

**如果把这第 i 个物品装入了背包**，也就是说你使用 coins[i] 这个面值的硬币，那么 dp[i][j] 应该等于 `dp[i][j-coins[i-1]]`。  
<font color=red size=3>上面之所以当选择装入第 i 个物品时为 `dp[i][j-coins[i-1]]` 而不是 `dp[i-1][j-coins[i-1]]` 是因为考虑到当前币种数目无限所致</font>  

**综上就是两种选择，而我们想求的 `dp[i][j]` 是「共有多少种凑法」，所以 `dp[i][j]` 的值应该是以上两种选择的结果之和：**
```cpp
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= amount; j++) {
        if (j - coins[i-1] >= 0)
            dp[i][j] = dp[i - 1][j] 
                     + dp[i][j-coins[i-1]];
return dp[N][W]
```
## 4. 把伪码翻译成代码，处理一些边界情况  
```cpp
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size(), w = amount;
        vector<vector<int>> dp(n+1, vector<int>(w+1, 0));
        for (int i = 0; i <= n; ++i) dp[i][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= w; ++j) {
                if (j >= coins[i-1]) {
                    dp[i][j] = dp[i-1][j] + dp[i][j-coins[i-1]];
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[n][w];
    }
};
```
## 5. 状态压缩
```cpp
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size(), w = amount;
        vector<int> dp(w+1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= w; ++j) {
                if (j >= coins[i-1]) {
                    dp[j] = dp[j] + dp[j-coins[i-1]];
                }
            }
        }
        return dp[w];
    }
};
```  
**将二维 dp 数组压缩为一维，时间复杂度 O(N\*amount)，空间复杂度 O(amount)。**