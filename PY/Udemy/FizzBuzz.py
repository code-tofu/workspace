# EXERCISE16
"""
you have to write a function named sum_eo with the following parameters: n: a positive number t: a str
If t has the value 'e', the function should return the sum of all even natural numbers less than n.
Else if t has the value 'o', the function should return the sum of all odd natural numbers less than n.
For any other values of t return -1.
"""

def sum_eo(n,t):
    sum = 0
    i = 0
    if t == "e":
        for i < n:
            if i %2 == 0:
                sum += i
            i +=1
        return sum
    if t == "O":
        for i < n:
            if i % 2 == 1:
                sum += i
            i += 1
        return sum

# def sum_eo(n, t):
#     """Sum even or odd numbers in range.
#
#     Return the sum of even or odd natural numbers, in the range 1..n-1.
#
#     :param n: The endpoint of the range. The numbers from 1 to n-1 will be summed.
#     :param t: 'e' to sum even numbers, 'o' to sum odd numbers.
#     :return: The sum of the even or odd numbers in the range.
#             Returns -1 if `t` is not 'e' or 'o'.
#     """
#     if t == "e":
#         start = 2
#     elif t == 'o':
#         start = 1
#     else:
#         return -1
#
#     return sum(range(start, n, 2))
#
# #
# x = sum_eo(11, 'spam')
# print(x)

# EXERCISE 17
"""
For this exercise, you'll write a function that returns the next answer, in the game of fizz buzz.
It's a simple game, usually played with 2 or more people.
You start counting, in turn. That's easy enough, but there's a complication.
If the number is divisible by 3, you say "fizz" instead.
If it's divisible by 5, you say "buzz".
And if it's divisible by both 3 and 5, you say "fizz buzz".
"""


def fizz_buzz(number: int) -> str:
    """
    returns the next answer for the game fizzbuzz
    :param number: The current number in the fizz buzz game
    :return: fizz, buzz, fizzbuzz or the next number, depending on fizzbuzz rules
    """
    if (number % 5) == 0 and (number % 3) == 0:
        return "fizz buzz"
    # should check this solution first (most limiting)
    elif (number % 5) == 0:
        return "buzz"
    elif (number % 3) == 0:
        return "fizz"
    else:
        return str(number)


# EXERCISE 18
def factorial(value: int) -> int:
    """
    returns the factorial value of input number
    :param number: input value to calculate the factorial of
    :return: the factorial value
    """
    factorial_n = 1
    factorial_sum = 1
    while factorial_n <= value:
        factorial_sum = factorial_sum * factorial_n
        factorial_n += 1
    return factorial_sum


# EXERCISE19

def sum_numbers(*inputValues) -> float:
    """
    provides the sum of input values
    :param inputValues: numbers to be summed
    :return: total sum value
    """

    sum = 0
    for num in inputValues:
        sum += num
    return sum
