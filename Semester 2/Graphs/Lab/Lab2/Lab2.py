import random



def print_menu() -> None:
    print("\nMain Menu: ")
    print("1. Generate a list of n random natural numbers. Generated numbers must be between 0 and 1000.")
    print("2. Search for an item in the list using Binary search.")
    print("3. Sort the list using Bubble Sort.")
    print("4. Sort the list using Gnome Sort.")
    print("5. Exit the program.")



def random_numbers(n: int) -> list:
    random_list = []

    for _ in range(n):
        random_list.append(random.randint(1, 1000))

    return random_list



def bubble_sort(my_list: list, step: int) -> list:

    swap_count = 0

    for i in range(len(my_list) - 1):
        is_swapped = False
        for j in range(0, len(my_list) - i - 1):
            if my_list[j] > my_list[j + 1]:
                temp = my_list[j]
                my_list[j] = my_list[j + 1]
                my_list[j + 1] = temp
                is_swapped = True

                swap_count += 1
                if swap_count % step == 0:
                    print(f"Partially sorted list (after {swap_count} swaps): {my_list}")

        if not is_swapped:
            break

    return my_list



def gnome_sort(my_list: list, step: int) -> list:

    i = 0
    swap_count = 0

    while i < len(my_list):
        if i == 0:
            i = i + 1
        if my_list[i] >= my_list[i - 1]:
            i = i + 1
        else:
            temp = my_list[i]
            my_list[i] = my_list[i - 1]
            my_list[i - 1] = temp

            swap_count += 1
            if swap_count % step == 0:
                print(f"Partially sorted list (after {swap_count} swaps): {my_list}")

            i = i - 1

    return my_list



def binary_search(my_list: list, element: int) -> int:

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



def start_menu():

    random_list = []
    is_sorted = True

    while True:
        print_menu()

        choice = int(input("Please choose an option: "))

        if choice == 1:
            n = int(input("How many numbers would you like to generate?\n"))
            random_list = random_numbers(n)
            is_sorted = False
            print(f"The list is: {random_list}")

        elif choice == 2:
            if not random_list:
                print("The list is empty. Generate numbers first.")
            elif not is_sorted:
                print("You must sort the list before performing a binary search.")
            else:
                element = int(input("Enter the number you want to search for: "))
                result = binary_search(random_list, element)
                if result != -1:
                    print(f"Element found at index {result}")
                else:
                    print("Element not found")

        elif choice == 3:
            if random_list:
                step = int(input("Enter the step for printing partially sorted list: "))
                sorted_list = bubble_sort(random_list, step)
                is_sorted = True
                print(f"The sorted list is: {sorted_list}")
            else:
                print("The list is empty. Generate numbers first.")


        elif choice == 4:
            if random_list:
                step = int(input("Enter the step for printing partially sorted list: "))
                sorted_list = gnome_sort(random_list, step)
                is_sorted = True
                print(f"The sorted list is: {sorted_list}")
            else:
                print("The list is empty. Generate numbers first.")

        elif choice == 5:
            print("Exiting...")
            break

        else:
            print("Invalid choice, please try again.")



start_menu()