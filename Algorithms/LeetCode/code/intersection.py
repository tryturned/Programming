def intersection(nums1, nums2):
    """
    :type nums1: List[int]
    :type nums2: List[int]
    :rtype: List[int]
    """
    nums1.sort()
    nums2.sort()
    len1, len2 = len(nums1), len(nums2)
    index1 = index2 = 0
    res = list()
    while index1 < len1 and index2 < len2:
        if nums1[index1] == nums2[index2]:
            if not res or res[-1] != nums1[index1]:
                res.append(nums1[index1])
            index1 += 1
            index2 += 1
        elif nums1[index1] < nums2[index2]:
            index1 += 1
        else:
            index2 += 1
    return res


arr1 = [1, 2, 2, 1, 3, 4]
arr2 = [2, 2, 4, 3]
print(intersection(arr1, arr2))
