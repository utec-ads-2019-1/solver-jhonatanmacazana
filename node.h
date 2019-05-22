#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

class BSTree;


class Node {
private:
public:
    std::string data;
    Node *left;
    Node *right;

    Node(): data("") {left = right = nullptr;}
    Node(std::string data) : data(data){ left = right = nullptr; }

    friend class BSTree;

};



#endif
