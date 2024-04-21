#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "Quotes.h"
#pragma once
using namespace std;

//maybe just make a class for popped string
class gameQuote {
public:
    string original;
    string mod;
    string category;
    string author;
    set<char> letters;
    set<char> not_popped;
    set<char> letters_guessed;
    int attempts;
    map<string, vector<pair<string, string>>> categories;

    gameQuote();
    gameQuote(map<string, vector<pair<string, string>>>& categories);
    void printWelcomeBoard();

private:
    void getCategory();
    void printGameBoard();
    void toggleGameBoard();
    void popString();
    void restart();
    void isGameOver(string& guess);
    string getQuote(string& category);
    int getAttempts();
    string filter(string& str);
    void editMod(char input);

};


