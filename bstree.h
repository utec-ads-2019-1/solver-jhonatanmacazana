#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "operations/operation.h"

#include <stdlib.h>
#include <math.h>

class BSTree: public Operation {
private:
    Node *root;

    float getValue(Node* node)
    {
        if(!node)
            return 0;

        if(!node->left && !node->right)
            return strtof(node->data.c_str(), 0);

        float left_operation = getValue(node->left);
        float right_operation = getValue(node->right);

        if(node->data == "+")
            return left_operation + right_operation;

        if(node->data == "-")
            return left_operation - right_operation;

        if(node->data == "*")
            return left_operation * right_operation;

        if(node->data == "/")
            return left_operation / right_operation;

        return pow(left_operation,right_operation);
    }

public:
    BSTree() : root(nullptr) {};

    bool insert(Node *node)
    {
        this -> root = node;
    }

    float operate()
    {
        return getValue(this->root);
    }

    ~BSTree() {
        // TODO
    }
};

#endif
