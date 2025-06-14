# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values

def complex_number_list(real: float, imaginary: float) -> list:
    """
    :param real: the real part of the complex number z
    :param imaginary: the imaginary part of the complex number z
    :return: the complex number z as a list [real, imaginary]
    """
    return [real, imaginary]  # Return a complex number as a list


def get_real_part_list(complex_number: list) -> float:
    """
    :param complex_number: complex number in list form
    :return: the real part of the complex number
    """
    return complex_number[0]  # Access the first element as the real part


def get_imaginary_part_list(complex_number: list) -> float:
    """
    :param complex_number: complex number in list form
    :return: the imaginary part of the complex number
    """
    return complex_number[1]  # Access the second element as the imaginary part


def set_real_part_list(complex_number: list, real: float) -> list:
    """
    :param real: new real part to set
    :param complex_number: complex number in list form
    :return: modified complex number with updated real part
    """
    complex_number[0] = real  # Set the first element as the new real part
    return complex_number


def set_imaginary_part_list(complex_number: list, imaginary: float) -> list:
    """
    :param imaginary: new imaginary part to set
    :param complex_number: complex number in list form
    :return: modified complex number with updated imaginary part
    """
    complex_number[1] = imaginary  # Set the second element as the new imaginary part
    return complex_number


def complex_to_str_list(complex_number: list) -> str:
    """
    :param complex_number: complex number in list form
    :return: string representation of the complex number
    """
    real = get_real_part_list(complex_number)  # Get real part
    imaginary = get_imaginary_part_list(complex_number)  # Get imaginary part
    # Format as a string with "+" or "-" based on the imaginary part
    return f"{real} {'-' if imaginary < 0 else '+'} {abs(imaginary)}i"


# Functions for working with complex numbers -- dict representation

def complex_number_dict(real: float, imaginary: float) -> dict:
    """
    :param real: the real part of the complex number z
    :param imaginary: the imaginary part of the complex number z
    :return: complex number represented as a dictionary
    """
    return {'real': real, 'imaginary': imaginary}  # Represent as a dictionary


def get_real_part_dict(complex_number: dict) -> float:
    """
    :param complex_number: complex number as dictionary
    :return: real part of the complex number
    """
    return complex_number['real']  # Access 'real' key


def get_imaginary_part_dict(complex_number: dict) -> float:
    """
    :param complex_number: complex number as dictionary
    :return: imaginary part of the complex number
    """
    return complex_number['imaginary']  # Access 'imaginary' key


def set_real_part_dict(complex_number: dict, real: float) -> dict:
    """
    :param real: new real part to set
    :param complex_number: complex number as dictionary
    :return: updated complex number with new real part
    """
    complex_number['real'] = real  # Update the 'real' key
    return complex_number

def set_imaginary_part_dict(complex_number: dict, imaginary: float) -> dict:
    """
    :param imaginary: new imaginary part to set
    :param complex_number: complex number as dictionary
    :return: updated complex number with new imaginary part
    """
    complex_number['imaginary'] = imaginary  # Update the 'imaginary' key
    return complex_number


def complex_to_str_dict(complex_number: dict) -> str:
    """
    :param complex_number: complex number as dictionary
    :return: string representation of the complex number
    """
    real = get_real_part_dict(complex_number)  # Get real part
    imaginary = get_imaginary_part_dict(complex_number)  # Get imaginary part
    return f"{real} {'-' if imaginary < 0 else '+'} {abs(imaginary)}i"


# Function to check if a complex number (represented as a list or dict) is distinct in the subarray
def is_distinct_in_subarray(subarray, number) -> bool:
    """
    :param subarray: the sequence of numbers
    :param number: the number to be searched
    :return: True if the number is not the current sequence, false otherwise
    """
    if isinstance(number, list):
        # Compare based on real and imaginary parts for list representation
        for existing_number in subarray:
            if existing_number[0] == number[0] and existing_number[1] == number[1]:  # Compare real and imaginary parts
                return False
    elif isinstance(number, dict):
        # Compare based on real and imaginary parts for dict representation
        for existing_number in subarray:
            if existing_number['real'] == number['real'] and existing_number['imaginary'] == number['imaginary']:
                return False
    return True


# Function to find the longest distinct subarray for complex numbers
def longest_distinct_subarray(array) -> list:
    """
    :param array: the list of complex numbers
    :return: the longest distinct subarray for complex numbers
    """
    current_subarray = []  # Empty subarray
    max_subarray = []  # To store the longest found subarray

    for number in array:
        if is_distinct_in_subarray(current_subarray, number):  # Add to subarray if distinct
            current_subarray.append(number)
        else:
            if len(current_subarray) > len(max_subarray):
                max_subarray = current_subarray  # Update max if current is longer
            # Restart subarray from the duplicate
            current_subarray = [number]

    # Final check for max subarray length
    if len(current_subarray) > len(max_subarray):
        max_subarray = current_subarray

    return max_subarray


# Function for finding the longest increasing subsequence based on real part of complex numbers
def longest_increasing_subsequence_real(list_numbers):
    if not list_numbers:
        return []

    dp = [1] * len(list_numbers)  # Initialize dp with 1 for each element (We initialize each element of dp to 1 because every element is an increasing subsequence by itself)
    previous = [-1] * len(list_numbers)  # To reconstruct LIS (an array that keeps track of the index of the previous element in the LIS that ends at position i)

    for i in range(1, len(list_numbers)):
        for j in range(i):
            real_i = get_real_part_list(list_numbers[i]) if isinstance(list_numbers[i], list) else get_real_part_dict(list_numbers[i])
            real_j = get_real_part_list(list_numbers[j]) if isinstance(list_numbers[j], list) else get_real_part_dict(list_numbers[j])

            if real_i > real_j and dp[i] < dp[j] + 1:
               # dp[i] < dp[j] + 1 ensures that if list_numbers[i] can be appended to the subsequence ending at list_numbers[j], then the length of the subsequence at index i is updated.
               # dp[i] stores the length of the LIS ending at i. If dp[i] is less than dp[j] + 1, it means we can extend the LIS by adding list_numbers[i] to the subsequence that ends at list_numbers[j].
               # The +1 accounts for including the number list_numbers[i] in the sequence

                dp[i] = dp[j] + 1  # Update LIS length
                previous[i] = j  # Update previous index


    max_index = dp.index(max(dp))  # Find LIS length index
                                   # dp is a list where each element at index i stores the length of the longest increasing subsequence ending at position i in array.
                                   # max(dp) finds the maximum length of any increasing subsequence in the list.
                                   # dp.index finds the first occurrence of this maximum value in dp and returns its index, max_index.
                                   # max_index points to the position in array where the longest increasing subsequence ends.
    li_sequence = []

    while max_index != -1:  # Reconstruct LIS
        li_sequence.append(list_numbers[max_index])
        max_index = previous[max_index]

    return li_sequence[::-1]  # Return in correct order (slice notation for reversing a list / The first colon (:) means "take the entire list," and the -1 indicates to step backwards, effectively reversing the list)

def test_longest_distinct_subarray():
    # Test with complex numbers in list form
    complex_list = [
        complex_number_list(1, 2),  # 1 + 2i
        complex_number_list(2, 3),  # 2 + 3i
        complex_number_list(1, 2),  # 1 + 2i (duplicate)
        complex_number_list(3, 1),  # 3 + 1i
        complex_number_list(5, 5),  # 5 + 5i
        complex_number_list(4, 6)   # 4 + 6i
    ]
    expected_result_list = [
        complex_number_list(1, 2), complex_number_list(3, 1), complex_number_list(5, 5), complex_number_list(4, 6)
    ]
    result = longest_distinct_subarray(complex_list)
    assert result == expected_result_list, f"Expected {expected_result_list}, but got {result}"

    # Test with complex numbers in dict form
    complex_dict = [
        complex_number_dict(1, 2),  # 1 + 2i
        complex_number_dict(2, 3),  # 2 + 3i
        complex_number_dict(1, 2),  # 1 + 2i (duplicate)
        complex_number_dict(3, 1),  # 3 + 1i
        complex_number_dict(5, 5),  # 5 + 5i
        complex_number_dict(4, 6)   # 4 + 6i
    ]
    expected_result_dict = [
        complex_number_dict(1, 2), complex_number_dict(3, 1), complex_number_dict(5, 5), complex_number_dict(4, 6)
    ]
    result = longest_distinct_subarray(complex_dict)
    assert result == expected_result_dict, f"Expected {expected_result_dict}, but got {result}"

# Test function for longest_increasing_subsequence_real
def test_longest_increasing_subsequence_real():
    # Test with complex numbers in list form
    complex_list = [
        complex_number_list(1, 2),  # 1 + 2i
        complex_number_list(2, 3),  # 2 + 3i
        complex_number_list(3, 4),  # 3 + 4i
        complex_number_list(4, 5),  # 4 + 5i
        complex_number_list(1, 2),  # 1 + 2i (will not affect LIS of real parts)
        complex_number_list(5, 6)   # 5 + 6i
    ]
    expected_result_list = [
        complex_number_list(1, 2), complex_number_list(2, 3), complex_number_list(3, 4), complex_number_list(4, 5), complex_number_list(5, 6)
    ]
    result = longest_increasing_subsequence_real(complex_list)
    assert result == expected_result_list, f"Expected {expected_result_list}, but got {result}"

    # Test with complex numbers in dict form
    complex_dict = [
        complex_number_dict(1, 2),  # 1 + 2i
        complex_number_dict(2, 3),  # 2 + 3i
        complex_number_dict(3, 4),  # 3 + 4i
        complex_number_dict(4, 5),  # 4 + 5i
        complex_number_dict(1, 2),  # 1 + 2i (will not affect LIS of real parts)
        complex_number_dict(5, 6)   # 5 + 6i
    ]
    expected_result_dict = [
        complex_number_dict(1, 2), complex_number_dict(2, 3), complex_number_dict(3, 4), complex_number_dict(4, 5), complex_number_dict(5, 6)
    ]
    result = longest_increasing_subsequence_real(complex_dict)
    assert result == expected_result_dict, f"Expected {expected_result_dict}, but got {result}"


def split_complex_numbers(input_string: str, format_type: str) -> list:
    """
    Parses a string containing multiple complex numbers in the form 'real imaginary, real imaginary, ...'
    :param input_string: Input string containing complex numbers
    :param format_type: 'list' or 'dict' to determine the format of complex numbers
    :return: List of complex numbers in either list or dictionary format
    """
    pairs = input_string.split(",")  # Split by commas to separate each complex number
    complex_numbers = []

    for pair in pairs:
        parts = pair.split()  # Split by space to separate real and imaginary parts
        if len(parts) == 2:  # Ensure valid input with both real and imaginary parts
            try:
                real = float(parts[0])
                imaginary = float(parts[1])
                if format_type == 'list':
                    complex_numbers.append(complex_number_list(real, imaginary))
                elif format_type == 'dict':
                    complex_numbers.append(complex_number_dict(real, imaginary))
            except ValueError:
                print(f"Invalid number format: {pair}. Skipping this entry.")
                continue  # Skip invalid complex numbers
        else:
            print(f"Invalid input format: {pair}. Skipping this entry.")
            continue  # Skip invalid entries

    return complex_numbers


# Main function to interact with the user
def menu():
    complex_numbers = []  # Initialize an empty list for complex numbers
    format_type = ''  # 'list' or 'dict' to store the type of format

    while True:
        print("\nMenu:")
        print("1. Choose complex number format (list or dict)")
        print("2. Enter a list of complex numbers")
        print("3. Display all complex numbers")
        print("4. Solve longest distinct subarray problem")
        print("5. Solve longest increasing subsequence problem based on real part")
        print("6. Exit")
        choice = input("Enter your choice: ")

        if choice == "1":
            format_type = input("Enter format type ('list' or 'dict'): ").strip().lower()
            if format_type not in ['list', 'dict']:
                print("Invalid format type. Please enter 'list' or 'dict'.")
                format_type = ''  # Reset format type if invalid
            else:
                print(f"Selected format: {format_type}")


        elif choice == "2":
            if not format_type:
                print("Please select a format type first.")
                continue
            input_string = input(
                f"Enter complex numbers in '{format_type}' format as 'real imaginary, real imaginary, ...': ")
            complex_numbers = split_complex_numbers(input_string, format_type)
            print("\nComplex numbers added successfully.")


        elif choice == "3":
            # Display all complex numbers in their respective formats
            if not complex_numbers:
                print("No complex numbers to display.")
                continue

            print("\nList of complex numbers:")
            for num in complex_numbers:
                if format_type == 'list':
                    print(complex_to_str_list(num))
                elif format_type == 'dict':
                    print(complex_to_str_dict(num))


        elif choice == "4":
            # Solve the longest distinct subarray problem
            if not complex_numbers:
                print("Please enter some complex numbers first.")
                continue
            print("\nSolving longest distinct subarray problem...")

            result = longest_distinct_subarray(complex_numbers)
            print("Longest distinct subarray:")
            if format_type == 'list':
                for num in result:
                    print(complex_to_str_list(num))

            elif format_type == 'dict':
                for num in result:
                    print(complex_to_str_dict(num))


        elif choice == "5":
            # Solve the longest increasing subsequence based on real part
            if not complex_numbers:
                print("Please enter some complex numbers first.")
                continue
            print("\nSolving longest increasing subsequence problem based on real part...")
            result = longest_increasing_subsequence_real(complex_numbers)
            print("Longest increasing subsequence (based on real part):")
            if format_type == 'list':
                for num in result:
                    print(complex_to_str_list(num))
            elif format_type == 'dict':
                for num in result:
                    print(complex_to_str_dict(num))

        elif choice == "6":
            print("Exiting the program.")
            break

        else:
            print("Invalid choice. Please try again.")


# Start the menu

test_longest_increasing_subsequence_real()
test_longest_distinct_subarray()
menu()