### USING MULTIPLE FUNCTIONS AS PER PS1###
import cs50


def main():
    # input in dollars
    while (True):
        change = cs50.get_float("Change owed: ")
        if (change >= 0):
            break

    quarters = calculate_quarters(change)
    change = round(change - (quarters * 0.25), 2)
    dimes = calculate_dimes(change)
    change = round(change - (dimes * 0.1), 2)
    nickel = calculate_nickels(change)
    change = round(change - (nickel * 0.05), 2)
    pennies = calculate_pennies(change)
    change = round(change - (pennies * 0.01), 2)
    print(quarters + dimes + nickel + pennies)


def calculate_quarters(change):
    remainder = int(change // 0.25)
    return remainder


def calculate_dimes(change):
    remainder = int(change // 0.1)
    return remainder


def calculate_nickels(change):
    remainder = int(change // 0.05)
    return remainder


def calculate_pennies(change):
    remainder = int(change // 0.01)
    return remainder


main()