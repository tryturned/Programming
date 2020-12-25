<!--
 * @Author: taobo
 * @Date: 2020-12-25 21:20:37
 * @LastEditTime: 2020-12-25 21:22:58
-->
* [题目](#题目)
* [题目描述](#题目描述)
* [思路分析](#思路分析)
* [优化](#优化)
* [AC代码](#ac代码)
* [重新定义状态转移](#重新定义状态转移)
* [ref](#ref)

## 题目
- [887. 鸡蛋掉落](https://leetcode-cn.com/problems/super-egg-drop/)
- [NC87	丢棋子问题](https://www.nowcoder.com/practice/d1418aaa147a4cb394c3c3efc4302266?tpId=117&tags=&title=&diffculty=0&judgeStatus=0&rp=1)  

## 题目描述
一座大楼有 `0 ~ N` 层，地面算作第 `0` 层，最高的一层为第 `N` 层。 已知棋子从第 `0` 层掉落肯定不会摔碎，但存在楼层 `F` (0 <= F <= N), 在这层楼将鸡蛋扔下去，鸡蛋恰好没摔碎（高于 `F` 的楼层都会碎，低于 `F` 的楼层都不会碎）。现在问**在最坏情况下**，**最少**要扔几次鸡蛋，才能确定这个楼层 `F`。

什么是 **在最坏情况下**？    

即在采取某种搜索策略解决问题时，一直到搜索区间穷尽时才得到结果。在该题目中举个例子来说就是，七层楼，一个鸡蛋，从第 0 层开始扔鸡蛋，一直到第七层才可以确定最终结果。因为在最坏情况下，此处会假设前六层鸡蛋不会碎。

什么是 **最少要扔几次鸡蛋**？   

上述举例是顺序扫描确定最终结果要比较 `N` 次 ，但如果采取二分法的方式进行扫描，这样比较次数可以降低至 `log N` 。同样可以采取五分法、十分法等等，这些皆是所采取的一种选择，最终我们需要返回这些选择所得到结果的最小值。

## 思路分析
由上面的分析可以看出，需要穷举扔鸡蛋的所有方式，显然该题是一个动态规划问题, 所以需要确定状态和选择是什么？

**「状态」很明显，就是当前拥有的鸡蛋数K和需要测试的楼层数N。** 随着测试的进行，鸡蛋个数可能减少，楼层的搜索范围会减小，这就是状态的变化。  

**「选择」其实就是去选择哪层楼扔鸡蛋。** 类似上面的线性扫描和二分思路，二分查找每次选择到楼层区间的中间去扔鸡蛋，而线性扫描选择一层层向上测试。不同的选择会造成状态的转移，此处应该包括 `1 ~ N` 的多种选择。  

因此该动态规划的基本思路就形成了：肯定是个二维的dp数组或者带有两个状态参数的dp函数来表示状态转移；外加一个 for 循环来遍历所有选择，伪代码如下所示 ：
```python
# 当前状态为 (K 个鸡蛋，N 层楼)
# 返回这个状态下的最优结果
def dp(K, N):
    if K == 1: return N
    if N == 0: return 0
    res = INF
    for 1 <= i <= N:
        # res = min(res, 这次在第 i 层楼扔鸡蛋)
        # 最坏情况下的最少扔鸡蛋次数
        res = min(res, 
                  max( 
                        dp(K - 1, i - 1), # 碎
                        dp(K, N - i)      # 没碎
                     ) + 1 # 在第 i 楼扔了一次
                 )
    return res
```
至此，然后添加一个备忘录消除重叠子问题，这道题就解决了：
```python
class Solution:
    def solve(self, n, k):
        # write code here
        memo = dict()

        def dp(n, k):
            if n == 0: return 0
            if k == 1: return n
            if (n, k) in memo:
                return memo[(n, k)]
            res = float('INF')
            for i in range(1, n + 1):
                res = min(res, max(dp(i - 1, k - 1), dp(n - i, k)) + 1)
            memo[(n, k)] = res
            return res

        return dp(n, k)
```
该解法的**时间复杂度就是子问题个数 × 函数本身的复杂度** = O(N * KN) = <img src="https://latex.codecogs.com/svg.latex?\\O(KN^2)">

然而现在仍旧无法通过 OJ，会报 `maximum recursion depth exceeded in comparison`，所以需要进一步的优化。

## 优化
显然对于该算法的状态转移方程如下所示：  

<img src="https://latex.codecogs.com/svg.latex?dp(K,N)=\min_{0<=i<=N}\{max\{dp(K-1,i-1),  dp(K, N-i)\} + 1\}">
  
  
根据 `dp(K, N)` 数组的定义（有 K 个鸡蛋面对 N 层楼，最少需要扔几次），很容易知道当 `K`, `N` 固定时，这两个函数随着 `i` 的增加:  
- `dp(K - 1, i - 1)` 随着 `i` 的增加应该是单调递增的;  
- `dp(K, N - i)` 随着 `i` 的增加应该是单调递减的;

<img src="https://codechina.csdn.net/qq_41345173/visualization/-/raw/master/image/demo.png" align='center'>

如上图所示，最终要求的应该是两条曲线的交点，即红色曲线的最小值。这样就可以使用二分的思想进行求解，最终可以通过代码如下所示。

## AC代码
### cpp
```cpp
class Solution {
  class hashfunc {
   public:
    size_t operator()(const pair<int, int>& i) const {
      return hash<int>()(i.first) ^ hash<int>()(i.second);
    }
  };
  unordered_map<pair<int, int>, int, hashfunc> eggmp;

 public:
  int superEggDrop(int K, int N) {
    if (K == 1) return N;
    if (N == 0) return 0;
    pair<int, int> kv = make_pair(K, N);
    if (eggmp.find(kv) != eggmp.end()) {
      return eggmp[kv];
    }
    int res = INT_MAX;
    int l = 1, r = N;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      int broken = superEggDrop(K - 1, mid - 1);
      int not_broken = superEggDrop(K, N - mid);
      if (broken >= not_broken) {
        r = mid - 1;
        res = min(res, broken + 1);
      } else {
        l = mid + 1;
        res = min(res, not_broken + 1);
      }
    }
    eggmp[kv] = res;
    return res;
  }
};
```
## 重新定义状态转移
**上面的 leetcode 可以通过，但牛客仍旧不可以，所以继续优化。没想到优化完了之后仍旧不能通过。**

`dp` 数组定义，**确定当前的鸡蛋个数和最多允许的扔鸡蛋次数，就知道能够确定 F 的最高楼层数**。具体来说是这个意思：
```bash
dp[k][m] = n
# 当前有 k 个鸡蛋，可以尝试扔 m 次鸡蛋
# 这个状态下，最坏情况下最多能确切测试一栋 n 层的楼

# 比如说 dp[1][7] = 7 表示：
# 现在有 1 个鸡蛋，允许你扔 7 次;
# 这个状态下最多给你 7 层楼，
# 使得你可以确定楼层 F 使得鸡蛋恰好摔不碎
# （一层一层线性探查嘛）
```
题目给出 `K` 鸡蛋，`N` 层楼，让你求**最坏情况下最少的测试次数 m** !  
`while` 循环结束的条件是 `dp[K][m] == N`，也就是**给你 K 个鸡蛋，测试 m 次，最坏情况下最多能测试 N 层楼**。

根据这个特点，可以写出下面的状态转移方程：
```c
dp[k][m] = dp[k][m - 1] + dp[k - 1][m - 1] + 1
```

`dp[k][m - 1]` 就是楼上的楼层数，因为鸡蛋个数 k 不变，也就是鸡蛋没碎，扔鸡蛋次数 `m` 减一；  

`dp[k - 1][m - 1]` 就是楼下的楼层数，因为鸡蛋个数 `k` 减一，也就是鸡蛋碎了，同时扔鸡蛋次数 `m` 减一。

如此，可写出如下代码：
```python
class Solution:
    def superEggDrop(self, K: int, N: int) -> int:
        # k 个蛋，扔 m 次，最坏情况下最多能确切测试一栋 n 层的楼
        dp = [[0 for _ in range(N+1)] for _ in range(K+1)]
        m = 0
        while dp[K][m] < N:
            m = m + 1
            for k in range(1, K+1):
                dp[k][m] = dp[k][m-1] + dp[k-1][m-1] + 1
        return m
```

## ref
[1. 常用数学符号的 LaTeX 表示方法](https://www.mohu.org/info/symbols/symbols.htm)

[2. 经典动态规划：高楼扔鸡蛋](https://mp.weixin.qq.com/s/xn4LjWfaKTPQeCXR0qDqZg)

[3. 经典动态规划：高楼扔鸡蛋（进阶）](https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/gao-lou-reng-ji-dan-jin-jie)

[4. 【鸡蛋掉落】5 行代码，从求扔几次变为求多少层楼 =附面试经历=](https://leetcode-cn.com/problems/super-egg-drop/solution/887-by-ikaruga/)

[5. 复工复产找工作？先来看看这道面试题：双蛋问题](https://www.bilibili.com/video/BV1KE41137PK)

[6. Welcome to EqnEditor Render](https://latex.codecogs.com/)