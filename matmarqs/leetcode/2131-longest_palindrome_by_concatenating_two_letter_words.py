from typing import List

###################################################

def rev(s):
    return s[1] + s[0]

def two_letters(s):
    return s[0] != s[1]

class Solution:
    def longestPalindrome(self, words: List[str]) -> int:
        dic = {}
        for w in words:
            dic[w] = dic.get(w, 0) + 1
        num_singl = 0
        num_pairs = 0
        for k in dic.keys():
            if two_letters(k):
                num_pairs += min(dic.get(k, 0), dic.get(rev(k), 0))
            else:
                num_pairs += 2 * (dic.get(k, 0) // 2)
                num_singl += dic.get(k, 0) % 2
        num_pairs = num_pairs // 2
        len = 2 * (2 * num_pairs + (1 if num_singl else 0))
        return len
