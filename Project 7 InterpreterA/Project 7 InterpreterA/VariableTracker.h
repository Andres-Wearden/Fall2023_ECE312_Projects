// InterpreterA <Project8.cpp>
// ECE 312 Project 8 submission by
// <Andres Wearden>
// <aew3364>
// Slip days used: <1>
// Fall 2023
#include <map>
#include <iostream>
#include <string>
using namespace std;

#ifndef PROJECT8_STARTER_FILES_VARIABLETRACKER_H
#define PROJECT8_STARTER_FILES_VARIABLETRACKER_H


class VariableTracker {
        private:
        map<string, int> variables;

        public:
        ~VariableTracker();
        void addVariable(const string& key, int val);
        void updateValue(const string& key, int val);
        void setVariable(const string& key2, const string& key1);
        void print();
        int getVar(const string& key);
        int varExist(const string& key);
        void clear();
};


#endif //PROJECT8_STARTER_FILES_VARIABLETRACKER_H
