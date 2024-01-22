// SuperStrings <Project1.cpp>
// EE 312 Project 1 submission by
// Andres Wearden
// aew3364
// Slip days used: <0>
// Spring 2023
// Copy-paste contents of this file at the top of every .c or .h file that you write or modify.





#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types

/*
All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)

You must write this function (printSuperStrings). Do not change the way the function is declared (i.e., it has
exactly two parameters, each parameter is a standard (mundane) C string (see Instruction).
*/

int wordLength(const char array[]);
int isSuperString(char targets[], char candidates[]);
char* movePointerToLetter(char string[]);
void printWord(char word[]);
char* goToNextWord(char word[]);

void printSuperStrings(char targets [], char candidates []) {
    targets = movePointerToLetter(targets); //move pointers to first letter in strings
    candidates = movePointerToLetter(candidates);
    char* initialCandidatesPointer = candidates; //save location of first letter of superstring words
    while(*targets != '\0') {
        while (*candidates != '\0') {
            if (isSuperString(targets, candidates)) {
                printWord(candidates); //print word if it's a super string
                candidates = goToNextWord(candidates);
            } else {
                candidates = goToNextWord(candidates); //go to next word to check if it's a superstring of the target words.
            }
        }
        candidates = initialCandidatesPointer; // reset candidates pointer back to beginning of superstring list
        targets = goToNextWord(targets); //analyze next word in targets
    }
}

//gets string pointer as input then returns size of sequence of letters before
// any whitespaces are encountered
int wordLength(const char array[]){
    int i = 0;
    while((array[i] != ' ') && (array[i] != '\t') && (array[i] != '\n') && (array[i] != '\r') && (array[i] != '\v') && (array[i] != '\f') && (array[i] != '\0')){
        i++;
    }
    return i;
}

//checks to see if candidates is superstring of targets, returns 0 if not,
// returns 1 if it is a superstring
int isSuperString(char targets[], char candidates[]){
    int j = 0;
    for(int i = 0; i < wordLength(candidates); i++){
        if(targets[j] == candidates[i]){
            j++;
        }
    }
    return (j == wordLength(targets));
}

//will move pointer to the start of a word, returns the pointer to that letter.
char* movePointerToLetter(char string[]){
    char* ch = string;
    while(*ch == ' ' || *ch == '\t' || *ch == '\n' || *ch == '\r' || *ch == '\v' || *ch == '\f'){
        ch++;
    }
    return ch;
}

//As long as there is no whitespace, function will print the following word.
void printWord(char word[]){
    for(int i = 0; i < wordLength(word); i++){
        printf("%c", word[i]);
    }
    printf("\n");
}

//returns pointer to first letter of the next word to analyze, if there is no next word
//returns pointer to '\0'
char* goToNextWord(char word[]){
    int i = wordLength(word);
    if(word[i] == '\0'){
        return &word[i];
    }else{
        return movePointerToLetter(&word[i]);
    }
}






