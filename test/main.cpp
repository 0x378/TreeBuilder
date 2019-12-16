/*
 * Tree Builder 9001
 *
 * Author: The Cat
 * Version: 2019.12.16
 */

#include <iostream>
#include "Tree.h"

int main() {
    std::string testString = "2{ -5(-9,null), 7[3(n,04[n,4]),42(9,9001)] }";

    std::cout << "Meow, World!";
    std::cout << "\n\nString-generated tree:";
    std::cout << "\n\tSource string: " << testString;
    std::cout << "\n\tInstructions: " << Tree::getInstructions(testString);

    Tree strTree(testString), expTree;

    std::cout << "\n\n\tPre-order traversal:  " << strTree.toStringPreOrder();
    std::cout << "\tIn-order traversal:   " << strTree.toStringInOrder();
    std::cout << "\tPost-order traversal: " << strTree.toStringPostOrder();

    std::cout << "\n\tOutput stream: " << strTree;

    return 0;
}
