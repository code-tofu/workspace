/*
S10 Strings

also known as character arrays i.e array of char variables
take note of using single vs double quotation mark for char variable. single quotes are for characters
string constant of string literally uses double quotes. can include spaces and special characters
using escape characters for " or \ e.g. \" or \\.  the escape character is not started in memory.
printf uses string constants
character arrays end in\0 null terminators. Hence the length of the string array is always one longer than the length of the string of characters
do not confuse NULL with /0 null characters

Creating a string:
there is no explicit data type for string, hence there are no special operators usable on strings - use the standard library with string functions instead
strings in C are an array with type char, stored in adjacent memory cells, one char per cell
remember that the last cell has to be the null terminator hence an array of size 20 can only store 19 characters. in the absence of an array sized, the compiler automatically computers the necessary size of the array. if the specified size is too small, the compiler will not raise any errors. leave the array size empty
initialise a string via char word [] = (‘H’, ’e’, 
‘l’, ’l’, ’o’); or use double quotes char word[6] = {"Hello"}; ->test without size specification?
remember character arrays are zero indexed
you can initialise part of array to a string although the memory is still allocated for the full array size

you cannot directly assign to an array variables, you need to assign to element indices. use strcopy

scanf only reads until a space character 
use fgets to read regardless of spaces

you cannot use equality operator for structures or arrays, either comparing element by element or using strcompr. you can compare characters eg. ==  /0
to find length of string, user strlen

defining CONST strings - more meaningful and efficient if the value if used many times, or if values don't need to change (compare to a variable)
note that define has no semicolon as it is not a statement
define values don't have any scope - tey are pre-processor compiled so it exists eveywhere
#define CONSTSTRING "constant string"
#define CONSTCHAR 'x'
const int MONTHS = 12
const is better because it allows better control over the usage and allows you to declare the type

string.h functions:
strlen, strcpy, strncpy
strcat,strncat, strcmp, strncmp

len is returned as size_t variable (integer, use %d to display)
you cannot assign array in C hence /you cannot assign stings e.g.
 char s[100]; //declare
 s = "hello"; //initialize does not work
you can use strcpy to define

strn includes an additional argument which is the length to copy. i.e. use the length of thje destination array to prevent buffer overflows
sizeof()-1?

strcmp gives a value that is equal or less than greater than
you can only use strcmp on strings i.e. "A" not  'A'. the value is either the length or the ASCII value?
if compares until it finds corresponding characters that differ
strncmp compares sttring until they differ unitl the length argument e.g. prefix


*/