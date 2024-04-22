//
// Created by Abigail An Qi Meiser on 4/20/2024.
//

#include "HashMap.h"
#include <iostream>
#include <string>

using namespace std;

int HashMap::hashFunction(const string& key){
    int hash = 0;

    for(char c : key){
        hash = (hash * base)^c;
    }
    return hash;
}

// inserts a key into the hashmap if it doesn't already exist
// increases the frequency of a key if the key already exists
void HashMap::insert(const string& key){
    int index = hashFunction(key) % table.size();
    bool keyExists = false;
    for(auto& node : table[index]){
        if(node.key == key){
            node.frequency++;
            keyExists = true;
            break;
        }
    }
    // if the key doesn't already exist
    if(!keyExists) {
        table[index].emplace_back(key, 1);
    }
}

// prints the hashmap
void HashMap::printTable() {
    for(int i = 0; i < table.size(); ++i){
        cout << "Bucket: " << i << ": ";
        for(auto node : table[i]){
            cout << "{" << node.key << ": " << node.frequency;
        }
        cout << endl;
    }
}

void HashMap::findGreatestFrequenciesHash(){
    //edge case if table is empty
    if(table.empty()){
        cout << "";
    }
    else{
        //makes min heap to find top ten keys
        for(const auto& chain : table){
            for(const auto& node: chain){
                minHeap.push(node);
                if(minHeap.size() > 10){
                    minHeap.pop();
                }
            }
        }

        //puts the top ten keys into a vector
        while(!minHeap.empty()){
            pair<string, int> p;
            p.first = minHeap.top().key;
            p.second = minHeap.top().frequency;
            topTen.push_back(p);
            minHeap.pop();
        }
    }
}

void HashMap::printGreatestFrequenciesHash() {

    for(auto& pair : topTen){
        cout << "Frequency: " <<  pair.second << ", Key: " << pair.first << endl;
    }
}