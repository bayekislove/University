import random

limit = 10

print(limit)
list_len = 0
i = 0
while i < limit:
    op_type = random.sample(['I', 'D', 'S'], 1)[0]
    if op_type == 'I':
        idx = random.randint(0, list_len)
        print(f"I {idx} {i}")
        list_len += 1
    if op_type == 'D':
        if list_len == 0:
            continue
        idx = random.randint(1, list_len)
        print(f"D {idx}")
        list_len -= 1
    if op_type == 'S':
        if list_len == 0:
            continue
        idx1 = random.randint(1, list_len)
        idx2 = random.randint(1, list_len)
        if idx1 > idx2:
            continue
        print(f"S {idx1} {idx2}")
    i += 1
