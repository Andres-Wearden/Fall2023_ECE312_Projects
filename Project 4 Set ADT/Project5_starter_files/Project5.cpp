// Set <Project5.cpp>
// EE 312 Project 5 submission by
// <Andres Wearden>
// <aew3364>
// Slip days used: <1>
// Spring 2023

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */


int BinarySearch(int numbers[], int numbersSize, int key);
int findMin(const Set* set);
int findMax(const Set* set);
void makeSetEqualTo(Set* self, const Set* other);
/* done for you already */
void destroySet(Set* self) {
    free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
    self->len = 0;
    self->elements = nullptr;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
    self->elements = (int*) malloc(sizeof(int));
    self->elements[0] = x;
    self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
    self->elements = (int*) malloc(other->len * sizeof(int));
    for (int k = 0; k < other->len; k += 1) {
        self->elements[k] = other->elements[k];
    }
    self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
    if (self == other) { return; }

    destroySet(self);
    createCopySet(self, other);
}

/* return true if x is an element of self */

bool isMemberSet(const Set* self, int x) {
    if(BinarySearch(self->elements, self->len, x) == -1){
        return false;
    }else{
        return true;
    }
}

//The code below for binary search was copied from zybooks section 13.2
int BinarySearch(int numbers[], int numbersSize, int key) {
    int mid;
    int low;
    int high;

    low = 0;
    high = numbersSize - 1;

    while (high >= low) {
        mid = (high + low) / 2;
        if (numbers[mid] < key) {
            low = mid + 1;
        }
        else if (numbers[mid] > key) {
            high = mid - 1;
        }
        else {
            return mid;
        }
    }

    return -1; // not found
}


/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
    if(!isMemberSet(self, x)) {
        self->len++;
        self->elements = (int*)realloc(self->elements, self->len*sizeof(int));
        self->elements[self->len - 1] = x;
        for(int i = self->len - 1; i > 0; i--){
            if(self->elements[i - 1] > self->elements[i]){
                int temp = self->elements[i - 1];
                self->elements[i - 1] =  self->elements[i];
                self->elements[i] = temp;
            }
        }
    }
}

/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    if(isMemberSet(self, x)){
        int i = 0;
        while(self->elements[i] != x){
            i++;
        }
        while(i+1 != self->len){
            self->elements[i] = self->elements[i+1];
            i++;
        }
        self->len--;
    }
}

/* done for you already */
void displaySet(const Set* self) {
    int k;

    printf("{");

    if (self->len == 0) {
        printf("}");
    }
    else {
        for (k = 0; k < self->len; k += 1) {
            if (k < self->len - 1) {
                printf("%d,", self->elements[k]);
            } else {
                printf("%d}", self->elements[k]);
            }
        }
    }
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if(isEmptySet(self) && isEmptySet(other)){
        return true;
    }
    if(!isEmptySet(self)){
        if(self->len != other->len){
            return false;
        }else{
            for(int i = 0; i < self->len; i++){
                if(self->elements[i] != other->elements[i]){
                    return false;
                }
            }
            return true;
        }
    }else{
        return false;
    }
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    if(self->len <= other->len){
        if(isEmptySet(self)){
            return true;
        }
        if(isEmptySet(other)){
            return false;
        }
        int j = 0;
        for(int i = 0; (i < other->len) && (j < self->len); i++){
            if(self->elements[j] == other->elements[i]){
                j++;
            }
        }
        return (j == self->len);
    }else{
        return false;
    }
}

/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

int findMax(const Set* set){
    int max = set->elements[0];
    for(int i = 0; i < set->len; i++){
        if(max < set->elements[i]){
            max = set->elements[i];
        }
    }
    return max;
}

int findMin(const Set* set){
    int min = set->elements[0];
    for(int i = 0; i < set->len; i++){
        if(min > set->elements[i]){
            min = set->elements[i];
        }
    }
    return min;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
    int i = 0;
    int j = 0;
    int k = 0;
    while(i < self->len && j < other->len){
        if(self->elements[i] < other->elements[j]){
            i++;
        }else if(self->elements[i] > other->elements[j]){
            j++;
        }else if(self->elements[i] == other->elements[j]){
            self->elements[k] = self->elements[i];
            k++;
            i++;
            j++;
        }
    }
    self->len = k;
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
    if(!isEmptySet(self) && !isEmptySet(other)){
        int i = 0;
        int j = 0;
        int k = 0;
        int* elements = (int*)malloc(sizeof(int)*self->len);
        while((i < self->len) && (j < other->len)){
            if(self->elements[i] == other->elements[j]){
                i++;
                j++;
            }else if(self->elements[i] < other->elements[j]){
                elements[k] = self->elements[i];
                i++;
                k++;
            }else{
                j++;
            }
        }
        //add remaining elements from self into newSelf
        while(i < self->len){
            elements[k] = self->elements[i];
            k++;
            i++;
        }
        free(self->elements);
        self->elements = elements;
        self->len = k;
    }
}

void makeSetEqualTo(Set* self, const Set* other){
    for(int i = 0; i < other->len; i++){
        self->elements[i] = other->elements[i];
    }
    self->len = other->len;
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
    if(!isEmptySet(other)) {
        int newLength = self->len + other->len;
        int* elements = (int*)malloc(sizeof(int)*newLength);
        int i = 0;
        int j = 0;
        int k = 0;
        while ((i < self->len) && (j < other->len)) {
            if (self->elements[i] == other->elements[j]) {
                elements[k] = self->elements[i];
                i++;
                j++;
                k++;
            } else if (self->elements[i] < other->elements[j]) {
                elements[k] = self->elements[i];
                i++;
                k++;
            } else {
                elements[k] = other->elements[j];
                j++;
                k++;
            }
        }
        //add remaining elements from self into newSelf
        while(i < self->len){
            elements[k] = self->elements[i];
            k++;
            i++;
        }
        while(j < other->len){
            elements[k] = other->elements[j];
            k++;
            j++;
        }
        free(self->elements);
        self->elements = elements;
        self->len = k;
        self->elements = (int *)realloc(self->elements, self->len*sizeof(int));
    }
}
