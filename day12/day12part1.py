def sum_integers_in_file(file_path):
    total_sum = 0
    with open(file_path, 'r') as file:
        for line in file:
            integers = re.findall(r'-?\d+', line)
            total_sum += sum(int(num) for num in integers)
    return total_sum

import re

file_path = 'input.txt'
total_sum = sum_integers_in_file(file_path)
print("Total sum of integers in the file:", total_sum)
