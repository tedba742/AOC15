def sum_integers_in_file(file_path):
    total_sum = 0
    with open(file_path, 'r') as file:
        for line in file:
            # Extract all integer substrings using regular expression
            integers = re.findall(r'-?\d+', line)
            # Convert each integer substring to an integer and sum them up
            total_sum += sum(int(num) for num in integers)
    return total_sum

# Example usage:
import re

file_path = 'input.txt'  # Replace 'input.txt' with the path to your input file
total_sum = sum_integers_in_file(file_path)
print("Total sum of integers in the file:", total_sum)
