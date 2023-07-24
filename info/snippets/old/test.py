

array = [1,2]

print(len(array))
index = 0

for i in range(len(array)):
    index += 1
    if index == len(array):
        print(index)
        print("last element")