import cs50

while (True):
    height = cs50.get_int("Height:")
    if (0 < height < 9):
        break

for i in range(1, (height+1)):
    for j in range(height-i):
        print(" ", end="")
    for k in range(i):
        print("#", end="")
    print("  ", end="")
    for k in range(i):
        print("#", end="")
    print()


"""
$ python mario.py
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####

To make things more interesting, first prompt the user with get_int for the half-pyramid’s height, a positive integer between 1 and 8, inclusive. (The height of the half-pyramids pictured above happens to be 4, the width of each half-pyramid 4, with a gap of size 2 separating them).
If the user fails to provide a positive integer no greater than 8, you should re-prompt for the same again.
Then, generate (with the help of print and one or more loops) the desired half-pyramids.
Take care to align the bottom-left corner of your pyramid with the left-hand edge of your terminal window, and ensure that there are two spaces between the two pyramids, and that there are no additional spaces after the last set of hashes on each row.
"""