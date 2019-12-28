/*
 * Tree Builder 9001
 *
 * Author: The Cat
 * Version: 2019.12.28
 */

#include <iostream>
#include "Tree.h"

/*
 * nextWord(string) is a helper method for obtaining the next set of
 * non-space characters in between spaces. Once identified, these characters
 * are removed from the source data string, then returned on their own as a
 * separate string.
 */
std::string Tree::nextWord(std::string &data) {
    int start, end, length = data.length();

    // The start integer identifies the index of the first non-space character
    for (start = 0; start < length && data.at(start) == ' '; start++);

    // The end integer determines the index of the first space after the end
    // of the first word in the data string.
    for (end = start; end < length && data.at(end) != ' '; end++);

    // Obtain the first word from the data string using substr
    std::string word = data.substr(start, end - start);

    // Remove the word from the data string by using substr upon the remainder.
    data = data.substr(end);
    return word;
}

/*
 * getInstructions(string) generates and returns a copy of the source data
 * string, but with additional spaces added to separate the parentheses from
 * the data. This makes it easier for later processing of the tree-building
 * instructions word by word.
 *
 * All brackets and braces are converted to regular parentheses, so that the
 * tree builder will have less cases to identify.
 *
 * All commas are converted into spaces.
 *
 * A count is kept for the number of parentheses opened, and decremented
 * every time that the parentheses are closed. If at any point this count
 * drops below zero, the instructions have too many closing parentheses, so
 * the method returns "INVALID" instead of the data.
 *
 * If the count is nonzero after the string is processed, then "INVALID" is
 * returned because there are parentheses which have not been closed.
 *
 * The enableSpace boolean keeps track of whether it is necessary to insert a
 * space before the next character in the output string. If the last character
 * inserted was a space, this boolean is set to false, so that no additional
 * spaces are inserted until the next non-space character is inserted.
 */
std::string Tree::getInstructions(const std::string &data) {
    std::string output;
    int pCount = 0; // Parentheses counter
    bool enableSpace = false;

    for (char element : data) { // For each character in the data string...
        switch (element) { // Detect the character type
            case ',': // No break here, because the comma is treated as a space
            case ' ':
                if (enableSpace) output += ' ';
                enableSpace = false;
                break;
            case '(':
            case '{': // Brackets and braces are also treated as parentheses
            case '[':
                if (enableSpace) output += ' ';
                output += "( ";
                pCount++; // Increment the quantity of parentheses opened
                enableSpace = false;
                break;
            case ')':
            case '}':
            case ']':
                if (enableSpace) output += ' ';
                output += ")";
                pCount--; // Decrement the quantity of open parentheses
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

/*
 * nodeFromInstructions(string) Assembles the tree nodes recursively from the
 * instructions string.
 *
 * Upon encountering each open parenthesis, two recursive calls are made to
 * generate the left and right nodes. A closing parentheses allows exiting the
 * current call, as the current node has been fully constructed.
 *
 * If there is no opening parenthesis, the left and right nodes are both set
 * to null.
 */
Tree::Node *Tree::nodeFromInstructions(std::string &instructions) {
    // Obtain the next word from the instructions string
    std::string word = nextWord(instructions);

    // Base case: If the instructions were empty, then return nullptr
    if (word.empty()) return nullptr;

    // Obtain the first character of the current word
    char c = word.at(0);

    // Abort the program if parentheses are closed prematurely.
    if (c == ')') illegal();

    // Other base case: If the instructions state to generate a null left or
    // right node, return nullptr.
    if (c == 'n' || c == 'N') return nullptr;

    int value;

    // If an integer value cannot be obtained for the current node, abort.
    if (!(std::stringstream(word) >> value)) illegal();

    // Generate a new Node with the integer value obtained from the word.
    Node *ptr = new Node(value);

    // Obtain the next word from the instructions string
    word = nextWord(instructions);

    // If the next word was an opening parenthesis, generate the left and
    // right Node by making two recursive calls. Otherwise, place the word
    // back into the instructions string and return the current Node without
    // making a left or right Node.

    if (!word.empty() && word.at(0) == '(') {
        ptr->left = nodeFromInstructions(instructions);
        ptr->right = nodeFromInstructions(instructions);

        // Obtain the next word from the instructions string
        word = nextWord(instructions);

        // Verify that the parentheses are closed now that the left and right
        // nodes have been generated. Abort the program if some other
        // character is encountered instead.
        if (word.at(0) != ')') {
            delete ptr;
            illegal();
        }
    } else {
        // Place the word back into the instructions string
        instructions = word + instructions;
    }

    return ptr;
}

/*
 * toNode(string) generates the root Node for a tree from the instructions of
 * the input data string.
 */
Tree::Node *Tree::toNode(const std::string &data) {
    // Convert the data string into usable instruction words
    std::string instructions = getInstructions(data);

    // Abort the program if the getInstructions method detected an invalid
    // quantity of parentheses in the data string.
    if (instructions == "INVALID") illegal();

    // Generate the root node from the instructions
    Node *ptr = nodeFromInstructions(instructions);

    // If additional words remain after all parentheses are closed, abort the
    // program due to invalid instructions.
    if (!nextWord(instructions).empty()) {
        delete ptr;
        illegal();
    }

    // Return the root node
    return ptr;
}

/*
 * The illegal() function is used for exiting the program in the case that the
 * tree builder methods detect an invalid instruction string for construction.
 * This function prints an error message to the console, then aborts the
 * program with an exit code of -777.
 */
void Tree::illegal() {
    std::cout << "[ERROR] Illegal instructions.\n\n\tPROGRAM ABORTED\n\n";
    exit(-777);
}
