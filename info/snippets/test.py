def change_order(array):

    for i in range(len(array)):

        if i % 2 == 1:

            start = array[i][-1]
            end = array[i][0]

            array[i][0] = start
            array[i][-1] = end
    return array



# Example usage

array = [[(1, 2), (3, 4), (5, 6), (7, 8)],

         [(9, 10), (11, 12), (13, 14), (15, 16)],

         [(17, 18), (19, 20), (21, 22), (23, 24)]]



result = change_order(array)

print(result)