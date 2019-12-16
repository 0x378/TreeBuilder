/*
 * Tree Builder 9001
 *
 * Author: The Cat
 * Version: 2019.12.16
 */

#ifndef TREE_H
#define TREE_H

#include <ostream>
#include <sstream>
#include <string>

class Tree {
private:
    struct Node {
        int data;
        Node *left, *right;

        explicit Node() = delete;
        explicit Node(int);

        ~Node(){ delete left; delete right; }
    };

    Node *root;

    static void illegal();

    static std::string  toStringPreOrder(Node *);
    static std::string   toStringInOrder(Node *);
    static std::string toStringPostOrder(Node *);

    static Node *toNode(const std::string &);
    static Node *nodeFromInstructions(std::string &);

public:
    explicit Tree() : root(nullptr) {}
    explicit Tree(Node *root) : root(root) {}
    explicit Tree(const std::string &data) : Tree(toNode(data)) {}

    ~Tree(){ delete root; }

    static std::string nextWord(std::string &);
    static std::string getInstructions(const std::string &data);

    std::string toStringPreOrder()  { return  toStringPreOrder(root) + '\n'; }
    std::string toStringInOrder()   { return   toStringInOrder(root) + '\n'; }
    std::string toStringPostOrder() { return toStringPostOrder(root) + '\n'; }

    friend std::ostream &operator<<(std::ostream &, const Node *);
    friend std::ostream &operator<<(std::ostream &, const Tree &);
};

#endif
