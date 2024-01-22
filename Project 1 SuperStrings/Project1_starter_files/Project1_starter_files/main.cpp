#include <stdio.h> // declarations of standard input/output functions
#include <stdint.h> // declarations of standard integer types (e.g., int32_t)
#include <stdlib.h> // declarations of general functions in the standard library (e.g., abort, exit)
#include "Project1.cpp"

#define ONE_MB (1 << 20)
#define BUFFER_SIZE ONE_MB

char superstrings[BUFFER_SIZE]; // a large buffer to hold a dictionary (1MB)
char strings[BUFFER_SIZE]; // a large buffer to hold an strings (1MB)

void printSuperStrings(char target [], char candidates []);  // this is the function you write

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


void simpleTest(void) {
    printf("******* Starting Base Test #1 (simpleTest) *******\n");
    char superstrings[] = "bulldogx\nbulldog\nbulldo\nulldog\nxbullxdogxx\nbulsdf\nabuxllORdoxgM\nulld";
    char strings[] = "bulldog bulld";
    printSuperStrings(strings, superstrings); // should print: don
    printf("****DONE****\n");
}

void generalTest(void) {
    printf("\n\n******* Starting General Test #2 *******\n");
    readFile("strings1.txt", strings);
    readFile("superstrings1.txt", superstrings);
    printSuperStrings(strings, superstrings);
    printf("****DONE****\n");
}

/* you should also make your own tests! */
int main(void) {
    /* for starters, uncomment the following tests, one at a time */
    simpleTest();
    generalTest();
}
