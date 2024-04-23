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

void Quotes::startGame() {
    string input;
    cout << "\n********* WHEEL OF QUOTES *********\n\n"
            "Would you like to: \n"
            "1. View our structural sponsors!\n"
            "2. Begin Playing\n"
            "3. Quit\n"
            "Enter an integer corresponding to your choice" << endl;
    getline(cin, input);
    if (input == "1"){

        // prints top 10 most frequent tags from both RB tree and hashmap
        // prints the amount of time it took to build each data structure using chrono
        cout << "\n********* STRUCTURAL SPONSORS *********\n" << endl;

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

        cout << "Time taken to build red black tree: " << chrono::duration<double, milli>(difference).count() << " ms" << endl << endl;


        start = chrono::steady_clock::now();

        h.findGreatestFrequenciesHash();


        end = chrono::steady_clock::now();

        difference = end-start;

        h.printGreatestFrequenciesHash();

        cout << "Time taken to find Top 10 most frequent tags in hashmap: " << chrono::duration<double, milli>(difference).count() << " ms" << endl << endl;

        start = chrono::steady_clock::now();

        tree.findGreatestFrequencies(tree.getRoot());

        end = chrono::steady_clock::now();

        difference = end-start;

        tree.printGreatestFrequencies();

        cout << "Time taken to find Top 10 most frequent tags in red black tree: " << chrono::duration<double, milli>(difference).count() << " ms" << endl << endl;

        startGame();

    } else if(input == "2"){
        // values for the top 10 most frequent tags are still generated so the user can choose from them to start the game
        HashMap h;
        getFirstTagHashmap(h);
        RedBlackTree tree;
        getFirstTagTree(tree);
        h.findGreatestFrequenciesHash();
        tree.findGreatestFrequencies(tree.getRoot());
        vector<string> finalTenTags = tree.returnGreatestFrequencies();

        unordered_set<string> finalTags(finalTenTags.begin(), finalTenTags.end());

        for(auto iter = quotes.begin(); iter != quotes.end(); ++iter){
            if (finalTags.find(iter->tags) != finalTags.end()) {
                categories[iter->tags].emplace_back(iter->quote, iter->author);
            }
        }
        Game game(categories);

        //starts the game
        game.printWelcomeBoard();
    } else if (input == "3"){
        cout << "thanks anyway... >_<" << endl;
        return;
    } else {
        cout << "invalid input :( try again" << endl;
        startGame();
    }
}