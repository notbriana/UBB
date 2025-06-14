# The program's functions are implemented here.
# There is no user interaction in this file, therefore no input/print statements.
# Functions here communicate via function parameters, the return statement, and raising of exceptions.

from datetime import datetime

from texttable import Texttable

valid_categories = {"housekeeping", "food", "transport", "clothing", "internet", "others"}


def get_amount(expense: dict) -> int:
    """
    Retrieves the amount of money spent on a given expense.

    :param expense: A dictionary representing an expense.
    :return: The amount spent on the expense.
    """
    return expense['amount']

def get_category(expense: dict) -> str:
    """
    Retrieves the category of a given expense.

    :param expense: A dictionary representing an expense.
    :return: The category of the expense.
    """
    return expense['category']

def get_day(expense: dict) -> int:
    """
    Retrieves the day the expense was made.

    :param expense: A dictionary representing an expense.
    :return: The day the expense was made.
    """
    return expense['day']

def set_amount(expense: dict, amount: int) -> dict:
    """
    Updates the amount of money spent on a given expense.

    :param expense: A dictionary representing the expense.
    :param amount: The new amount to set for the expense.
    :return: The updated expense dictionary with the new amount.
    """
    if amount <= 0:
        raise ValueError("Amount must be a positive integer.")
    expense['amount'] = amount
    return expense

def set_category(expense: dict, category: str) -> dict:
    """
    Updates the category of a given expense.

    :param expense: A dictionary representing the expense.
    :param category: The new category to set for the expense.
    :return: The updated expense dictionary with the new category.
    """
    if category not in valid_categories:
        raise ValueError(f"Invalid category. Must be one of: {', '.join(valid_categories)}")
    expense['category'] = category
    return expense

def set_day(expense: dict, day: int) -> dict:
    """
    Updates the day on which the expense was made.

    :param expense: A dictionary representing the expense.
    :param day: The new day to set for the expense.
    :return: The updated expense dictionary with the new day.
    """
    if day < 1 or day > 30:
        raise ValueError("Day must be between 1 and 30.")
    expense['day'] = day
    return expense

def expenses_dict(amount: int, category: str, day: int = None) -> dict:
    """
    Creates a dictionary to represent an expense.

    :param amount: The amount of money spent on the expense. It must be a positive integer.
    :param category: The category of the expense, which must be one of the predefined categories.
    :param day: The day the expense was made. If not provided, it defaults to the current day.
    :return: A dictionary containing the expense details: day, amount, and category.
    """
    if amount <= 0:
        raise ValueError("Amount must be a positive integer.")

    if category not in valid_categories:
        raise ValueError(f"Invalid category. Must be one of: {', '.join(valid_categories)}")

    if day is None:
        day = datetime.now().day

    if day < 1 or day > 30:
        raise ValueError("Day must be between 1 and 30.")

    return {"day": day, "amount": amount, "category": category}

def add_expense(expenses: dict, amount: int, category: str, day: int = None) -> None:
    """
    Adds an expense for the current day or a given day.

    :param day: The current day or a given day.
    :param expenses: Dictionary to store all expenses by day.
    :param amount: Amount to add.
    :param category: Expense category.
    """
    if day is None:
        day = datetime.now().day

    if day not in expenses:
        expenses[day] = []

    expense = expenses_dict(amount, category, day)
    expenses[day].append(expense)

def remove_expenses(expenses: dict, identifier):
    """
    Removes expenses based on the provided identifier.

    :param expenses: Dictionary containing all expenses.
    :param identifier: Either a day (int), a range of days (tuple), or a category (str).
    """
    if isinstance(identifier, int):
        if identifier in expenses:
            del expenses[identifier]
        else:
            raise ValueError(f"No expenses found for day {identifier}.")

    elif isinstance(identifier, tuple) and len(identifier) == 2:
        start_day, end_day = identifier
        if start_day < 1 or start_day > 30 or end_day < 1 or end_day > 30:
            raise ValueError("Days must be between 1 and 30.")
        if start_day > end_day:
            raise ValueError("Start day must be less than or equal to end day.")

        for day in range(start_day, end_day + 1):
            if day in expenses:
                del expenses[day]

    elif isinstance(identifier, str):
        if identifier not in valid_categories:
            raise ValueError(f"Invalid category. Must be one of: {', '.join(valid_categories)}")

        for day in expenses:
            expenses[day] = [expense for expense in expenses[day] if expense["category"] != identifier]

    else:
        raise ValueError("Invalid identifier. Must be an int (day), tuple (start day, end day), or a string (category).")

"""
def test_add_expense():
    # Test adding expense for a specific day
    expenses = {}
    add_expense(expenses, 50, "food", 5)
    expected = {5: [{"amount": 50, "category": "food", "day": 5}]}
    assert expenses == expected, f"Expected {expected}, but got {expenses}"

    # Test adding expense for the current day
    current_day = datetime.now().day
    add_expense(expenses, 30, "transport")
    expected[current_day] = [{"amount": 30, "category": "transport", "day": current_day}]
    assert expenses[current_day] == expected[current_day], f"Expected {expected}, but got {expenses}"

def test_remove_expenses():
    # Test removing expenses for a specific day
    expenses = {5: [{"amount": 50, "category": "food", "day": 5}]}
    remove_expenses(expenses, 5)
    expected = {}
    assert expenses == expected, f"Expected {expected}, but got {expenses}"

    # Test removing expenses for a range of days
    expenses = {
        1: [{"amount": 20, "category": "food", "day": 1}],
        2: [{"amount": 30, "category": "transport", "day": 2}],
        3: [{"amount": 40, "category": "entertainment", "day": 3}],
    }
    remove_expenses(expenses, (1, 2))
    expected = {3: [{"amount": 40, "category": "entertainment", "day": 3}]}
    assert expenses == expected, f"Expected {expected}, but got {expenses}"

    # Test removing expenses by category
    expenses = {
        1: [{"amount": 20, "category": "food", "day": 1}],
        2: [{"amount": 30, "category": "food", "day": 2}],
        3: [{"amount": 40, "category": "entertainment", "day": 3}],
    }
    remove_expenses(expenses, "food")
    expected = {3: [{"amount": 40, "category": "entertainment", "day": 3}]}
    assert expenses == expected, f"Expected {expected}, but got {expenses}"

def run_tests():
    test_add_expense()
    test_remove_expenses()
    print("All tests passed!")

"""


def display_dict(expenses: dict, identifier):
    """
    Format expenses in a table. The function filters the expenses
    based on the identifier. If no identifier is provided, all expenses are included.
    If a category is provided, only those expenses for that category are included.
    If a tuple is provided (category and value comparison), the expenses are filtered accordingly.

    :param expenses: Dictionary containing expenses, categorized by day.
    :param identifier: Can be None, a string (category), or a tuple (category, comparison, value).
    :return: Formatted table as a string.
    """
    table = Texttable()
    table.add_row(["Day", "Amount", "Category"])

    if identifier is None:
        for day in expenses:
            for expense in expenses[day]:
                table.add_row([expense["day"], expense["amount"], expense["category"]])

    elif isinstance(identifier, str):
        for day in expenses:
            for expense in expenses[day]:
                if identifier == expense["category"]:
                    table.add_row([expense["day"], expense["amount"], expense["category"]])

    elif isinstance(identifier, tuple):
        if len(identifier) != 3:
            raise ValueError("Tuple identifier must contain category, operator, and value.")

        category, operator, value = identifier

        if category not in valid_categories:
            raise ValueError(f"Invalid category. Valid categories are: {', '.join(valid_categories)}")

        for day in expenses:
            for expense in expenses[day]:
                if expense["category"] == category:
                    if operator == "<" and expense["amount"] < value:
                        table.add_row([expense["day"], expense["amount"], expense["category"]])
                    elif operator == "=" and expense["amount"] == value:
                        table.add_row([expense["day"], expense["amount"], expense["category"]])
                    elif operator == ">" and expense["amount"] > value:
                        table.add_row([expense["day"], expense["amount"], expense["category"]])

    return table.draw()

def filter_expenses(expenses: dict, category: str, condition=None, value: int = None):
    """
    Filters expenses based on category and optional condition.

    :param expenses: Dictionary of expenses where keys are days (int) and values are lists of expense dictionaries.
    :param category: The category to filter by (str).
    :param condition: A comparison operator ('<', '=', '>') or None.
    :param value: The value to compare amounts against, if condition is provided.
    :return: A filtered dictionary of expenses.
    """
    valid_conditions = {'<', '=', '>'}
    if condition not in valid_conditions:
        raise ValueError(f"Invalid condition. Must be one of: {', '.join(valid_conditions)}")
    if condition and value is None:
        raise ValueError("Value must be provided when a condition is specified.")

    filtered_expenses = {}
    for day, day_expenses in expenses.items(): #.items = key-value pairs
        filtered_day_expenses = []
        for expense in day_expenses:
            if expense["category"] == category:
                if condition == '<' and expense["amount"] < value:
                    filtered_day_expenses.append(expense)
                elif condition == '=' and expense["amount"] == value:
                    filtered_day_expenses.append(expense)
                elif condition == '>' and expense["amount"] > value:
                    filtered_day_expenses.append(expense)
                elif condition is None:
                    filtered_day_expenses.append(expense)
        if filtered_day_expenses:
            filtered_expenses[day] = filtered_day_expenses

    return filtered_expenses


undo_stack = []


def save_state(expenses):
    """
    Saves the current state of the expenses to allow undoing later.

    :param expenses: The current list of expenses (list of dictionaries).
    """
    undo_stack.append(expenses.copy())  # Adds the copied version of expenses to the undo_stack


def undo(expenses):
    """
    Reverts the expenses to the last saved state.

    :param expenses: The current list of expenses (list of dictionaries).
    :return: The updated list of expenses after undoing the last operation.
    :raises Exception: If there are no operations to undo.
    """
    if not undo_stack:
        raise Exception("No operations to undo.")

    last_state = undo_stack.pop()  # Removes and returns the last item from the undo_stack list
    expenses.clear()  # Clears the list of expenses
    expenses.extend(last_state)  # Restores the last state into expenses
    return expenses



"""
f = open("doc.html", "wt")
f.write(pdoc("functions.py", ""))
f.close()
"""

def test_undo():
    """
    Test undo function with multiple undo operations.
    """
    expenses = [{"day": 1, "amount": 100, "category": "Food"}]
    save_state(expenses)

    print("Initial expenses:", expenses)

    expenses.append({"day": 2, "amount": 200, "category": "Transport"})
    print("Modified expenses (1):", expenses)

    save_state(expenses)

    expenses.append({"day": 3, "amount": 300, "category": "Internet"})
    print("Modified expenses (2):", expenses)

    save_state(expenses)

    undo(expenses)
    print("After 1st undo (removed Internet):", expenses)

    undo(expenses)
    print("After 2nd undo (removed Transport):", expenses)

    undo(expenses)
    print("After 3rd undo (removed Food):", expenses)

    assert len(expenses) == 1, "Expenses should be reverted to the saved state."
    assert expenses[0] == {"day": 1, "amount": 100, "category": "Food"}, "Expenses should match the saved state."
    print("Final expenses (should be the initial state):", expenses)



test_undo()
