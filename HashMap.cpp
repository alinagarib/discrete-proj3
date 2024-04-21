//
// Created by Abigail An Qi Meiser on 4/20/2024.
//

#include "HashMap.h"
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <list>

using namespace std;

int HashMap::hashFunction(const string& key){
    int hash = 0;
    for(int i = 0; i < key.length(); i++){
        hash = hash + key[i] * pow(base, i);
    }
    return hash;
}

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

string HashMap::findHighestVal(){
    string maxKey;
    int highestFreq = -1;

    for(const auto& chain : table){
        for(const auto& node : chain){
            if(node.frequency > highestFreq){
                highestFreq = node.frequency;
                maxKey = node.key;
            }
        }
    }
    return maxKey;
}

void HashMap::printTable() {
    for(int i = 0; i < table.size(); ++i){
        cout << "Bucket: " << i << ": ";
        for(auto node : table[i]){
            cout << "{" << node.key << ": " << node.frequency;
        }
        cout << endl;
    }
}