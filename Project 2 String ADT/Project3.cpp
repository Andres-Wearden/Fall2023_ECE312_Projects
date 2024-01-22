// String ADT <Project3.cpp>
// EE 312 Project 3 submission by
// Andres Wearden
// aew3364
// Slip days used: <0>
// Summer 2022
// Copy and paste this file at the top of all your submitted source code files.
// Do not turn this in by itself.


#include <assert.h>     //to provide assert()
#include <stdbool.h>    //to provide "bool" datatype (true or false)
#include <stdlib.h>     //dynamic allocation functions
#include <stdint.h>     //integer datatype with precise explicit width
#include <string.h>     //utility functions for string management
#include "UTString.h"
#include "assert.h"

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))
void appendSignature(UTString* s);
/*
 * Checks if a UTString is valid or not.
 */
bool isOurs(const UTString* s) {
    if (CHECK(s) == SIGNATURE) { return true; }
    else { return false; }
}
/*
 * Allocate a utstring on the heap.
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {
    UTString* utStringDup;
    utStringDup = (UTString*)(malloc(sizeof(UTString)));
    utStringDup->string = (char*)(malloc((strlen(src)*sizeof(char)) + 5));
    strcpy(utStringDup->string, src);
    utStringDup->length = strlen(src);
    utStringDup->capacity = utStringDup->length;
    appendSignature(utStringDup); // same as CHECK(s)
    return utStringDup;
}

/*
 * Returns the length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s){
    assert(isOurs(s));
    return s->length;
}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s.
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) {
    assert(isOurs(s));
    int i = 0;
    while((s->length < s->capacity) && (suffix[i] != '\0')){
        s->string[s->length] = suffix[i]; //appends letter to end of s string
        i++;
        s->length++;
    }
    s->string[s->length] = '\0';
    appendSignature(s);
    return s;
}

//will add the signature at the end of string s given its string pointer.
void appendSignature(UTString* s){
    *((int32_t *) (s->string + s->length + 1)) = SIGNATURE;
}
/*
 * Copy src into dst.
 *  dst must be a valid UTString.
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst.
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) {
    assert(isOurs(dst));
    int i = 0;
    while((i < dst->capacity) && (src[i] != '\0')){
        dst->string[i] = src[i];
        i++;
    }
    dst->length = i;
    dst->string[dst->length] = '\0';
    appendSignature(dst);
    return dst;
}

/*
 * Free all memory associated with the given UTString.
 */
void utstrfree(UTString* self) {
    assert(isOurs(self));
    free(self->string);
    free(self);
}

/*
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity,
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata.
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
    assert(isOurs(s));
    if(s->capacity >= new_capacity){
        return s;
    }
    s->string = (char*)realloc(s->string, (new_capacity + 5));
    s->capacity = new_capacity;
    appendSignature(s);
    return s;
}
