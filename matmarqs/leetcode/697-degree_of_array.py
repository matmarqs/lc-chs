from typing import List

class Solution:
    def findShortestSubArray(self, nums: List[int]) -> int:
        map = {}
        max_freq = 0
        for i in range(len(nums)):
            if nums[i] not in map:
                map[nums[i]] = [i, 1, i]
            else:
                map[nums[i]][1] += 1
                map[nums[i]][2] = i
            if map[nums[i]][1] > max_freq:
                max_freq = map[nums[i]][1]
        min_len = 100000
        for num, map_num in map.items():
            if max_freq == map_num[1]:
                if map_num[2] - map_num[0] + 1 < min_len:
                    min_len = map_num[2] - map_num[0] + 1
        return min_len

sol = Solution()
sol.findShortestSubArray([1,2,2,3,1,4,2])
