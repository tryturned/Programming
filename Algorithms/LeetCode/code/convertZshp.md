<!--
 * @Author: taobo
 * @Date: 2020-10-29 20:06:02
 * @LastEditTime: 2020-10-29 20:54:17
-->
# Z 字形变换
将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 `"LEETCODEISHIRING"` 行数为 3 时，排列如下：
```cpp
L   C   I   R
E T O E S I I G
E   D   H   N
```
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如： `"LCIRETOESIIGEDHN"。`  
# 方法一：按行排序
通过从左向右迭代字符串，我们可以轻松地确定字符位于 Z 字形图案中的哪一行。  

我们可以使用 `min(numRows,len(s))` 个列表来表示 Z 字形图案中的非空行。

从左到右迭代 s，将每个字符添加到合适的行。可以使用当前行和当前方向这两个变量对合适的行进行跟踪。

只有当我们向上移动到最上面的行或向下移动到最下面的行时，当前方向才会发生改变。代码实现如下：
```cpp
/**
 * @description: 
 * @param {s:字符串； numRows:给定行数}
 * @return 层序遍历序列
 * @src: https://leetcode-cn.com/problems/zigzag-conversion/
 */
string convert(string s, int numRows) {
  if (numRows == 1) return s;
  vector<string> rows(min(numRows, (int)s.size()));
  int p_row = 0;
  bool go_down = false;
  for (char& c: s) {
    rows[p_row] += c;
    if (p_row == 0 || p_row == numRows-1) go_down = !go_down;
    p_row += go_down ? 1 : -1;
  }
  string res;
  for (string& str: rows) {
    res += str;
  }
  return res;
}
```
# 方法二：按行访问
## 思路
按照与逐行读取 Z 字形图案相同的顺序访问字符串。
## 算法
首先访问 `行 0 `中的所有字符，接着访问 `行 1`，然后 `行 2`，依此类推...  

对于所有整数 `k`，  
- `行 0` 中的字符位于索引 `k(2⋅numRows−2)` 处;
- 行`numRows−1 `中的字符位于索引 `k(2⋅numRows−2)+numRows−1`处;
- 内部的 `行 i`中的字符位于索引 `k(2⋅numRows−2)+i` 以及 `(k+1)(2⋅numRows−2)−i `处;  

## 代码
```cpp
string convert(string s, int numRows) {

    if (numRows == 1) return s;

    string ret;
    int n = s.size();
    int cycleLen = 2 * numRows - 2;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j + i < n; j += cycleLen) {
            ret += s[j + i];
            if (i != 0 && i != numRows - 1 && j + cycleLen - i < n)
                ret += s[j + cycleLen - i];
        }
    }
    return ret;
}
```
