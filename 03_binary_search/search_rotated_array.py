# https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/

def search(self, nums: List[int], target: int) -> bool:
    l_idx = 0
    r_idx = len(nums) - 1
    mid = 0
    while l_idx < r_idx:
        mid = int((l_idx + r_idx) / 2)
        if nums[mid] == target: 
            return True;
        if nums[mid] < nums[-1]:  # 分割点右边有序
            if target <= nums[r_idx] and target > nums[mid]:
                l_idx = mid + 1;
            else:
                r_idx = mid - 1;
        elif nums[mid] > nums[-1]: # 分割点左边有序
            if target >= nums[l_idx] and target < nums[mid]:
                r_idx = mid - 1;
            else:
                l_idx = mid + 1;
        else: # nums[mid] == nums[-1] # 无法判断分割点左右区间的单调性
            if nums[r_idx] == target: 
                return True
            else: r_idx -= 1;
    return nums[l_idx] == target   