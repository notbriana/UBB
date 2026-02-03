#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#

from ui import run_ui
from functions import add_expense
import random


def initialize_expenses():
    """
    Initialize the application with at least 10 randomly generated expenses.

    :return: A dictionary with initialized expenses.
    """
    categories = ["housekeeping", "food", "transport", "clothing", "internet", "others"]
    expenses_list = {}
    for _ in range(10):
        amount = random.randint(10, 500)
        category = random.choice(categories)
        day = random.randint(1, 30)
        add_expense(expenses_list, amount, category, day)
    return expenses_list


if __name__ == "__main__":
    expenses = initialize_expenses()
    run_ui(expenses)
