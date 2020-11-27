'''
Author: taobo
Date: 2020-11-03 14:24:12
LastEditTime: 2020-11-03 14:42:47
'''
def longestCommonSubsequence_1(text1, text2):

    def dp(i, j):
        if i == -1 or j == -1:
            return 0
        if text1[i] == text2[j]:
            return dp(i - 1, j - 1) + 1
        else:
            return max(dp(i - 1, j), dp(i, j - 1))

    return dp(len(text1) - 1, len(text2) - 1)

def longestCommonSubsequence_2(text1, text2):
    m, n = len(text1), len(text2)
    memo = [[0] * n for _ in range(m)]

    def dp(i, j):
        if i == -1 or j == -1:
            return 0
        if memo[i][j] != 0:
            return memo[i][j]
        if text1[i] == text2[j]:
            ans = dp(i - 1, j - 1) + 1
        else:
            ans = max(dp(i - 1, j), dp(i, j - 1))
        memo[i][j] = ans
        return ans

    return dp(len(text1) - 1, len(text2) - 1)

def longestCommonSubsequence_3(text1, text2):
    m, n = len(text1), len(text2)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if text1[i - 1] == text2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    return dp[m][n]


str1 = "abcde"
str2 = "ace"
print(longestCommonSubsequence_3(str1, str2))