import np

a = open("aaa.csv")
b = a.read()
csvLines = b.split('\n')
for i in range(0, len(csvLines)):
    line = csvLines[i]
    line = line.split(',')
    for j in range(0, len(line)):
        if line[j] == '':
            line[j] = None
    csvLines[i] = line

print(csvLines)