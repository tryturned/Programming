'''
Author: taobo
Date: 2020-11-14 20:33:14
LastEditTime: 2020-11-14 20:45:29
link: https://leetcode-cn.com/problems/find-all-numbers-disappeared-in-an-array/
'''
def findDisappearedNumbers1(nums):
    """
    :type nums: List[int]
    :rtype: List[int]
    """
    hash_table = {}
    res = []
    for num in nums:
        hash_table[num] = 1
    for num in range(1, len(nums) + 1):
        if num not in hash_table:
            res.append(num)
    return res
        

def findDisappearedNumbers2(nums):
    """
    :type nums: List[int]
    :rtype: List[int]
    """
    for i in range(len(nums)):
        idx = abs(nums[i]) - 1
        if nums[idx] > 0:
            nums[idx] *= -1
    res = []
    for i in range(1, len(nums) + 1):
        if nums[i-1] > 0:
            res.append(i)
    return res

nums = [4,3,2,7,8,2,3,1]
print(findDisappearedNumbers1(nums))
print(findDisappearedNumbers2(nums))