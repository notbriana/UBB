import random
import timeit

# Generate a list of sorted numbers for the best case
def generate_best_case(n: int) -> list:
    return list(range(1, n + 1))

# Generate a list of reversed numbers for worst case
def generate_worst_case(n: int) -> list:
    return list(range(n, 0, -1))

# Generate a list of random numbers for average case
def generate_average_case(n: int) -> list:
    return [random.randint(1, 1000) for _ in range(n)]

# Define function for creating a menu operation
def create_operation(op_id, name, function):
    return {
        "op_id": op_id,
        "name": name,
        "function": function
    }

# Menu display function
def print_menu(operations: dict) -> None:
    print("\nMain Menu:")
    for op in operations.values():
        print(f"{op['op_id']}. {op['name']}")

# Generate a list of random numbers
def random_numbers(n: int) -> dict:
    random_list = [random.randint(1, 1000) for _ in range(n)]
    return {"random_list": random_list, "is_sorted": False}

"""
The Bubble Sort algorithm has two loops: an inner loop and an outer loop.
The inner loop inevitably performs O(n) comparisons.


- The worst case scenario occurs when the array is sorted in reverse order. Every element must be compared and potentially swapped. 
In the worst-case scenario, the outer loop runs O(n) times.
The worst-case time complexity of bubble sort is O(n x n) = O(n x n) (n^2).

- In the best-case scenario, the array is already sorted, but just in case, bubble sort will still check each pair of adjacent elements.
As a result, the time complexity of bubble sort in the best-case scenario is O(n).

- If the list is randomly arranged, the average case occurs. Bubble sort may still require (n/2) passes and O(n) comparisons for each pass in the average case.
As a result, the average case time complexity of bubble sort is O(n/2 x n) = O (n^2).

"""


# Bubble sort with partial print functionality
def bubble_sort(context: dict, step: int) -> dict:
    my_list = context["random_list"]
    swap_count = 0

    for i in range(len(my_list) - 1):
        is_swapped = False
        for j in range(0, len(my_list) - i - 1):
            if my_list[j] > my_list[j + 1]:
                my_list[j], my_list[j + 1] = my_list[j + 1], my_list[j]
                is_swapped = True
                swap_count += 1
                if swap_count % step == 0:
                    print(f"Partially sorted list (after {swap_count} swaps): {my_list}")

        if not is_swapped:
            break

    context["random_list"] = my_list
    context["is_sorted"] = True
    return context

"""
In Gnome sort, there are no nested loops, only one while.

The worst case scenario occurs when the list is in reverse order. In this scenario, Gnome sort will repeatedly swap elements back and forth. 
In this case, each element may have to be compared with every other element in the list multiple times due to the backtracking nature of the algorithm.
For n elements there may be n*(n-1)/2 comparisons, so O(n^2)

The best case occurs when the input array is already sorted in ascending order. The algorithm performs one comparison for each element and moves the index forward without needing any swaps or backtracking.
Thus, it results in a linear number of comparisons, leading to O(n).

The average case represents a scenario where the input array is in random order. The index will increment when elements are in the correct order and decrement when they are not.
The backtracking behavior means that many elements will be compared multiple times before reaching the correct sorted order.
Thus, the average time complexity will also be O(n^2).


"""


# Gnome sort with partial print functionality
def gnome_sort(context: dict, step: int) -> dict:
    my_list = context["random_list"]
    i = 0
    swap_count = 0

    while i < len(my_list):
        if i == 0 or my_list[i] >= my_list[i - 1]:
            i += 1
        else:
            my_list[i], my_list[i - 1] = my_list[i - 1], my_list[i]
            swap_count += 1
            if swap_count % step == 0:
                print(f"Partially sorted list (after {swap_count} swaps): {my_list}")
            i -= 1

    context["random_list"] = my_list
    context["is_sorted"] = True
    return context

# Bubble sort with no partial print functionality
def bubble_sort_no_print(context: dict) -> dict:
    my_list = context["random_list"]
    for i in range(len(my_list) - 1):
        is_swapped = False
        for j in range(0, len(my_list) - i - 1):
            if my_list[j] > my_list[j + 1]:
                my_list[j], my_list[j + 1] = my_list[j + 1], my_list[j]
                is_swapped = True
        if not is_swapped:
            break
    context["random_list"] = my_list
    context["is_sorted"] = True
    return context

# Gnome sort with no partial print functionality
def gnome_sort_no_print(context: dict) -> dict:
    my_list = context["random_list"]
    i = 0
    while i < len(my_list):
        if i == 0 or my_list[i] >= my_list[i - 1]:
            i += 1
        else:
            my_list[i], my_list[i - 1] = my_list[i - 1], my_list[i]
            i -= 1
    context["random_list"] = my_list
    context["is_sorted"] = True
    return context


"""
For binary search, the best case is when the element is at the middle index of the array. 
It takes only one comparison to find the target element. So the best case complexity is O(1).

For a random element, there are two possible choices. When the element is present in the list, and when it's not (n + 1 cases).
So, total comparisons for log n elements:
= 1*(elements requiring 1 comparisons) + 2*(elements requiring 2 comparisons) + . . . + logN*(elements requiring logN comparisons)
= 1*1 + 2*2 + 3*4 + . . . + logN * (2logN-1)
= 2logN * (logN – 1) + 1
= N * (logN – 1) + 1
Thus, the average time complexity is O(log n)

The worst case will be when the element is present in the first position. As seen in the average case, the comparison required to reach the first element is logN. So the time complexity for the worst case is O(logN).
"""

# Binary search function
def binary_search(context: dict, element: int) -> int:
    my_list = context["random_list"]
    start = 0
    end = len(my_list) - 1
    while start <= end:
        mid = (start + end) // 2
        if element == my_list[mid]:
            return mid
        elif my_list[mid] < element:
            start = mid + 1
        else:
            end = mid - 1
    return -1

def measure_sort_times(context: dict, sort_func, case_func, label: str):
    sizes = [random.randint(500, 10000) for _ in range(5)]  # Generate 5 random sizes
    for size in sizes:
        context["random_list"] = case_func(size)  # Generate the list
        context["is_sorted"] = False
        time_taken = timeit.timeit('sort_func(context)', globals={'sort_func': sort_func, 'context': context}, number=1)
        print(f"{label}: List of size {size} sorted in {time_taken:.5f} seconds")

def measure_search_times(context: dict, element: int, case_func, label: str):
    sizes = [random.randint(500, 10000) for _ in range(5)]  # Generate 5 random sizes between 500 and 10000
    for size in sizes:
        context["random_list"] = case_func(size)
        context["is_sorted"] = True  # Ensure the list is sorted for binary search
        time_taken = timeit.timeit(lambda: binary_search(context, element), number=1)
        print(f"{label}: List of size {size} searched in {time_taken:.5f} seconds")

# Functions for menu choices
def menu_generate_numbers(context: dict):
    n = int(input("How many numbers would you like to generate?\n"))
    context.update(random_numbers(n))
    print(f"The list is: {context['random_list']}")

def menu_binary_search(context: dict):
    if not context.get("random_list"):
        print("The list is empty. Generate numbers first.")
    elif not context.get("is_sorted"):
        print("You must sort the list before performing a binary search.")
    else:
        element = int(input("Enter the number you want to search for: "))
        result = binary_search(context, element)
        if result != -1:
            print(f"Element found at index {result}")
        else:
            print("Element not found")

def menu_bubble_sort(context: dict):
    if context.get("random_list"):
        step = int(input("Enter the step for printing partially sorted list: "))
        context.update(bubble_sort(context, step))
        print(f"The sorted list is: {context['random_list']}")
    else:
        print("The list is empty. Generate numbers first.")

def menu_gnome_sort(context: dict):
    if context.get("random_list"):
        step = int(input("Enter the step for printing partially sorted list: "))
        context.update(gnome_sort(context, step))
        print(f"The sorted list is: {context['random_list']}")
    else:
        print("The list is empty. Generate numbers first.")

# Menu choices for best, average, and worst case
def menu_sort_best_case(context: dict):
    print("Timing Bubble Sort and Gnome Sort for Best Case:")
    measure_sort_times(context, bubble_sort_no_print, generate_best_case, "Bubble Sort")
    measure_sort_times(context, gnome_sort_no_print, generate_best_case, "Gnome Sort")

def menu_sort_average_case(context: dict):
    print("Timing Bubble Sort and Gnome Sort for Average Case:")
    measure_sort_times(context, bubble_sort_no_print, generate_average_case, "Bubble Sort")
    measure_sort_times(context, gnome_sort_no_print, generate_average_case, "Gnome Sort")

def menu_sort_worst_case(context: dict):
    print("Timing Bubble Sort and Gnome Sort for Worst Case:")
    measure_sort_times(context, bubble_sort_no_print, generate_worst_case, "Bubble Sort")
    measure_sort_times(context, gnome_sort_no_print, generate_worst_case, "Gnome Sort")

# Menu choices for binary search timing
def menu_search_best_case(context: dict):
    print("Timing Binary Search for Best Case:")
    element = generate_best_case(1)[0]  # Element is at the middle (1 in sorted list of size 1)
    measure_search_times(context, element, generate_best_case, "Binary Search")

def menu_search_average_case(context: dict):
    print("Timing Binary Search for Average Case:")
    element = random.randint(1, 1000)  # Random element for average case
    measure_search_times(context, element, generate_average_case, "Binary Search")

def menu_search_worst_case(context: dict):
    print("Timing Binary Search for Worst Case:")
    element = 1  # In worst case, the element is the first element (in a sorted list)
    measure_search_times(context, element, generate_worst_case, "Binary Search")

# Exit function
def menu_exit(context: dict):
    print("Exiting the program...")

# Main menu function
def start_menu():
    context = {"random_list": [], "is_sorted": False}
    operations = {
        1: create_operation(1, "Generate a list of n random natural numbers", menu_generate_numbers),
        2: create_operation(2, "Search for an item in the list using Binary search", menu_binary_search),
        3: create_operation(3, "Sort the list using Bubble Sort", menu_bubble_sort),
        4: create_operation(4, "Sort the list using Gnome Sort", menu_gnome_sort),
        5: create_operation(5, "Time sorting algorithms for Best Case", menu_sort_best_case),
        6: create_operation(6, "Time sorting algorithms for Average Case", menu_sort_average_case),
        7: create_operation(7, "Time sorting algorithms for Worst Case", menu_sort_worst_case),
        8: create_operation(8, "Time Binary Search for Best Case", menu_search_best_case),
        9: create_operation(9, "Time Binary Search for Average Case", menu_search_average_case),
        10: create_operation(10, "Time Binary Search for Worst Case", menu_search_worst_case),
        11: create_operation(11, "Exit the program", menu_exit)
    }

    while True:
        print_menu(operations)
        choice = int(input("Please choose an option: "))
        if choice in operations:
            if choice == 11:  # Exit
                menu_exit(context)
                break
            else:
                operations[choice]["function"](context)
        else:
            print("Invalid choice, please try again.")

start_menu()
