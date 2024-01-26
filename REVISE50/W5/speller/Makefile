speller:
	clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o speller.o speller.c
	clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o dictionary.o dictionary.c
	clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -o speller speller.o dictionary.o -lm


# make automates compilation of your code so that you don’t have to execute clang manually along with a whole bunch of switches.
# However, as your programs grow in size, make won’t be able to infer from context anymore how to compile your code;
# you’ll need to start telling make how to compile your program, particularly when they involve multiple source (i.e., .c) files,
# hence utilize a Makefile, a configuration file that tells make exactly what to do.
# The first line tells make to execute the subsequent lines whenever you yourself execute make speller (or just make).
# The second line tells make how to compile speller.c into machine code (i.e., speller.o).
# The third line tells make how to compile dictionary.c into machine code (i.e., dictionary.o).
# The fourth line tells make to link speller.o and dictionary.o in a file called speller.