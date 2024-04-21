//
// Created by Abigail An Qi Meiser on 4/20/2024.
//

#ifndef DISCRETE_PROJ3_HASHMAP_H
#define DISCRETE_PROJ3_HASHMAP_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

struct Node{
    string key;
    int frequency;
    Node(const string& k, int f) : key(k), frequency(f){}
};

class HashMap{
private:
    vector<list<Node>> table;
    const int base = 31;

public:
    HashMap(int size = 100) : table(size){}
    int hashFunction(const string& key);
    void insert(const string& key);
    string findHighestVal();
    void printTable();
};

#endif //DISCRETE_PROJ3_HASHMAP_H