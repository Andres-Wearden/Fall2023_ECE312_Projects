// InterpreterA <Project8.cpp>
// ECE 312 Project 8 submission by
// <Andres Wearden>
// <aew3364>
// Slip days used: <1>
// Fall 2023


#include "Parse.h"
#include "VariableTracker.h"
#include <iostream>
#include <string>
#include "ExpTree.h"
using namespace std;

enum operationType{
    OUTPUT,
    TEXT,
    SET,
    VAR,
    UNKNOWN
};




void run();
void setOperation(operationType currentOperation);
void pushNode(const string& nextString);
int getNum(const string& variable, int num);
int evaluatePrefix();
void performOperation(const string& key, int numExpr);

operationType currentInstruction = UNKNOWN;
vector<Node*> expr;
VariableTracker vt;

int main(){
    set_input("C:\\Users\\anesw\\Downloads\\Proj08\\Project 7 InterpreterA\\test1.blip");
    run();
    set_input("C:\\Users\\anesw\\Downloads\\Proj08\\Project 7 InterpreterA\\test2.blip");
    run();
    set_input("C:\\Users\\anesw\\Downloads\\Proj08\\Project 7 InterpreterA\\test3.blip");
    run();
    set_input("C:\\Users\\anesw\\Downloads\\Proj08\\Project 7 InterpreterA\\test4.blip");
    run();
    set_input("C:\\Users\\anesw\\Downloads\\Proj08\\Project 7 InterpreterA\\test5.blip");
    run();
    set_input("C:\\Users\\anesw\\Downloads\\Proj08\\Project 7 InterpreterA\\test6.blip");
    run();
    return 0;
}

void setOperation(operationType currentOperation){
    currentInstruction = currentOperation;
}

void pushNode(const string& nextString){
    Node* newNode;
    if(next_token_type == NUMBER || next_token_type == NAME){
        newNode = new Node(true, getNum(nextString, token_number_value), "\0");
    }else{
        newNode = new Node(false, 0, nextString);
    }
    expr.push_back(newNode);
}

void performOperation(const string& key, int numExpr){
    string next;
    switch(currentInstruction){
        case OUTPUT:
            cout << numExpr;
            break;
        case TEXT:
            read_next_token();
            next = next_token();
            cout << next;
            break;
        case SET:
            vt.updateValue(key, numExpr);
            break;
        case VAR:
            vt.addVariable(key, numExpr);
            break;
        case UNKNOWN:
            break;
        default:
            break;
    }
}

int getNum(const string& variable, int num){
    if(next_token_type == NAME){
        return vt.getVar(variable);
    }else{
        return num;
    }
}

int evaluatePrefix(){
    string nextString = next_token();
    if(next_token_type == NUMBER || next_token_type == SYMBOL || currentInstruction == OUTPUT){
        pushNode(nextString);
    }
    nextString = peek_next_token();
    while(!((nextString == "text") || (nextString == "output") || (nextString == "var") || (nextString == "set") || (nextString == "//"))){
        pushNode(nextString);
        read_next_token();
        nextString = peek_next_token();
    }
    ExpTree myTree(expr);
    expr.clear();
    int val = myTree.evaluate();
    return val;
}

void run(){
    string nextString;
    while(next_token_type != END){
        read_next_token();
        nextString = next_token();
        switch(next_token_type){
            case NUMBER:
                performOperation(nextString, evaluatePrefix());
                break;
            case SYMBOL:
                if(nextString == "~"){
                    performOperation(nextString, evaluatePrefix());
                }else if(nextString == "!"){
                    performOperation(nextString, evaluatePrefix());
                }else if(nextString == "//"){
                    skip_line();
                }else{
                    performOperation(nextString, evaluatePrefix());
                }
                break;
            case NAME:
                if(nextString == "text"){
                    setOperation(TEXT);
                    performOperation(nextString, 0);
                }else if(nextString == "output"){
                    setOperation(OUTPUT);
                }else if(nextString == "var"){
                    setOperation(VAR);
                    read_next_token();
                    nextString = next_token();
                    performOperation(nextString, evaluatePrefix());
                }else if(nextString == "set"){
                    setOperation(SET);
                    read_next_token();
                    nextString = next_token();
                    performOperation(nextString, evaluatePrefix());
                }else if (vt.varExist(nextString)){
                    performOperation(nextString, evaluatePrefix());
                }else{
                    setOperation(UNKNOWN);
                }
                break;
            case END:
                break;
            case INVALID:
                break;
            case KEYWORD:
                break;
            case STRING:
                break;
            default:
                break;
        }
    }
    next_token_type = INVALID;
    currentInstruction = UNKNOWN;
    vt.clear();
}