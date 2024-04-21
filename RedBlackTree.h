//
// Created by jakeb on 4/19/2024.
//

#ifndef DISCRETE_PROJ3_REDBLACKTREE_H
#define DISCRETE_PROJ3_REDBLACKTREE_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Learned what enum was while trying to search of a way to code color in a readable manner on stack overflow
enum Color {RED, BLACK};



class TreeNode{
public:
    string key;
    int value;
    Color color;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(string& key) : key(""), value(0),left(nullptr), right(nullptr), parent(nullptr), color(RED){
        this->key = key;
        this->value = value;
    }

};


class RedBlackTree {
private:
    TreeNode* root;
    TreeNode* insertHelper(TreeNode* node, string& key);
    vector<TreeNode> findGreatestFrequenciesHelper();
    void rotateLeft(TreeNode* node);
    void rotateRight(TreeNode* node);


public:
    RedBlackTree() : root(nullptr){};
    void insert(string& key);
    void fixTree(TreeNode* node);
    vector<TreeNode> findGreatestFrequencies();

};


#endif //DISCRETE_PROJ3_REDBLACKTREE_H
