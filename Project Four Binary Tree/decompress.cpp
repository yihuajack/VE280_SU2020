#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <fstream>

using namespace std;

void printNode(const Node *node) {
    // EFFECTS: Print str member of the node.
    cout << node->getstr();
}

void binDecode(Node *node, const string& bincode) {
    // MODIFIES: node
    // EFFECTS: Decode the binary code.
    for (unsigned int i = 0; i < bincode.length(); i++) {
        if (bincode[i] == '0')
            node = node->leftSubtree();
        else
            node = node->rightSubtree();
    }
    printNode(node);
}

int main(int argc, char *argv[]) {
    // TODO: implement this function
    // REQUIRES: two arguments.
    // EFFECTS: Decompress the treefile and the binaryfile to textfile.
    string bincode, treefilename = argv[1], binaryfile = argv[2];
    ifstream ifile(binaryfile);
    HuffmanTree huffmanTree(treefilename);
    while (ifile >> bincode) {
        binDecode(huffmanTree.root, bincode);
    }
    ifile.close();
}