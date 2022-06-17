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
use fgets


*/