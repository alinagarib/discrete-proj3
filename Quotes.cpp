#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "Quotes.h"
#include "Game.h"
using namespace std;

Quotes::Quotes() {}

void Quotes::readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: File could not be opened." << endl;
        return; // Exit the function if file is not open
    }

    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        Quote entry;

        // Read quote
        if (ss.peek() == '"') {
            ss.get(); // Skip the opening quote
            getline(ss, entry.quote, '"'); // Read until the next quote
            if (ss.peek() == ',') ss.get(); // Skip the comma after the closing quote
        } else {
            getline(ss, entry.quote, ',');
        }

        // Read author
        getline(ss, entry.author, ',');

        //parse to only get the first tag of list of categories
        // Read categories, potentially enclosed in quotes
        string full_tags;
        if (ss.peek() == '"') {
            ss.get(); // Skip the opening quote
            getline(ss, full_tags, '"'); // Read until the next quote
        } else {
            getline(ss, full_tags);
        }

        stringstream tagsStream(full_tags);
        getline(tagsStream, entry.tags, ',');

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

void Quotes::startGame(map<string, vector<pair<string, string>>> &categories) {
    //set default map values for now
    categories[quotes[0].tags].push_back({quotes[0].quote, quotes[0].author});
    categories[quotes[1].tags].push_back({quotes[1].quote, quotes[1].author});
    gameQuote game(categories);
    game.printWelcomeBoard();
}
