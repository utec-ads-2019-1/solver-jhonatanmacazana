#include "operation.h"
#include "../bstree.h"
#include <stack>
#include <cstring>

stack<Node* > stackNode;

Operation* Operation::buildFromEquation(string equation) {

    auto solver = new BSTree();
    solver->equation = equation;

    string fixedEquation = fixArithmetic(equation);
    string ordEquation = infixToPostfix(fixedEquation);

    Node *t, *t1, *t2;

    for (size_t i = 0; i < ordEquation.size(); ++i)
    {
        if(!isOperator(ordEquation[i]))
        {
            string tempStr(1, ordEquation[i]);
            t = new Node(tempStr);
            stackNode.push(t);
        }
        else
        {
            string tempStr(1, ordEquation[i]);
            t = new Node(tempStr);

            t1 = stackNode.top();
            stackNode.pop();
            t2 = stackNode.top();
            stackNode.pop();

            t->right = t1;
            t->left = t2;

            stackNode.push(t);
        }
    }

    t = stackNode.top();
    stackNode.pop();

    solver->insert(t);

    return solver;
}

string fixArithmetic(string equation)
{
    string output;
    uint8_t flag = 0, minus = 0;
    for(int i = 0; i < equation.size(); i++)
    {
        switch(flag)
        {
            case 1:     // If prev value was '+'
                if (equation[i] == '-') minus++;
                else if (equation[i] != '+') {
                    if (minus % 2 == 0) output += '+';
                    else output += '-';

                    output += equation[i];
                    minus = 0;
                    flag = 0;
                }
                break;

            default:
                if (equation[i] == '+' || equation[i] == '-') {
                    flag = 1;
                    if (equation[i] == '-') minus++;
                } else
                    output += equation[i];

                break;
        }
    }

    return output;
}


string infixToPostfix(string equation)
{
    std::stack<char> eqStack;
    eqStack.push('N');
    string output;

    for(int i = 0; i < equation.size(); i++)
    {
        if((equation[i] >= 'a' && equation[i] <= 'z')||(equation[i] >= '0' && equation[i] <= '9'))
            output += equation[i];

        else if(equation[i] == '(')
            eqStack.push('(');

        else if(equation[i] == ')')
        {
            while(eqStack.top() != 'N' && eqStack.top() != '(')
            {
                char c = eqStack.top();
                eqStack.pop();
                output += c;
            }
            if(eqStack.top() == '(')
            {
                char c = eqStack.top();
                eqStack.pop();
            }
        }

        else
        {
            while(eqStack.top() != 'N' && orderOperators(equation[i]) <= orderOperators(eqStack.top()))
            {
                char c = eqStack.top();
                eqStack.pop();
                output += c;
            }
            eqStack.push(equation[i]);
        }
    }

    while(eqStack.top() != 'N')
    {
        char c = eqStack.top();
        eqStack.pop();
        output += c;
    }

    return output;
}

int orderOperators(char c)
{
    if(c == '^')
        return 3;
    else if(c == '*' || c == '/')
        return 2;
    else if(c == '+' || c == '-')
        return 1;
    else
        return -1;
}

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

