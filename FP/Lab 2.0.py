import random

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

# Main menu function
def start_menu():
    context = {"random_list": [], "is_sorted": False}

    operations = {
        1: create_operation(1, "Generate a list of n random natural numbers", menu_generate_numbers),
        2: create_operation(2, "Search for an item in the list using Binary search", menu_binary_search),
        3: create_operation(3, "Sort the list using Bubble Sort", menu_bubble_sort),
        4: create_operation(4, "Sort the list using Gnome Sort", menu_gnome_sort),
        5: create_operation(5, "Exit the program", lambda x: print("Exiting..."))
    }

    while True:
        print_menu(operations)
        choice = int(input("Please choose an option: "))

        if choice in operations:
            if choice == 5:  # Exit
                break
            else:
                operations[choice]["function"](context)
        else:
            print("Invalid choice, please try again.")

# Run the program
start_menu()
