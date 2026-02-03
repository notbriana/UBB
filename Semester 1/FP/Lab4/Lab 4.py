def lcs_recursive(X, Y, m, n):
    # Base case: If either string is empty, return 0 and an empty sequence
    if m == 0 or n == 0:
        return 0, ""  # Length 0 and empty sequence

    # If the characters match, add 1 to the length and include the character in the sequence
    if X[m - 1] == Y[n - 1]:
        length, seq = lcs_recursive(X, Y, m - 1, n - 1)  # Recur for both X and Y
        return length + 1, seq + X[m - 1]  # Add the current character to the sequence

    # If characters don't match, we explore both possibilities
    X_length, X_seq = lcs_recursive(X, Y, m - 1, n)
    Y_length, Y_seq = lcs_recursive(X, Y, m, n - 1)

    # Return the longer subsequence and its length
    if X_length > Y_length:
        return X_length, X_seq
    else:
        return Y_length, Y_seq

def lcs_dynamic(X, Y):
    m = len(X)  # Length of the first string
    n = len(Y)  # Length of the second string

    # Initialize a DP table with zero values
    dp = []  # An empty list to store the DP table rows
    for i in range(m + 1):  # Create rows for each character in X (including the zero row at the top)
        dp.append([0] * (n + 1))  # Add columns for each character in Y (including the zero column at the left)

    # Fill the DP table with the lengths of common subsequences
    for i in range(1, m + 1):  # Loop through the characters of X
        for j in range(1, n + 1):  # Loop through the characters of Y
            if X[i - 1] == Y[j - 1]:  # If the characters match
                dp[i][j] = dp[i - 1][j - 1] + 1  # Add 1 to the LCS of the previous characters
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])  # Take the maximum of excluding one character

    # The length of the LCS is stored in dp[m][n]
    lcs_length = dp[m][n]  # The length of the longest common subsequence

    # Backtrack to find one possible LCS sequence
    lcs_sequence = []  # Initialize an empty list to store the LCS sequence
    i, j = m, n  # Start from the bottom-right corner of the table
    while i > 0 and j > 0:  # While there are characters to compare
        if X[i - 1] == Y[j - 1]:  # If the characters match
            lcs_sequence.append(X[i - 1])  # Add the character to the LCS sequence
            i -= 1  # Move to the previous character in the first string
            j -= 1  # Move to the previous character in the second string
        elif dp[i - 1][j] >= dp[i][j - 1]:  # If moving left gives a longer subsequence
            i -= 1  # Move to the previous character in the first string
        else:  # Otherwise, move up in the table
            j -= 1  # Move to the previous character in the second string

    # The LCS sequence is built backwards, so we reverse it
    lcs_sequence.reverse()  # Reverse the sequence to get the correct order

    return lcs_length, ''.join(lcs_sequence)  # Return the length and the LCS sequence as a string


def test_lcs():
    # Test 1: Basic Example
    X = "MNPNQMN"
    Y = "NQPMNM"
    expected_length = 4
    expected_sequence = "NQMN"  # One possible LCS

    # Test Recursive Method
    assert lcs_recursive(X, Y, len(X), len(Y)) == expected_length

    # Test Dynamic Programming Method
    dp_length, dp_sequence = lcs_dynamic(X, Y)
    assert dp_length == expected_length
    assert dp_sequence == expected_sequence

    # Test 2: Edge Case - Empty Strings
    X = ""
    Y = ""
    assert lcs_recursive(X, Y, len(X), len(Y)) == 0
    dp_length, dp_sequence = lcs_dynamic(X, Y)
    assert dp_length == 0
    assert dp_sequence == ""

    # Test 3: No Common Characters
    X = "ABCDE"
    Y = "XYZ"
    assert lcs_recursive(X, Y, len(X), len(Y)) == 0
    dp_length, dp_sequence = lcs_dynamic(X, Y)
    assert dp_length == 0
    assert dp_sequence == ""

    # Test 4: All Characters Match
    X = "ABC"
    Y = "ABC"
    expected_length = 3
    expected_sequence = "ABC"  # The whole string is the LCS
    assert lcs_recursive(X, Y, len(X), len(Y)) == expected_length
    dp_length, dp_sequence = lcs_dynamic(X, Y)
    assert dp_length == expected_length
    assert dp_sequence == expected_sequence

    print("All tests passed!")


def main_menu():
    while True:
        print("1. Use Recursive Method")
        print("2. Use Dynamic Programming Method")
        print("3. Run Tests")
        print("4. Exit")

        choice = input("Choose an option (1/2/3/4): ")

        if choice == '1':
            X = input("Enter the first string: ")
            Y = input("Enter the second string: ")
            m, n = len(X), len(Y)
            lcs_length = lcs_recursive(X, Y, m, n)
            print(f"Length of LCS (Recursive): {lcs_length}")

        elif choice == '2':
            X = input("Enter the first string: ")
            Y = input("Enter the second string: ")
            lcs_length, lcs_sequence = lcs_dynamic(X, Y)
            print(f"Length of LCS (Dynamic Programming): {lcs_length}")
            print(f"One possible LCS: {lcs_sequence}")

        elif choice == '3':
            test_lcs()  # Run tests

        elif choice == '4':
            print("Exiting...")
            break
        else:
            print("Invalid choice, please try again.")


# Call main_menu to interact with the user
main_menu()