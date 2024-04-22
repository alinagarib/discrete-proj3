//
// Created by jakeb on 4/19/2024.
//

#ifndef DISCRETE_PROJ3_REDBLACKTREE_H
#define DISCRETE_PROJ3_REDBLACKTREE_H
#include <iostream>
#include <vector>
#include <string>
#include <queue>
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

    TreeNode(string& key) : key(""), value(1),left(nullptr), right(nullptr), parent(nullptr), color(RED){
        this->key = key;
    }

};

//This was heavily influenced by geeksforgeeks.org
class nodeComparator
{
public:
    bool operator() (const TreeNode* a, const TreeNode* b)
    {
        return a->value > b->value;
    }
};

class RedBlackTree {
private:
    TreeNode* root;
    TreeNode* insertHelper(TreeNode* root, TreeNode* node);
    void rotateLeft(TreeNode* node);
    void rotateRight(TreeNode* node);
    priority_queue<TreeNode*, vector<TreeNode*>, nodeComparator > minHeap;

public:
    RedBlackTree() : root(nullptr){};
    void insert(string key);
    void fixTree(TreeNode* node);
    void printPreorder(TreeNode* node);
    void findGreatestFrequencies(TreeNode* node);
    vector<string> returnGreatestFrequencies();
    void printGreatestFrequencies();
    TreeNode* getRoot();

};



#endif //DISCRETE_PROJ3_REDBLACKTREE_H
