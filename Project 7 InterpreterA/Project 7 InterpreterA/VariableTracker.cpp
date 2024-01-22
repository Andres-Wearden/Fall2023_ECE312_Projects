// InterpreterA <Project8.cpp>
// ECE 312 Project 8 submission by
// <Andres Wearden>
// <aew3364>
// Slip days used: <1>
// Fall 2023
#include "VariableTracker.h"

VariableTracker::~VariableTracker() { variables.clear(); }
void VariableTracker::print() {
    for (auto s : variables) {
        cout << "Variable " << s.first << ": " << s.second << endl;
    }
}
void VariableTracker::clear(){
    variables.clear();
}

void VariableTracker::addVariable(const string& key, int val){
    if(!variables.count(key)){
        variables[key] = val;
    }else{
        cout << "variable " << key <<  " incorrectly re-initialized"<< endl;
    }
}
void VariableTracker::updateValue(const string& key, int val){
    if(variables.count(key)){
        variables.at(key) = val;
    }else{
        cout << "variable " << key << " not declared"<< endl;
    }
}
int VariableTracker::getVar(const string& key){
    if(variables.count(key)){
        return variables.at(key);
    }else{
        cout << "error " << key << " does not exist"<< endl;
        return 0;
    }
}

int VariableTracker::varExist(const string& key){
    return variables.count(key);
}

void VariableTracker::setVariable(const string& key2, const string& key1){
    if(variables.count(key1)){
        variables[key2] = variables[key1];
    }else{
        cout << key1 << " cannot be set because it does not exist" << endl;
    }
}
