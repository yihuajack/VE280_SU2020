#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const std::string &str, int num, Node *left, Node *right) : str(str), num(num), left(left), right(right) {
    // TODO: implement this function.
    // REQUIRES: The input left and right point to a dynamically allocated node object,
    //           if not being NULL.
    // MODIFIES: this
    // EFFECTS: Construct a node with given input values.

}

Node* Node::leftSubtree() const{
    // TODO: implement this function.  
    // EFFECTS: Return the pointer to the left child of the node.
    return left;
}

void Node::setleft(Node *n) {
    // TODO: implement this function.  
    // MODIFIES: this
    // EFFECTS: set the left child of the node to be n.
    left = n;
}

Node* Node::rightSubtree() const{
    // TODO: implement this function.  
    // EFFECTS:  Return the pointer to the right child of the node.
    return right;
}

void Node::setright(Node *n) {
    // TODO: implement this function.  
    // MODIFIES: this
    // EFFECTS: set the right child of the node to be n.
    right = n;
}

string Node::getstr() const {
    // TODO: implement this function.  
    // EFFECTS:  Return the “str” component of the node.
    return str;
}

int Node::getnum() const {
    // TODO: implement this function.  
    // EFFECTS:  Return the “num” component of the node.
    return num;
}

void Node::incnum() {
    // TODO: implement this function.
    // MODIFIES: this
    // EFFECTS: increment num by 1
    num++;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    // TODO: implement this function.
    // REQUIRES: leftNode and rightNode points to dynamically allocated node objects.
    // EFFECTS: Returns a pointer to a node with "str" being the result of appending
    //          leftNode->str and rightNode->str, and "num" being leftNode->num +
    //          rightNode->num. Moreover, “left” should be leftNode and “right”
    //          should be rightNode. Also, Please allocate memory for this returned node
    //          object.
    //
    //          For example, if leftNode->str = "a", and rightNode->str = "b", then
    //          the "str" of the merged node is "ab".
    return new Node(leftNode->str + rightNode->str, leftNode->num + rightNode->num, leftNode, rightNode);
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode) : root(rootNode) {
    // TODO: implement this function.
}

static void RemoveBinaryTree(Node *node) {
    // MODIFIES: node
    // EFFECTS: Recursivly remove the left sub tree and right sub tree of the binary tree.
    if (!node)
        return;
    else {
        Node *victim = node;
        RemoveBinaryTree(victim->leftSubtree());
        RemoveBinaryTree(victim->rightSubtree());
        delete victim;
    }
}

BinaryTree::~BinaryTree() {
    // TODO: implement this function.
    // REQUIRES: The input rootNode points to a dynamically allocated node object,
    //           if not being NULL.
    // MODIFIES: this
    // EFFECTS: Construct a binary tree with a root node.
    RemoveBinaryTree(root);
}

static string FindPath(const Node *node, const string& s) {
    // EFFECTS: Recursively derive the path of s.
    if (!node) return "-1";
    else if (node->getstr() == s) return "";
    else {
        string path = FindPath(node->leftSubtree(), s);
        if (path != "-1") return "0" + path;
        else {
            path = FindPath(node->rightSubtree(), s);
            return (path != "-1") ? "1" + path : "-1";
        }
    }
}

string BinaryTree::findPath(const string &s) const{
    // TODO: implement this function.
    // EFFECTS: Return the path from the root node to the node with the string s.
    //          The path is encoded by a string only containing '0' and '1'. Each
    //          character, from left to right, shows whether going left (encoded
    //          by ‘0’) or right (encoded by ‘1’) from a node can lead to the
    //		    target node.
    //
    //          For example, we want to find "g" in the following
    //          tree (only the "str" components are shown):
    //
    //                          "a"
    //                         /   \
    //                        /      \
    //                      "b"      "c"
    //                      / \      / \
    //                        "d"      "e"
    //                        / \      / \
    //                      "f" "g"
    //                      / \ / \
    //
    //          The returned string should be "011". (Go left from "a", then go right from
    //          "b", and finally go right from "d" can lead us to "g".)
    //
    //          If s is in root node, then return an empty string.
    //          If s is not in the tree, then return "-1".
    //          You can assume that the "str" components of all the nodes are unique in a
    //          tree.
    return FindPath(root, s);
}

static int Sum(const Node *node) {
    // EFFECTS: Recursively sum up the num of this node, its left node and its right node.
    return (node) ? node->getnum() + Sum(node->leftSubtree()) + Sum(node->rightSubtree()) : 0;
}

int BinaryTree::sum() const {
    // TODO: implement this function.
    // EFFECTS: Returns the sum of "num" values of all nodes in the tree. If the tree is
    //          empty, return 0.
    return Sum(root);
}

static int Depth(const Node *node) {
    // EFFECTS: Recursively add 1 to the larger one between the left sub tree and the right sub tree until the function reaches the leaves.
    return (node) ? max(Depth(node->leftSubtree()), Depth(node->rightSubtree())) + 1 : 0;
}

int BinaryTree::depth() const {
    // TODO: implement this function.
    // EFFECTS: Returns the depth of the tree, which equals the number of layers of nodes
    //          in the tree. Returns zero if the tree is empty.
    //
    // For example, the tree
    //
    //                           a
    //                         /   \
    //                        /      \
    //                       b        c
    //                      / \      / \
    //                         d        e
    //                        / \      / \
    //                       f   g
    //                      / \ / \
    //
    // has depth 4.
    // The node a is on the first layer.
    // The nodes b and c are on the second layer.
    // The nodes d and e are on the third layer.
    // The nodes f and g are on the fourth layer.
    return Depth(root);
}

static void Preorder_num(const Node *node) {
    // EFFECTS: Print the "num" component of the tree by preorder.
    if (!node)
        return;
    else {
        cout << node->getnum() << " ";
        Preorder_num(node->leftSubtree());
        Preorder_num(node->rightSubtree());
    }
}

void BinaryTree::preorder_num() const {
    // TODO: implement this function.
    // EFFECTS: Prints the "num" component of each node using a pre-order traversal.
    //          Seperate each "num" with a space. A pre-order traversal prints the
    //          current node first, then recursively visit its left subtree, and then
    //          recursively visit its right subtree and so on, until the right-most
    //          element is printed.
    //
    //          For any node, all the elements of its left subtree
    //          are considered as on the left of that node and
    //          all the elements of its right subtree are considered as
    //          on the right of that node.
    //
    //          For example, the tree:
    //
    //                           4
    //                         /   \
    //                        /     \
    //                       2       5
    //                      / \
    //                     7   3
    //                        / \
    //                       8   9
    //
    //          would print 4 2 7 3 8 9 5
    //
    //          An empty tree would print nothing.
    Preorder_num(root);
    cout << endl;
}

static void Inorder_str(const Node *node) {
    // EFFECTS: Print the "str" component of the tree by inorder.
    if (!node)
        return;
    else {
        Inorder_str(node->leftSubtree());
        cout << node->getstr() << " ";
        Inorder_str(node->rightSubtree());
    }
}

void BinaryTree::inorder_str() const {
    // TODO: implement this function.
    // EFFECTS: Prints the "str" component of each node using an in-order traversal.
    //          Separate each "str" with a space. An in-order traversal prints the
    //          "left most" element first, then the second-left-most, and so on,
    //          until the right-most element is printed.
    //
    //          For any node, all the elements of its left subtree
    //          are considered as on the left of that node and
    //          all the elements of its right subtree are considered as
    //          on the right of that node.
    //
    //          For example, the tree:
    //
    //                           a
    //                         /   \
    //                        /     \
    //                       bb     ddd
    //                      /  \
    //                     e    c
    //
    //          would print e bb c a ddd
    //
    //          An empty tree would print nothing.
    Inorder_str(root);
    cout << endl;
}

static void Postorder_num(const Node *node) {
    // EFFECTS: Print the "num" component of the tree by postorder.
    if (!node)
        return;
    else {
        Postorder_num(node->leftSubtree());
        Postorder_num(node->rightSubtree());
        cout << node->getnum() << " ";
    }
}

void BinaryTree::postorder_num() const {
    // TODO: implement this function.
    // EFFECTS: Prints the "num" component of each node using a post-order traversal.
    //          Seperate each "num" with a space. A post-order traversal recursively
    //          visit its left subtree, and then recursively visit its right subtree
    //          and then print the current node.
    //
    //          For any node, all the elements of its left subtree
    //          are considered as on the left of that node and
    //          all the elements of its right subtree are considered as
    //          on the right of that node.
    //
    //          For example, the tree:
    //
    //                           4
    //                         /   \
    //                        /     \
    //                       2       5
    //                      / \
    //                     7   3
    //                        / \
    //                       8   9
    //
    //          would print 7 8 9 3 2 5 4
    //
    //          An empty tree would print nothing.
    Postorder_num(root);
    cout << endl;
}

static bool AllPathSumGreater(const Node *node, int sum) {
    // EFFECTS: Recursively determine whether the sum of all the paths is grater than "sum" from the root.
    if (!node)
        return true;
    else
        return (node->leftSubtree() && node->rightSubtree()) ? AllPathSumGreater(node->leftSubtree(), sum - node->getnum()) && AllPathSumGreater(node->rightSubtree(), sum - node->getnum()) : node->getnum() > sum;
}

bool BinaryTree::allPathSumGreater(int sum) const {
    // TODO: implement this function.
    // REQUIRES: The tree is not empty
    //
    // EFFECTS: Returns true if and only if for each root-to-leaf path of the tree,
    //          the sum of "num" of all nodes along the path is greater than "sum".
    //
    //          A root-to-leaf path is a sequence of nodes in a tree starting with
    //          the root element and proceeding downward to a leaf (an element with
    //          no children).
    //
    // For example, the tree (only the "num" components are shown):
    //
    //                           4
    //                         /   \
    //                        /     \
    //                       1       5
    //                      / \     / \
    //                     3   6
    //                    / \ / \
    //
    // has three root-to-leaf paths: 4->1->3, 4->1->6 and 4->5.
    // Given the input sum = 9, the path 4->5 has the sum 9, so the function
    // should return false. If the input sum = 7, since all paths have the sums
    // greater than 7, the function should return true.
    return AllPathSumGreater(root, sum);
}

static bool Covered_by(const Node *node, const Node *treenode) {
    // EFFECTS: Recursively determine whether this node is covered by the treenode.
    if (node && treenode)
        return node->getnum() == treenode->getnum() && Covered_by(node->leftSubtree(), treenode->leftSubtree()) && Covered_by(node->rightSubtree(), treenode->rightSubtree());
    else
        return (!node) ? true : false;
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    // TODO: implement this function.
    // EFFECTS: Returns true if this tree is covered by the input binary tree "tree".
    //          (only consider the "num" component)
    return Covered_by(root, tree.root);
}

static bool Contained_by(const Node *node, const Node *treenode) {
    // EFFECTS: Recursively determine whether this node is contained by the treenode.
    if (Covered_by(node, treenode))
        return true;
    else
        return (treenode) ? Contained_by(node, treenode->leftSubtree()) || Contained_by(node, treenode->rightSubtree()) : false;
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    // TODO: implement this function.
    // EFFECTS: Returns true if this tree is contained by the input binary tree "tree".
    //          (only consider the "num" component)
    return Contained_by(root, tree.root);
}

Node *Copy(const Node *node) {
    // EFFECTS: Recursively copy the nodes in the tree.
    return (node) ? new Node(node->getstr(), node->getnum(), (node->leftSubtree()) ? Copy(node->leftSubtree()) : nullptr, (node->rightSubtree()) ? Copy(node->rightSubtree()) : nullptr) : nullptr;
}

BinaryTree BinaryTree::copy() const {
    // TODO: implement this function.
    // EFFECTS: Returns a copy of this tree. Hint: use deep copy.
    BinaryTree binaryTree(Copy(root));
    return binaryTree;
}
