/*
 * Tree Builder 9001
 *
 * Author: The Cat
 * Version: 2019.12.16
 */

#include <iostream>
#include "Tree.h"

std::string Tree::nextWord(std::string &data) {
    int start, end, length = data.length();

    for (start = 0; start < length && data.at(start) == ' '; start++);
    for (end = start; end < length && data.at(end) != ' '; end++);

    std::string word = data.substr(start, end - start);
    data = data.substr(end);
    return word;
}

std::string Tree::getInstructions(const std::string &data) {
    std::string output;
    int pCount = 0; // Parentheses counter
    bool enableSpace = false;

    for (char element : data) {
        switch (element) {
            case ',':
            case ' ':
                if (enableSpace) output += ' ';
                enableSpace = false;
                break;
            case '(':
            case '{':
            case '[':
                if (enableSpace) output += ' ';
                output += "( ";
                pCount++;
                enableSpace = false;
                break;
            case ')':
            case '}':
            case ']':
                if (enableSpace) output += ' ';
                output += ")";
                pCount--;
                enableSpace = true;
                break;
            default :
                output += element;
                enableSpace = true;
        }

        // In the case of too many closing parentheses:
        if (pCount < 0) return "INVALID";
    }

    // Not enough closing parentheses:
    if (pCount > 0) return "INVALID";

    return output;
}

Tree::Node *Tree::nodeFromInstructions(std::string &instructions) {
    std::string word = nextWord(instructions);

    if (word.empty()) return nullptr;

    char c = word.at(0);
    if (c == ')') illegal();
    if (c == 'n' || c == 'N') return nullptr;

    int value;
    if (!(std::stringstream(word) >> value)) illegal();
    Node *ptr = new Node(value);

    word = nextWord(instructions);

    if (!word.empty() && word.at(0) == '(') {
        ptr->left = nodeFromInstructions(instructions);
        ptr->right = nodeFromInstructions(instructions);

        word = nextWord(instructions);

        if (word.at(0) != ')') {
            delete ptr;
            illegal();
        }
    } else {
        instructions = word + instructions;
    }

    return ptr;
}

Tree::Node *Tree::toNode(const std::string &data) {
    std::string instructions = getInstructions(data);

    if (instructions == "INVALID") {
        illegal();
    }

    Node *ptr = nodeFromInstructions(instructions);

    if (!nextWord(instructions).empty()) {
        delete ptr;
        illegal();
    }

    return ptr;
}

void Tree::illegal() {
    std::cout << "[ERROR] Illegal instructions.\n\n\tPROGRAM ABORTED\n\n";
    exit(-777);
}
