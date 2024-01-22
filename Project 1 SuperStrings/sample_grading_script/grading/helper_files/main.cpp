//
// Created by vn2783 on 6/1/20.
//

#include <stdio.h> // declarations of standard input/output functions
#include <stdint.h> // declarations of standard integer types (e.g., int32_t)
#include <stdlib.h> // declarations of general functions in the standard library (e.g., abort, exit)


#define ONE_MB (1 << 20)
#define BUFFER_SIZE ONE_MB

char superstrings[BUFFER_SIZE]; // a large buffer to hold a dictionary (1MB)
char strings[BUFFER_SIZE]; // a large buffer to hold an strings (1MB)

void printSuperStrings(char strings [], char superstrings []);  // this is the function you write

/*
 * Read a .txt file into one of the two buffers
 * this function does NOT confirm that the file is correctly formatted
 */
void readFile(const char file_name[], char buffer[]) {
    FILE* file = fopen(file_name, "r");
    if (file == 0) {
        printf("unable to open file \"%s\"\n", file_name);
        abort();
    }

    /* clear (set to zeros) the buffer */
    for (uint32_t k = 0; k < BUFFER_SIZE; k += 1) {
        buffer[k] = 0;
    }

    /* read the file (this is a binary read, which is OK) */
    uint32_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
    buffer[bytes_read] = 0;
}


void generalTest(void) {
    printf("\n\n******* Starting General Test *******\n");
    readFile("strings.txt", strings);
    readFile("superstrings.txt", superstrings);
    printSuperStrings(strings, superstrings);
    printf("****DONE****\n");
}

/* you should also make your own tests! */
int main(void) {
    generalTest();
}
