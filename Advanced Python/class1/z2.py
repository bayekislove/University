import string

def is_palindrome(text) -> bool:
    text = text.translate(str.maketrans('', '', string.punctuation)).replace(' ', '').lower()
    p = 0
    k = len(text) - 1
    while p < k:
        if text[p] != text[k]:
            return False
        p += 1
        k -= 1
    return True

print(is_palindrome("Eine güldne, gute Tugend: Lüge nie!"))
print(is_palindrome('kajak'))
print(is_palindrome('人上人'))
print(is_palindrome('人上人b'))