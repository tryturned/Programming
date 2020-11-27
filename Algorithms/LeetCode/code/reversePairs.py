'''
Author: taobo
Date: 2020-11-15 21:40:07
LastEditTime: 2020-11-15 21:40:51
link: https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/
'''
class Solution(object):
    def mymerge(self, nums, start, mid, end):
        backups = nums[mid + 1:end + 1]
        pre, nxt, p = mid, len(backups) - 1, end
        cur_count = 0
        while pre >= start and nxt >= 0:
            if nums[pre] > backups[nxt]:
                nums[p] = nums[pre]
                p, pre = p - 1, pre - 1
                cur_count += nxt + 1
            else:
                nums[p] = backups[nxt]
                p, nxt = p - 1, nxt - 1
        while pre >= start:
            nums[p] = nums[pre]
            p, pre = p - 1, pre - 1
        while nxt >= 0:
            nums[p] = backups[nxt]
            p, nxt = p - 1, nxt - 1
        return cur_count

    def mergesort(self, nums, start, end):
        if start < end:
            mid = (start + end) // 2
            L = self.mergesort(nums, start, mid)
            R = self.mergesort(nums, mid + 1, end)
            M = self.mymerge(nums, start, mid, end)
            return L + R + M
        return 0

    def reversePairs(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        return self.mergesort(nums, 0, len(nums) - 1)


obj = Solution()
data1 = [7, 5, 6, 4, 1, 1, 1, 1, 2, 5, 3, 2, 1, 7, 4, 2]
data = [7, 5, 6, 4]
print(obj.reversePairs(data1))
