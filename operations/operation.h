#ifndef OPERATION_H
#define OPERATION_H

#include <string>

using namespace std;

class Operation {
protected:
    string equation;

public:
    static Operation* buildFromEquation(string equation);

    inline string name() { return equation; }

    virtual float operate() = 0;
};

string fixArithmetic(string equation);
string infixToPostfix(string equation);
int orderOperators(char c);
bool isOperator(char c);


#endif
