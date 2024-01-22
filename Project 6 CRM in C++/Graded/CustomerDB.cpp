/*
 * Copy the contents of header.txt (filled out) and paste here
 */
#include <iostream>
#include <cassert>
#include "UTString.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(UTString name) { // done, please do not edit
    this->bottles = 0;
    this->rattles = 0;
    this->diapers = 0;
    this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

int CustomerDB::size(void) { // done, please do not edit
    return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
    delete[] this->data;
}



void CustomerDB::clear(void) { // done, please do not edit
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
    assert(k >= 0 && k < this->length);
    return this->data[k];
}

Customer& CustomerDB::operator[](UTString name) {
    Customer newCustomer(name);
    for(int i = 0; i < this->length; i++){
        if(this->data[i].name == name){
            return this->data[i];
        }
    }
    if(this->length == this->capacity){
        this->capacity *= 2;
        Customer* newArr = new Customer[this->capacity]; //newArr contains pointer to new Array with updated size
        for(int i = 0; i < this->length; i++){
            newArr[i] = this->data[i];
        }
        delete[] this->data;
        this->data = newArr;
    }
    //adds customer to array
    this->data[this->length] = newCustomer;
    this->length++;
    return this->data[this->length - 1];
}

bool CustomerDB::isMember(UTString name) {
    for(int i = 0; i < this->length; i++){
        if(this->data[i].name == name){
            return true;
        }
    }
    return false;
}
