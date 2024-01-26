### USING SINGLE FUNCTION ###
import cs50

# input in dollars
while (True):
    change = cs50.get_float("Change owed: ")
    if (change >= 0):
        break

# 25c
quarters = int(change // 0.25)
change = round(change - (quarters * 0.25), 2)
# print(f"quarters:{quarters}")
# print(f"change:{change}")

# 10c
dimes = int(change // 0.1)
change = round(change - (dimes * 0.1), 2)
# print(f"dimes:{dimes}")
# print(f"change:{change}")

# 5c
nickel = int(change // 0.05)
change = round(change - (nickel * 0.05), 2)
# print(f"nickel:{nickel}")
# print(f"change:{change}")

# 1c
pennies = int(change // 0.01)
change = round(change - (pennies * 0.01), 2)
# print(f"pennies:{pennies}")
# print(f"change:{change}")

print(quarters+dimes+nickel+pennies)

"""
$ python cash.py
Change owed: 0.41
4

$ ./cash
Change owed: -41
Change owed: foo
Change owed: 41
4

Write, in a file called cash.py, a program that first asks the user how much change is owed and then spits out the minimum number of coins with which said change can be made.

Use get_float from the CS50 Library to get the user’s input and print to output your answer. Assume that the only coins available are quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢).
We ask that you use get_float so that you can handle dollars and cents, albeit sans dollar sign. In other words, if some customer is owed $9.75 (as in the case where a newspaper costs 25¢ but the customer pays with a $10 bill), assume that your program’s input will be 9.75 and not $9.75 or 975. However, if some customer is owed $9 exactly, assume that your program’s input will be 9.00 or just 9 but, again, not $9 or 900. Of course, by nature of floating-point values, your program will likely work with inputs like 9.0 and 9.000 as well; you need not worry about checking whether the user’s input is “formatted” like money should be.
If the user fails to provide a non-negative value, your program should re-prompt the user for a valid amount again and again until the user complies.
Incidentally, so that we can automate some tests of your code, we ask that your program’s last line of output be only the minimum number of coins possible: an integer followed by a newline.

Change owed: 4.1
change:0.09999999999999964
quarters:16
change:0.09999999999999964
dimes:0
change:0.09999999999999964
nickel:1
change:0.009999999999999648
pennies:9

"""