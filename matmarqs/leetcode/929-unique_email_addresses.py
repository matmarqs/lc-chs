from typing import List

def forward_email(email: str):
    split = email.split('@')
    domain = split[1]
    name = split[0]
    name = name.split('+')[0]
    name = name.replace('.', '')
    return name + "@" + domain

class Solution:
    def numUniqueEmails(self, emails: List[str]) -> int:
        diff_emails = set()
        for em in emails:
            diff_emails.add(forward_email(em))
        return len(diff_emails)
