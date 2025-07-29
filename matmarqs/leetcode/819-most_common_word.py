from typing import List

# beats 100%
class Solution:
    def mostCommonWord(self, paragraph: str, banned: List[str]) -> str:
        banned_set = set(banned)
        paragraph = "".join([ch if ch not in "!?',;." else " " for ch in paragraph])
        paragraph = paragraph.lower()
        dic = {}
        for w in paragraph.split():
            if w in dic:
                dic[w] += 1
            else:
                if w not in banned_set:
                    dic[w] = 1

        max = 0
        w = ""
        for word, count in dic.items():
            if count > max:
                max = count
                w = word

        return w

    def __init__(self):
        self.name = "Solution"

sol = Solution()
print(sol.mostCommonWord("Bob. hIt, baLl", ["bob", "hit"]))
