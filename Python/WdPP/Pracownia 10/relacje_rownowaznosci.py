from copy import deepcopy

#Calculating all set partitions 

def set_partition(inp_set):
    elements = list(inp_set)
    partitions = []
    if len(inp_set) == 0 or len(inp_set) == 1:
        return inp_set
    partitions.append([{elements[0]}])
    elements.remove(elements[0])
    while(len(elements) > 0):
        element = elements[0]
        elements.remove(element)
        updated_partitions = []
        for curr_partit in partitions:
            cloned = deepcopy(curr_partit)
            for subset in curr_partit:
                temp = deepcopy(curr_partit)
                temp.remove(subset)
                subset.add(element)
                temp.append(subset)
                updated_partitions.append(temp)
                curr_partit = deepcopy(cloned)
            curr_partit.append({element})
            updated_partitions.append(curr_partit)
        partitions = deepcopy(updated_partitions)
    return updated_partitions

print(len(set_partition({1,2,3,4,5,6,7})))
print(len(set_partition({1,2,3,4,5,6})))
print(len(set_partition({1,2,3,4,5})))
print(set_partition({1,2,3}))