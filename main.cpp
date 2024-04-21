#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "HashMap.h"
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
//            cout << "author: " << quotes[i].author << endl;
//            cout << "quote: " << quotes[i].quote << endl;
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
    void removeQuotesfromQuotes(){
    for (Quote& q : quotes){
        q.quote = removeQuotesFromString(q.quote);
        q.author = removeQuotesFromString(q.author);
        q.tags = removeQuotesFromString(q.tags);
    }
    }

    void getFirstTag(HashMap& map){

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

};

int main() {
    Quotes quotes;
    string filename = "quotes.csv";
    quotes.readFile(filename);
    quotes.removeQuotesfromQuotes();
    HashMap h;
    cout << "meow" << endl;
    quotes.getFirstTag(h);
    //quotes.printQuotes();

    // testing functions for HashMap implementation
//    h.insert("love");
//    h.insert("love");
//    h.insert("love");
//    h.insert("happy");
//
    //h.insert("attributed-no-source");

    h.printTable();
    cout << h.findHighestVal() << endl;

    return 0;
}