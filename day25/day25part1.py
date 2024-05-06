def next_code(current_code):
	multiplier_constant = 252533
	modulus_constant = 33554393
	return (current_code * multiplier_constant) % modulus_constant

def get_code_count(row, column):
	return sum(range(row + column - 1)) + column

first_code = 20151125
coordinates = (2947, 3029)

code_count = get_code_count(*coordinates)
current_code = first_code
for i in range(code_count - 1):
	current_code = next_code(current_code)
print(current_code)
