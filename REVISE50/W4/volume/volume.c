// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE]; //since header is 44 bytes as this is a 8bit int array
    uint8_t *header_start = &header[0];
    fread(header_start, 1, HEADER_SIZE, input); // fread(<buffer>, <size_in_bytes>, <qty>, <file pointer>);

    // Check Print Header
    for (int i = 0; i < HEADER_SIZE; i++)
    {
        printf("%u", header[i]);
    }

    fwrite(header_start, 1, HEADER_SIZE, output);

    // Read samples from input file and write updated data to output file
    int16_t buffer; //initialise buffer address of type int16_t

    //fread returns 1 per read (number of bytes read). once itis unable to read, i.e. EOF, condition is zero
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}


/*
WAV files store audio as a sequence of “samples”: numbers that represent the value of some audio signal at a particular point in time. WAV files begin with a 44-byte “header” that contains information about the file itself, including the size of the file, the number of samples per second, and the size of each sample. After the header, the WAV file contains a sequence of samples, each a single 2-byte (16-bit) integer representing the audio signal at a particular point in time.
Scaling each sample value by a given factor has the effect of changing the volume of the audio. Multiplying each sample value by 2.0, for example, will have the effect of doubling the volume of the origin audio. Multiplying each sample by 0.5, meanwhile, will have the effect of cutting the volume in half.
Inside a header file called stdint.h are the declarations of a number of other types that allow us to very precisely define the size (in bits) and sign (signed or unsigned) of an integer. Two types in particular will be useful to us in this lab.
- uint8_t is a type that stores an 8-bit unsigned (i.e., not negative) integer. We can treat each byte of a WAV file’s header as a uint8_t value.
- int16_t is a type that stores a 16-bit signed (i.e., positive or negative) integer. We can treat each sample of audio in a WAV file as an int16_t value.
The program accepts three command-line arguments: input represents the name of the original audio file, output represents the name of the new audio file that should be generated, and factor is the amount by which the volume of the original audio file should be scaled.
For example, if factor is 2.0, then your program should double the volume of the audio file in input and save the newly generated audio file in output.
Your program should first read the header from the input file and write the header to the output file. Recall that this header is always exactly 44 bytes long.
Note that volume.c already defines a variable for you called HEADER_SIZE, equal to the number of bytes in the header.
Your program should then read the rest of the data from the WAV file, one 16-bit (2-byte) sample at a time. Your program should multiply each sample by the factor and write the new sample to the output file.
You may assume that the WAV file will use 16-bit signed values as samples. In practice, WAV files can have varying numbers of bits per sample, but we’ll assume 16-bit samples for this lab.
Your program, if it uses malloc, must not leak any memory.
You’ll likely want to create an array of bytes to store the data from the WAV file header that you’ll read from the input file. Using the uint8_t type to represent a byte, you can create an array of n bytes for your header with syntax like
uint8_t header[n];
replacing n with the number of bytes. You can then use header as an argument to fread or fwrite to read into or write from the header.
You’ll likely want to create a “buffer” in which to store audio samples that you read from the WAV file. Using the int16_t type to store an audio sample, you can create a buffer variable with syntax like
int16_t buffer;
You can then use &buffer as an argument to fread or fwrite to read into or write from the buffer. (Recall that the & operator is used to get the address of the variable.)
You may find the documentation for fread and fwrite helpful here.
In particular, note that both functions accept the following arguments:
ptr: a pointer to the location in memory to store data (when reading from a file) or from which to write data (when writing data to a file)
size: the number of bytes in an item of data
nmemb: the number of items of data (each of size bytes) to read or write
stream: the file pointer to be read from or written to
Per its documentation, fread will return the number of items of data successfully read. You may find this useful to check for when you’ve reached the end of the file!
*/

