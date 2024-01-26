#include <stdio.h>
#include <stdlib.h>
#define CONST NAME_SIZE 8 //"000.JPG\0"

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *raw_in = fopen(argv[1], "r");

    // should check for NULL?

    unsigned char buffer [512];
    //CHECK allocated size is 512 bytes
    // printf("%lu bytes\n", sizeof(buffer)); //lu is unsigned long

    int num_image = 0;
    int num_buffer = 0; //for checking number of buffers read
    char *filename =  malloc(8); //why can't i use NAME_SIZE?
    //3digitint - creates 002 if 2 is int input. "filename" should have enough mem for entire string

    sprintf(filename, "%03i.jpg", num_image);
    // printf("filename: %s\n",filename); //CHECK: generated filename
    // creates the first jpg file
    FILE *img_out = fopen(filename, "w"); // if it's in IF section compiler doesn't recognise

    while (fread(buffer, 512, 1, raw_in))
    {
        // CHECK:track number of buffers read
        /*
        num_buffer++;
        printf(" \nBUFFERS of 512B READ:%d\n",num_buffer);
        */
        // CHECK: print HEX values to check
        /*
        for(int i = 0; i < 512 ; i++)
        {

            printf("%x ", buffer[i]);

        }
        */
        if ((buffer [0] == 0XFF) && (buffer [1] == 0XD8) && (buffer [2] == 0XFF) && ((buffer [3] & 0XF0) == 0XE0))
        {
            // CHECK: print
            // printf("%03i JPEGS FOUND \n", num_image);

            if (num_image == 0)
            {
                // CHECK: print
                // printf("writing num_image: %d\n",num_image);

                fwrite(buffer, 512, 1, img_out);
                num_image++;
                continue;
            }
            else
            {
                // CHECK
                // printf("NEW JPEG FOUND\n");

                // Close existing file
                fclose(img_out);
                // Update file name
                // printf("%03i JPEGS FOUND \n", num_image); DELETE
                sprintf(filename, "%03i.jpg", num_image);
                num_image++;

                // CHECK: Filename updated
                // printf("writing num_image: %d\n",num_image);
                // printf("filename: %s\n",filename);

                // Change pointer for imgout
                img_out = fopen(filename, "w");
            }
        }
        if (num_image == 0)
        {
            continue;
        }
        fwrite(buffer, 512, 1, img_out);
        // write current buffer to jpg if not new jpg
    }
    // close open files to close memory access
    fclose(raw_in);
    fclose(img_out);
    // free malloc memory
    free(filename);
}
/*
472 bytes in 1 blocks are still reachable in loss record 1 of 2: (file: recover.c, line: 14)
472 bytes in 1 blocks are still reachable in loss record 2 of 2: (file: recover.c, line: 79)

Use EOF?


void *malloc(size_t size) size − This is the size of the memory block, in bytes.


 FILEN *f = fopen(filename ,*r)


Digital cameras tend to store photographs contiguously on memory cards, whereby each photo is stored immediately after the previously taken photo. Accordingly, the start of a JPEG usually demarks the end of another. However, digital cameras often initialize cards with a FAT file system whose “block size” is 512 bytes (B). The implication is that these cameras only write to those cards in units of 512 B. A photo that’s 1 MB (i.e., 1,048,576 B) thus takes up 1048576 ÷ 512 = 2048 “blocks” on a memory card. But so does a photo that’s, say, one byte smaller (i.e., 1,048,575 B)! The wasted space on disk is called “slack space.” Forensic investigators often look at slack space for remnants of suspicious data.

Implement your program in a file called recover.c in a directory called recover.
Your program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs.
If your program is not executed with exactly one command-line argument, it should remind the user of correct usage, and main should return 1.
If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1.
The files you generate should each be named ###.jpg, where ### is a three-digit decimal number, starting with 000 for the first image and counting up.
Your program, if it uses malloc, must not leak any memory.
rather than read my memory card’s bytes one at a time, you can read 512 of them at a time into a buffer for efficiency’s sake. Thanks to FAT, you can trust that JPEGs’ signatures will be “block-aligned.” That is, you need only look for those signatures in a block’s first four bytes.
Realize, of course, that JPEGs can span contiguous blocks. Otherwise, no JPEG could be larger than 512 B. But the last byte of a JPEG might not fall at the very end of a block. Recall the possibility of slack space. But not to worry. Because this memory card was brand-new when I started snapping photos, odds are it’d been “zeroed” (i.e., filled with 0s) by the manufacturer, in which case any slack space will be filled with 0s. It’s okay if those trailing 0s end up in the JPEGs you recover; they should still be viewable.
But you should ultimately find that the image contains 50 JPEGs.

JPEG HEADER: 0XFF OXD8 OXFF OEX~
JPEGS in memory stored back to back
Each block is 512
Keep checking until jpeg header found, traverse memory until find new jpeg file
fread (data,size,number,inptr), where inptr is FILE * i.e. memory card
check if
buffer[0] = 0xff
buffer[1] = 0xd8
buffer[2] = 0xff
buffer[3] use boolean or bitwise arithmetic (buffer[3] & 0xf0) == 0xe0 i.e. look at first 4 bits of 8 bit and set remaining 45 bits to 0
Create a new file to write JPEG data

file name ###.jpg, starting with 000.jpg
sprintf(filename,"%03i.jpg",2);
FILE *img = fopen(filename,"w") - write to new file
fwrite(data,fize,number,outptr)

keep writing until end of  file
fread returns number of items of size "size" were read

open memory card
look for beginning of a jpeg
open a new jpeg file
write 512 to new jpeg until EOF

Open memory card
Repeat until end of card:
Read 512 bytes into a buffer
If start of new JPEG
If first JPEG
... start writing JPEGs
Else
... close file and open new file
Else
If already found JPEF
... keep writing
Close any remaining files

Keep in mind that you can open card.raw programmatically with fopen, as with the below, provided argv[1] exists.

FILE *file = fopen(argv[1], "r");
When executed, your program should recover every one of the JPEGs from card.raw, storing each as a separate file in your current working directory. Your program should number the files it outputs by naming each ###.jpg, where ### is three-digit decimal number from 000 on up. Befriend sprintf and note that sprintf stores a formatted string at a location in memory. Given the prescribed ###.jpg format for a JPEG’s filename, how many bytes should you allocate for that string? (Don’t forget the NUL character!)

You need not try to recover the JPEGs’ original names. To check whether the JPEGs your program spit out are correct, simply double-click and take a look! If each photo appears intact, your operation was likely a success!

Odds are, though, the JPEGs that the first draft of your code spits out won’t be correct. (If you open them up and don’t see anything, they’re probably not correct!) Execute the command below to delete all JPEGs in your current working directory.

$ rm *.jpg
If you’d rather not be prompted to confirm each deletion, execute the command below instead.

$ rm -f *.jpg
Just be careful with that -f switch, as it “forces” deletion without prompting you.

If you’d like to create a new type to store a byte of data, you can do so via the below, which defines a new type called BYTE to be a uint8_t (a type defined in stdint.h, representing an 8-bit unsigned integer).

typedef uint8_t BYTE;
Keep in mind, too, that you can read data from a file using fread, which will read data from a file into a location in memory. Per its manual page, fread returns the number of bytes that it has read, in which case it should either return 512 or 0, given that card.raw contains some number of 512-byte blocks. In order to read every block from card.raw, after opening it with fopen, it should suffice to use a loop like:

while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
{


}
That way, as soon as fread returns 0 (which is effectively false), your loop will end.

Testing




$ ./recover card.raw
*/
