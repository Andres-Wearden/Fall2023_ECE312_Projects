// CRM <Project4.cpp>
// EE 312 Project 4 submission by
// Andres Wearden
// aew3364
// Slip days used: <0>
// Fall 2022
// Copy-Paste the above lines at the top of your submitted files.

#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;

Customer Storage;
String bottles;
String diapers;
String rattles;
/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */

int customerLocate(String name);
void updateStorageAndCustomerPurchases(String itemPurchased, int numPurchased, int i);
void createNewCustomer(String name);
int findMax(String item);
bool enoughStock(String item, int numPurchased);
int inventoryStock(String item);
void errorMessage(String name, String itemPurchased);
void addInventory(String itemType, int amountAdded);
int getCustomerPurchase(String itemType, int i);
void printMaxPurchases();
void printMaxItem(String itemType, int maxIndex);
void addCustomerPurchase(String itemPurchased, int numPurchased, int i);
void cleanUpCustomers();
void destroyCmpStr();
void createCmpStr();
/* clear the inventory and reset the customer database to empty */
void reset(void) {
    for(int i = 0; i < MAX_CUSTOMERS; i++){
        customers[i].bottles = 0;
        customers[i].diapers = 0;
        customers[i].rattles = 0;
    }
    Storage.bottles = 0;
    Storage.diapers = 0;
    Storage.rattles = 0;
    cleanUpCustomers();
    num_customers = 0;
}

void cleanUpCustomers(){
    for(int i = 0; i < num_customers; i++){
        StringDestroy(&customers[i].name);
    }
}

void processSummarize() {
    createCmpStr();
    printf("There are %d Bottles %d Diapers and %d Rattles in inventory\n", Storage.bottles, Storage.diapers, Storage.rattles);
    printf("we have had a total of %d different customers\n", num_customers);
    printMaxPurchases();
    destroyCmpStr();
}

void printMaxPurchases(){
    int customerMaxBottles = findMax(bottles);
    int customerMaxDiapers = findMax(diapers);
    int customerMaxRattles = findMax(rattles);
    printMaxItem(bottles, customerMaxBottles);
    printMaxItem(diapers, customerMaxDiapers);
    printMaxItem(rattles, customerMaxRattles);
}

void printMaxItem(String itemType, int maxIndex){
    if(StringIsEqualTo(&itemType, &bottles)){
        if(maxIndex == -1){
            printf("no one has purchased any Bottles\n");
        }else{
            StringPrint(&customers[maxIndex].name);
            printf(" has purchased the most Bottles (%d)\n", customers[maxIndex].bottles);
        }
    }
    else if(StringIsEqualTo(&itemType, &rattles)){
        if(maxIndex == -1){
            printf("no one has purchased any Rattles\n");
        }else{
            StringPrint(&customers[maxIndex].name);
            printf(" has purchased the most Rattles (%d)\n", customers[maxIndex].rattles);
        }
    }else{
        if(maxIndex == -1){
            printf("no one has purchased any Diapers\n");
        }else{
            StringPrint(&customers[maxIndex].name);
            printf(" has purchased the most Diapers (%d)\n", customers[maxIndex].diapers);
        }
    }
}

int findMax(String item) {
    int max = 0;
    int maxIndex = 0;
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        if (getCustomerPurchase(item, i) > max) {
            max = getCustomerPurchase(item, i);
            maxIndex = i;
        }
    }
    if (max == 0) {
        return -1;
    } else {
        return maxIndex;
    }
}

int getCustomerPurchase(String itemType, int i){
    if(StringIsEqualTo(&itemType, &bottles)){
        return customers[i].bottles;
    }
    else if(StringIsEqualTo(&itemType, &rattles)){
        return customers[i].rattles;
    }else{
        return customers[i].diapers;
    }
}


void processPurchase() {
    String name{};
    readString(&name);
    String itemPurchased{};
    readString(&itemPurchased);
    int numPurchased;
    readNum(&numPurchased);
    createCmpStr();
    int indexOfCustomer = customerLocate(name);
    if(numPurchased > 0){
        if(enoughStock(itemPurchased, numPurchased)){
            if(indexOfCustomer == -1){
                indexOfCustomer = num_customers;
                createNewCustomer(name);
            }
            updateStorageAndCustomerPurchases(itemPurchased, numPurchased, indexOfCustomer);
        }else{
            errorMessage(name, itemPurchased);
        }
    }
    StringDestroy(&name);
    StringDestroy(&itemPurchased);
    destroyCmpStr();
}

void errorMessage(String name, String itemPurchased){
    printf("Sorry ");
    StringPrint(&name);
    printf(", we only have %d ", inventoryStock(itemPurchased));
    StringPrint(&itemPurchased);
    printf("\n");
}

int inventoryStock(String item){
    if(StringIsEqualTo(&item, &bottles)){
        return Storage.bottles;
    }
    else if(StringIsEqualTo(&item, &rattles)){
        return Storage.rattles;
    }else{
        return Storage.diapers;
    }
}



//returns 1 if item purchased is less than what's in stock, return 0 otherwise.
bool enoughStock(String item, int numPurchased){
    return (inventoryStock(item) >= numPurchased);
}

//helper function which takes in name of customer and returns index of customer if it does exist and -1
//if customer does not exist
int customerLocate(String name){
    for(int i = 0; i < num_customers; i++){
        if(StringIsEqualTo(&(customers[i].name), &name)){
            return i;
        }
    }
    return -1;
}

//will update the items purchased by a customer a storage count
//takes in index of customer, what item they purchased, and how much they purchased
void updateStorageAndCustomerPurchases(String itemPurchased, int numPurchased, int i){
    addCustomerPurchase(itemPurchased, numPurchased, i);
    addInventory(itemPurchased, numPurchased*(-1));
}

void addCustomerPurchase(String itemPurchased, int numPurchased, int i){
    if(StringIsEqualTo(&itemPurchased, &bottles)){
        customers[i].bottles += numPurchased;
    }
    else if(StringIsEqualTo(&itemPurchased, &rattles)){
        customers[i].rattles += numPurchased;
    }
    else{
        customers[i].diapers += numPurchased;
    }
}



//will write new name and reset purchase count in customers array
void createNewCustomer(String name){
    customers[num_customers].name = StringDup(&name);
    customers[num_customers].bottles = 0;
    customers[num_customers].diapers = 0;
    customers[num_customers].rattles = 0;
    num_customers++;
}

void processInventory() {
    String itemType{};
    int amountAdded;
    readString(&itemType);
    readNum(&amountAdded);
    createCmpStr();
    addInventory(itemType, amountAdded);
    StringDestroy(&itemType);
    destroyCmpStr();
}

void addInventory(String itemType, int amountAdded){
    if(StringIsEqualTo(&itemType, &bottles)){
        Storage.bottles += amountAdded;
        if(Storage.bottles < 0){
            Storage.bottles = 0;
        }
    }
    else if(StringIsEqualTo(&itemType, &rattles)){
        Storage.rattles += amountAdded;
        if(Storage.rattles < 0){
            Storage.rattles = 0;
        }
    }
    else{
        Storage.diapers += amountAdded;
        if(Storage.diapers < 0){
            Storage.diapers = 0;
        }
    }
}

void createCmpStr(){
    bottles = StringCreate("Bottles");
    diapers = StringCreate("Diapers");
    rattles = StringCreate("Rattles");
}
void destroyCmpStr(){
    StringDestroy(&bottles);
    StringDestroy(&diapers);
    StringDestroy(&rattles);
}

