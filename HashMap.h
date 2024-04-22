//
// Created by Abigail An Qi Meiser on 4/20/2024.
//

#ifndef DISCRETE_PROJ3_HASHMAP_H
#define DISCRETE_PROJ3_HASHMAP_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>

using namespace std;

struct Node{
    string key;
    int frequency;
    Node(const string& k, int f) : key(k), frequency(f){}
};

//used to build minHeap for finding the top 10 keys
struct hashComparator
{
    bool operator() (const Node& a, const Node& b){
        return a.frequency > b.frequency;
    }
};

class HashMap{
private:
    vector<list<Node>> table;
    vector<pair<string, int>> topTen;
    const int base = 31;
    int hashFunction(const string& key);
    priority_queue<Node, vector<Node>, hashComparator> minHeap;

public:

    HashMap(int size = 48571) : table(size){}
    void insert(const string& key);
    void printTable();
    void findGreatestFrequenciesHash();
    void printGreatestFrequenciesHash();
};


#endif //DISCRETE_PROJ3_HASHMAP_H