#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <unordered_set>
#include "Quotes.h"
#include "Game.h"
#include "HashMap.h"
#include "RedBlackTree.h"

using namespace std;

Quotes::Quotes() {}

void Quotes::readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: File could not be opened." << endl;
        return; // Exit the function if file is not open
    }

    string line;

    //ignoring the first line
    getline(file, line);

    while(getline(file, line)){
        istringstream ss(line);
        Quote entry;

        getline(ss, entry.quote, '\t');
        getline(ss, entry.author, '\t');
        getline(ss, entry.tags, '\t');

        quotes.push_back(entry);
    }

    file.close();
}

void Quotes::printQuotes(){
    for (int i = 0; i < 1; i++){
        cout << "author: " << quotes[i].author << endl;
        cout << "quote: " << quotes[i].quote << endl;
        cout << "tags: " << quotes[i].tags << endl;
    }
}

// removes the quotation marks from a string if it has any
string removeQuotesFromString(const string& str){
    string result;
    for(char c : str){
        if (c!= '"'){
            result +=c;
        }
    }
    return result;
}

// removes the quotation marks from a quote object
void Quotes::removeQuotesfromQuotes(){
    for (Quote& q : quotes){
        q.quote = removeQuotesFromString(q.quote);
        q.author = removeQuotesFromString(q.author);
        q.tags = removeQuotesFromString(q.tags);
    }
}

//gets the first tag in each list of tags for each quote object
void Quotes::getFirstTagHashmap(HashMap& map){

    for (int i = 0; i < quotes.size(); i++){

        int position = quotes[i].tags.find(',');
        string firstTag;
        // if there is more than one tag
        if (position != string::npos){
            firstTag = quotes[i].tags.substr(0, position);
        }
            // if there is only one tag
        else{
            firstTag = quotes[i].tags;
        }
        map.insert(firstTag);
    }
}

//Same as function for hashmap but for red black tree
void Quotes::getFirstTagTree(RedBlackTree& map){

    for (int i = 0; i < quotes.size(); i++){

        int position = quotes[i].tags.find(',');
        string firstTag;
        // if there is more than one tag
        if (position != string::npos){
            firstTag = quotes[i].tags.substr(0, position);
        }
            // if there is only one tag
        else{
            firstTag = quotes[i].tags;
        }
        map.insert(firstTag);
    }
}

void Quotes::startGame(map<string, vector<pair<string, string>>> &categories) {
    //set default map values for now

    cout << "********* WHEEL OF QUOTES *********" << endl;

    auto start = chrono::steady_clock::now();

    HashMap h;
    getFirstTagHashmap(h);

    auto end = chrono::steady_clock::now();

    auto difference = end-start;

    cout << "Time taken to build hashmap: " << chrono::duration<double, milli>(difference).count() << " ms" << endl;

    start = chrono::steady_clock::now();

    RedBlackTree tree;
    getFirstTagTree(tree);

    end = chrono::steady_clock::now();

    difference = end-start;

    cout << "Time taken to build red black tree: " << chrono::duration<double, milli>(difference).count() << " ms" << endl;


    start = chrono::steady_clock::now();

    h.findGreatestFrequenciesHash();


    end = chrono::steady_clock::now();

    difference = end-start;

    cout << "Time taken to find Top 10 most frequent tags in hashmap: " << chrono::duration<double, milli>(difference).count() << " ms" << endl;

    start = chrono::steady_clock::now();

    tree.findGreatestFrequencies(tree.getRoot());

    end = chrono::steady_clock::now();

    difference = end-start;

    vector<string> finalTenTags = tree.returnGreatestFrequencies();

    unordered_set<string> finalTags(finalTenTags.begin(), finalTenTags.end());


    cout << "Time taken to find Top 10 most frequent tags in red black tree: " << chrono::duration<double, milli>(difference).count() << " ms" << endl;

    for(auto iter = quotes.begin(); iter != quotes.end(); ++iter){
        if (finalTags.find(iter->tags) != finalTags.end()) {
            categories[iter->tags].emplace_back(iter->quote, iter->author);
        }
    }

    Game game(categories);
    game.printWelcomeBoard();
}
