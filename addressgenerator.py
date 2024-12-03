import random

def generate_addresses():
		# Prompt user for the number of addresses
		try:
				num_addresses = int(input("Enter the number of addresses to generate: "))
				if num_addresses <= 0:
						raise ValueError("Number of addresses must be greater than zero.")
		except ValueError as e:
				print(f"Invalid input: {e}")
				return

		# Prompt user for the output file name
		output_file = input("Enter the name of the output file (e.g., addresses.txt): ")

		# Set the seed for Mersenne Twister random generator
		random.seed()

		# Generate random addresses
		address_range = 65536  # 16-bit address range (0x0000 to 0xFFFF)
		with open(output_file, "w") as file:
				for _ in range(num_addresses):
						address = random.randint(0, address_range - 1)
						file.write(f"x{address:04X}\n")  # Write addresses in hexadecimal format

		print(f"File '{output_file}' generated with {num_addresses} addresses.")

if __name__ == "__main__":
	print('RUNNING ADDRESS GENERATOR SCRIPT:\n')
	generate_addresses()
	print('TERMINATING PROCESS')