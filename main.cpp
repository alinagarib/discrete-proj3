#include <fstream>
#include <chrono>
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

    void printQuotes(){
        for (int i = 0; i < quotes.size(); i++){
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
    void removeQuotesfromQuotes(){
    for (Quote& q : quotes){
        q.quote = removeQuotesFromString(q.quote);
        q.author = removeQuotesFromString(q.author);
        q.tags = removeQuotesFromString(q.tags);
    }
    }

    //gets the first tag in each list of tags for each quote object
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
    string filename = "quotes.txt";
    quotes.readFile(filename);
    quotes.removeQuotesfromQuotes();

    //timing how long it takes to insert all the data into the hashmap
    auto start = chrono::steady_clock::now();

    HashMap h;
    quotes.getFirstTag(h);

    auto end = chrono::steady_clock::now();

    cout << h.findHighestVal() << endl;

    auto difference = end-start;

    //h.printTable();
    h.findGreatestFrequenciesHash();

    cout << "Time taken to build hashmap: " << chrono::duration<double, milli>(difference).count() << " ms" << endl;

    return 0;
}