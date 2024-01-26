import cs50
# case sensitivity in packages

while (True):
    # capitalised True and False
    height = cs50.get_int("Height:")
    if (0 < height < 9):
        # actually don't need the brackets
        break

for i in range(1, (height+1)):
    for j in range(height-i):
        print(" ", end="")
    for k in range(i):
        print("#", end="")
    print()


"""
$ python mario.py
Height: 4
   #
  ##
 ###
####

To make things more interesting, first prompt the user with get_int for the half-pyramid’s height, a positive integer between 1 and 8, inclusive.
If the user fails to provide a positive integer no greater than 8, you should re-prompt for the same again.
Then, generate (with the help of print and one or more loops) the desired half-pyramid.
Take care to align the bottom-left corner of your half-pyramid with the left-hand edge of your terminal window.
"""