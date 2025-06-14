#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#

from functions import (
    add_expense, remove_expenses, display_dict, filter_expenses, undo, save_state
)


def run_ui(expenses):
    """
    Main function to handle the user interface and interaction with the application.

    :param expenses: Dictionary containing all expenses.
    """
    while True:
        print("\nExpense Tracker")
        print("-------------------")
        print("1. Add Expense")
        print("2. Remove Expenses")
        print("3. Display Expenses")
        print("4. Filter Expenses")
        print("5. Undo Last Action")
        print("6. Exit")

        choice = input("\nEnter your choice: ").strip()

        if choice == "1":
            save_state(expenses)
            day_input = input("Enter the day (1-30, or press Enter for no day): ").strip()
            day = int(day_input) if day_input else None
            amount = int(input("Enter the amount: ").strip())
            category = input("Enter the category: ").strip()

            add_expense(expenses, amount, category, day)
            print("\nExpense added successfully!")

        elif choice == "2":
            save_state(expenses)
            print("\nRemove Expenses Options:")
            print("1. By day")
            print("2. By day range")
            print("3. By category")
            option = input("Choose an option (1/2/3): ").strip()

            if option == "1":
                day = int(input("Enter the day to remove expenses: ").strip())
                remove_expenses(expenses, day)
                print("\nExpenses for the day removed successfully!")
            elif option == "2":
                start_day = int(input("Enter the start day: ").strip())
                end_day = int(input("Enter the end day: ").strip())
                remove_expenses(expenses, (start_day, end_day))
                print("\nExpenses for the range removed successfully!")
            elif option == "3":
                category = input("Enter the category: ").strip()
                remove_expenses(expenses, category)
                print("\nExpenses for the category removed successfully!")
            else:
                print("\nInvalid option. Please try again.")


        elif choice == "3":

            print("\nDisplay Expenses Options:")
            print("1. Display all expenses")
            print("2. Filter by category")
            print("3. Filter by condition (symbol and value)")
            option = input("Choose an option (1/2/3): ").strip()

            if option == "1":
                print(display_dict(expenses, None))

            elif option == "2":
                category = input("Enter the category: ").strip()
                print(display_dict(expenses, category))

            elif option == "3":
                category = input("Enter the category to filter by: ").strip()
                condition = input("Enter condition (<, =, >, or leave blank for no condition): ").strip()
                value = None

                if condition:
                    value = int(input("Enter the value to compare: ").strip())
                print(display_dict(expenses,(category, condition, value)))
            else:
                print("\nInvalid option. Please try again.")

        elif choice == "4":
            category = input("Enter the category to filter: ").strip()
            condition = input("Enter condition (<, =, >, or leave blank for no condition): ").strip()
            value = None

            if condition:
                value = int(input("Enter the value to compare: ").strip())

            filtered = filter_expenses(expenses, category, condition, value)
            print(display_dict(filtered, None))

        elif choice == "5":
            undo(expenses)
            print("\nLast action undone successfully!")

        elif choice == "6":
            print("\nExiting the program. Goodbye!")
            break

        else:
            print("\nInvalid choice. Please enter a valid option.")
