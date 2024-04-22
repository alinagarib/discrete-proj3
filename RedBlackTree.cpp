//
// Created by jakeb on 4/19/2024.
//

#include "RedBlackTree.h"


void RedBlackTree::insert(string key) {
    TreeNode* node = new TreeNode(key);
    this->root = insertHelper(root, node);

    //case in which node is not utilized because it is a duplicate
    if(node->parent != nullptr)
        fixTree(node);

    this->root->color = BLACK;
}

TreeNode *RedBlackTree::insertHelper(TreeNode *root, TreeNode* node) {
    //Standard insertion into a BST, taken from my AVL project and modified slightly
    if(root == nullptr){
        return node;
    }

    //Very specific to our game, but increases the value (frequency) of the tag if it is already in the tree
    if(node->key == root->key){
        root->value++;
        return root;
    }
    if(node->key < root->key){
        root->left = insertHelper(root->left, node);
        //With the addition of a parent pointer, must keep track of them, and this does that in an efficient manner
        root->left->parent = root;
    }
    if(node->key > root->key){
        root->right = insertHelper(root->right, node);
        root->right->parent = root;
    }
    return root;
}

//This function is heavily influenced by the website programiz.com
void RedBlackTree::fixTree(TreeNode* node) {
    TreeNode* uncle;

    //As stated on the slides, when the parent of the node is black, nothing needs to be fixed
    //Therefore, the fix function operates while that isn't true
    while (node->parent != nullptr && node != root && node->parent->color == RED) {

        //Case when the parent of the node is the right child of the grandparent of the node
        if(node->parent == node->parent->parent->right){
            //If the statement is true, uncle of the node is the left child of the grandparent
            uncle = node->parent->parent->left;

            //Case when uncle is red, so colors must be flipped as per the slides
            if(uncle != nullptr && uncle->color == RED){
                uncle->color = BLACK;
                node->parent->color = BLACK;
                node->parent->parent->color = RED;

                //As the color switch may disrupt the overall tree, set node as the grandparent and keep fixing
                node = node->parent->parent;
            } else{
                //Case when uncle is black, so rotation must occur as per slides
                if(node == node->parent->left){
                    //Case is which a right left rotation is needed, so right rotate is done first
                    node = node->parent;
                    rotateRight(node);
                }
                //Appropriately changing colors based on the rotation
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateLeft(node->parent->parent);
            }
        } else {
            //Case when the parent of the node is the left child of the grandparent of the node
            //Therefore, uncle of the node is right child of grandparent
            uncle = node->parent->parent->right;

            //Case when uncle is red, so colors must be flipped as per the slides
            if(uncle != nullptr && uncle->color == RED){
                uncle->color = BLACK;
                node->parent->color = BLACK;
                node->parent->parent->color = RED;

                //As the color switch may disrupt the overall tree, set node as the grandparent and keep fixing
                node = node->parent->parent;
            } else{
                //Case when uncle is black, so rotation must occur as per slides
                if(node == node->parent->right){
                    //Case is which a left right rotation is needed, so left rotate is done first
                    node = node->parent;
                    rotateLeft(node);
                }
                //Appropriately changing colors based on the rotation
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateRight(node->parent->parent);
            }
        }

        //If the node ever gets changed to the root, then the tree is fixed and no need to go further
        if(root == node)
            break;
    }

}

void RedBlackTree::printGreatestFrequencies() {
    //Prints the contents of the minHeap with greatest frequencies
    while (!minHeap.empty()) {
        cout << "Frequency: " << minHeap.top()->value << ", Key: " << minHeap.top()->key << endl;
        minHeap.pop();
    }
}

void RedBlackTree::rotateLeft(TreeNode* node) {
    TreeNode* rightChild = node->right;
    //Ensures that the left child of the right child is not lost in rotation
    node->right = rightChild->left;

    //After checking that it's not null, make the current node the parent of the previously transferred node
    if(node->right != nullptr)
        node->right->parent = node;

    rightChild->parent = node->parent;

    //Fixing the parent's left or right in regard to the node being rotated
    if (node->parent == nullptr)
        root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;

    //Completing the rotation by connecting the rotated node and rightChild
    rightChild->left = node;
    node->parent = rightChild;
}

void RedBlackTree::rotateRight(TreeNode* node) {
    //All the same logic as rotateLeft but inverted
    TreeNode* leftChild = node->left;
    node->left = leftChild->right;

    if (node->left != nullptr)
        node->left->parent = node;

    leftChild->parent = node->parent;

    if (node->parent == nullptr)
        root = leftChild;
    else if (node == node->parent->left)
        node->parent->left = leftChild;
    else
        node->parent->right = leftChild;

    leftChild->right = node;
    node->parent = leftChild;
}

void RedBlackTree::printPreorder(TreeNode* node) {
    //Preorder traversal taken from my AVL project and modified
    if(node == nullptr)
        cout << "";
    else{
        if(node->parent != nullptr)
            cout<< "Node: " << node->key << " Color: " << node->color << " Frequency: " << node->value << " Parent: " << node->parent->key << endl;
        else
            cout<< "Node: " << node->key << " Color: " << node->color << " Frequency: " << node->value << " Parent: NULL" << endl;

        printPreorder(node->left);
        printPreorder(node->right);
    }
}

void RedBlackTree::findGreatestFrequencies(TreeNode *node) {

    //Does an inorder traversal of the whole tree
    if(node == nullptr)
        cout << "";
    else{
        findGreatestFrequencies(node->left);

        //Logic behind keeping the K largest elements in the whole tree
        if (minHeap.size() < 10) {
            minHeap.push(node);
        } else if (node->value > minHeap.top()->value) {
            minHeap.pop();
            minHeap.push(node);
        }

        findGreatestFrequencies(node->right);
    }
}

TreeNode *RedBlackTree::getRoot() {
    return root;
}

vector<string> RedBlackTree::returnGreatestFrequencies() {
    vector<string> finalTen;
    while (!minHeap.empty()) {
        finalTen.push_back(minHeap.top()->key);
        minHeap.pop();
    }
    return finalTen;
}
