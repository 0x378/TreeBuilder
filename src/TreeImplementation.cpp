/*
 * Tree Builder 9001
 *
 * Author: The Cat
 * Version: 2019.12.16
 */

#include "Tree.h"

Tree::Node::Node(int data) : data(data) {
    left = nullptr;
    right = nullptr;
}

std::string Tree::toStringPreOrder(Node *ptr) {
    std::string output;

    if (ptr == nullptr) return output;

    output += std::to_string(ptr->data) + ' ';
    output += toStringPreOrder(ptr->left);
    output += toStringPreOrder(ptr->right);

    return output;
}

std::string Tree::toStringInOrder(Node *ptr) {
    std::string output;

    if (ptr == nullptr) return output;

    output += toStringInOrder(ptr->left);
    output += std::to_string(ptr->data) + ' ';
    output += toStringInOrder(ptr->right);

    return output;
}

std::string Tree::toStringPostOrder(Node *ptr) {
    std::string output;

    if (ptr == nullptr) return output;

    output += toStringPostOrder(ptr->left);
    output += toStringPostOrder(ptr->right);
    output += std::to_string(ptr->data) + ' ';

    return output;
}

std::ostream &operator<<(std::ostream &stream, const Tree &tree) {
    stream << tree.root << '\n';
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Tree::Node *ptr) {
    if (ptr == nullptr) return stream;

    stream << ptr->data;

    if (ptr->left != nullptr || ptr->right != nullptr) {
        stream << "(";

        if (ptr->left == nullptr)stream << 'n';
        else stream << ptr->left;

        stream << ",";

        if (ptr->right == nullptr) stream << 'n';
        else stream << ptr->right;

        stream << ")";
    }

    return stream;
}
