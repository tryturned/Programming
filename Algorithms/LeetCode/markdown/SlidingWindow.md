<!--
 * @Author: taobo
 * @Date: 2020-11-08 10:59:44
 * @LastEditTime: 2020-11-08 16:59:37
-->
# 题目
[3. 无重复字符的最长子串](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters)  

[76. 最小覆盖子串](https://leetcode-cn.com/problems/minimum-window-substring)  

[239. 滑动窗口最大值](https://leetcode-cn.com/problems/sliding-window-maximum/)     

[567. 字符串的排列](https://leetcode-cn.com/problems/permutation-in-string)  

[438. 找到字符串中所有字母异位词](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string)  
# 滑动窗口技巧
这个算法技巧的思路非常简单，就是维护一个窗口，不断滑动，然后更新答案。大致逻辑如下：
```java
int left = 0, right = 0;

while (right < s.size()) {`
    // 增大窗口
    window.add(s[right]);
    right++;

    while (window needs shrink) {
        // 缩小窗口
        window.remove(s[left]);
        left++;
    }
}
```
# 滑动窗口算法框架
```cpp
/* 滑动窗口算法框架 */
void slidingWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;

    int left = 0, right = 0;
    int valid = 0; 
    while (right < s.size()) {
        // c 是将移入窗口的字符
        char c = s[right];
        // 右移窗口
        right++;
        // 进行窗口内数据的一系列更新
        ...

        /*** debug 输出的位置 ***/
        printf("window: [%d, %d)\n", left, right);
        /********************/

        // 判断左侧窗口是否要收缩
        while (window needs shrink) {
            // d 是将移出窗口的字符
            char d = s[left];
            // 左移窗口
            left++;
            // 进行窗口内数据的一系列更新
            ...
        }
    }
}
```
**其中两处 ... 表示的更新窗口数据的地方，直接往里面填就行了。**  
# 算法题
## [一、最小覆盖子串](https://leetcode-cn.com/problems/minimum-window-substring)
现在开始套模板，只需要思考以下四个问题：  
**1、当移动right扩大窗口，即加入字符时，应该更新哪些数据？**

**2、什么条件下，窗口应该暂停扩大，开始移动left缩小窗口？**

**3、当移动left缩小窗口，即移出字符时，应该更新哪些数据？**

**4、我们要的结果应该在扩大窗口时还是缩小窗口时进行更新？**  

如果一个字符进入窗口，应该增加window计数器；如果一个字符将移出窗口的时候，应该减少window计数器；当valid满足need时应该收缩窗口；应该在收缩窗口的时候更新最终结果。  

下面是完整代码：  
```cpp
string minWindow(string s, string t) {
    unordered_map<char, int> need, window;
    int left = 0, right = 0, n = s.size();
    int valid = 0;
    for (char& c: t) need[c]++;
    int st = 0, len = INT_MAX;
    while (right < n) {
        char c = s[right];
        right++;
        // window ...
        if (need.count(c)) {
            window[c]++;
            if (window[c] == need[c])
                valid++;
        }
        // shrink
        while (valid == need.size()) {
            if (right - left < len) {
                st = left;
                len = right - left;
            }
            char d = s[left];
            left++;
            if (need.count(d)) {
                if (window[d] == need[d]) {
                    valid--;
                }
                window[d]--;
            }
        }
    }
    return len == INT_MAX ? "" : s.substr(st, len);
}
```
## [二、字符串的排列](https://leetcode-cn.com/problems/permutation-in-string)   
对于这道题的解法代码，基本上和最小覆盖子串一模一样，只需要改变两个地方：

**1、本题移动 `l` 缩小窗口的时机是窗口大小等于 `s1.size()` 时，因为排列嘛，显然长度应该是一样的。**

**2、当发现 `valid == need.size()` 时，就说明窗口中就是一个合法的排列，所以立即返回 `true`。**
```cpp
bool checkInclusion(string s1, string s2) {
    int l = 0, r = 0, valid = 0;
    unordered_map<char, int> need, window;
    for (char& c: s1) need[c]++;

    while (r < s2.size()) {
        char c = s2[r++];
        if (need.count(c)) {
            window[c]++;
            if (window[c] == need[c])
                valid++;
        }

        while (r - l >= s1.size()) {
            if (valid == need.size())
                return true;
            char d = s2[l++];
            if (need.count(d)) {
                if (window[d] == need[d])
                    valid--;
                window[d]--;
            }
        }
    }
    return false;
}
```
## [三、找到字符串中所有字母异位词](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string)    
给定一个字符串 s 和一个非空字符串 p，找到 s 中所有是 p 的字母异位词的子串，返回这些子串的起始索引。  

字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20100。

说明：
- 字母异位词指字母相同，但排列不同的字符串。
- 不考虑答案输出的顺序。  

**和第三题一样，相当于，输入一个串S，一个串T，找到S中所有T的排列，返回它们的起始索引。**
```cpp
vector<int> findAnagrams(string s, string p) {
    int l = 0, r = 0, valid = 0;
    unordered_map<char, int> need, window;
    for (char c: p) need[c]++;
    vector<int> res;
    while (r < s.size()) {
        // put
        char c = s[r++];
        if (need.count(c)) {
            if (++window[c] == need[c])
                valid++;
        }
        // shrink
        while (r - l == p.size()) {
            if (valid == need.size())
                res.push_back(l);
            char d = s[l++];
            if (need.count(d)) {
                if (window[d]-- == need[d])
                    valid--;
            }
        }
    }
    return res;
}
```

## [四、无重复字符的最长子串](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters)
给定一个字符串，请你找出其中不含有重复字符的最长子串的长度。
示例 1:
```shell
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
```  

这就是变简单了，连 `need` 和 `valid` 都不需要，而且更新窗口内数据也只需要简单的更新计数器 `window` 即可。

当 `window[c]` 值大于 ` 1 ` 时，说明窗口中存在重复字符，不符合条件，就该移动  `left` 缩小窗口了嘛。
```cpp
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> window;
    int l = 0, r = 0, res = 0;
    while (r < s.size()) {
        char c = s[r++];
        window[c]++;
        // shrink
        while (window[c] > 1) {
            char d = s[l++];
            window[d]--;
        }
        res = max(res, r-l);
    }
    return res;
}
```
## [五、滑动窗口最大值](https://leetcode-cn.com/problems/sliding-window-maximum/)    
仍旧是简单的滑动窗口问题，而和框架模式所不同的是使用 `list` 或者 `deque` 替代 `hashmap` ，因为在这道题里面涉及到对入队顺序的要求，所以采取双端队列可以提高效率。

代码如下：
```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    list<int> window;
    int l = 0, r = 0;
    vector<int> res;
    while (r < nums.size()) {
        // push nums[r]
        int val = nums[r++];
        while (!window.empty() && window.back() < val)
            window.pop_back();
        window.push_back(val);
        // shrink
        while (r-l == k) {
            int d = nums[l++];
            res.push_back(window.front());
            if (d == window.front())
                window.pop_front();
        }
    }
    return res;
}
```