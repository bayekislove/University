def if_possible(s1, s2):
    used_s1 = [0,1,2,3,4,5,6,7,8,9]
    used_s2 = [0,1,2,3,4,5,6,7,8,9]
    if len(s1) == len(s2):
        for s in range(len(s1)):
            used_s1[int(s1[s])] += 1
            used_s2[int(s2[s])] += 1
    elif len(s1) < len(s2):
        for i in range(len(s1)):
            used_s1[int(s1[i])] += 1
            used_s2[int(s2[i])] += 1
        for j in range(len(s1),len(s2)):
            used_s2[int(s2[j])] += 1
    else:
        for i in range(len(s2)):
            used_s1[int(s1[i])] += 1
            used_s2[int(s2[i])] += 1
        for j in range(len(s2), len(s1)):
            used_s1[int(s1[j])] += 1
    for i in range(10):
        if (used_s1[i] > i and used_s2[i] == i) or (used_s1[i] == i and used_s2[i] > i):
            return False
    return True

def if_num_isright(n, num):
        for multiplier in range(1, n):
            str1 = str(num)
            str2 = str(num * (multiplier+1))
            if(if_possible(str1, str2) == False):
                return False
        return True

def final(n):
    number = 1
    while True:
        if if_num_isright(n, number) == True:
            return number
        number += 1

print(final(6))

