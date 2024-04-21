#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "RedBlackTree.h"
using namespace std;

class Quotes {
    struct Quote {
        string quote;
        string author;
        string tags;
    };

    vector<Quote> quotes;

public:

    void readFile(const string& filename) {
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

            // Read categories, potentially enclosed in quotes
            if (ss.peek() == '"') {
                ss.get(); // Skip the opening quote
                getline(ss, entry.tags, '"'); // Read until the next quote
            } else {
                getline(ss, entry.tags);
            }

            quotes.push_back(entry);
        }

        file.close();
    }

    void printQuotes(){
        for (int i = 0; i < quotes.size(); i++){
            cout << "author: " << quotes[i].author << endl;
            cout << "quote: " << quotes[i].quote << endl;
            cout << "tags: " << quotes[i].tags << endl;
        }
    }
};

int main() {
    Quotes quotes;
    string filename = "quotes.csv";
    quotes.readFile(filename);

    RedBlackTree meow;
    meow.insert()
    return 0;
}