#ifndef DISCRETE_PROJ3_QUOTES_H
#define DISCRETE_PROJ3_QUOTES_H

#endif //DISCRETE_PROJ3_QUOTES_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "HashMap.h"
#include "RedBlackTree.h"

#pragma once
using namespace std;

class Quotes {
    struct Quote {
        string quote;
        string author;
        string tags;
    };

    vector<Quote> quotes;
    //map of map<string, vector<string>> to sort by <category, vector<quote, author>>

public:
    map<string, vector<pair<string, string>>> categories;
    Quotes();
    void readFile(const string& filename);
    void printQuotes();
    void startGame(); //that calls printWelcomeBoard
    //function to use the data structures and sort the quotes into categories
    void removeQuotesfromQuotes();
    void getFirstTagHashmap(HashMap &map);

    void getFirstTagTree(RedBlackTree& map);
};

