#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <utility>
#include <random>
#include <stdexcept>
#include <set>
#include <cctype>
#include <algorithm>
#include "Game.h"
using namespace std;


gameQuote::gameQuote() {
    original = "";
    mod = "";
    category = "";
    author = "";
    attempts = 10;
}

gameQuote::gameQuote(map<string, vector<pair<string, string>>>& categories){
    this->categories = categories;
    this->attempts = 10;
}

void gameQuote::getCategory() {
    cout << "Enter an integer to select your category: " << endl;
    int count = 1;
    for (auto iter = categories.begin(); iter != categories.end(); iter++){
        cout << count << ". " << iter->first << endl;
        count++;
    }

    string tag;
    getline(cin, tag);
    count = 1;
    //iterates through the map and assigns category corresponding to user input
    for (auto i = categories.begin(); i != categories.end(); i++){
        if(stoi(tag) == count){
            category = i->first;
        }
        count++;
    }

    //checks for valid input and starts game
    if(category.empty()) {
        cout << "invalid input! try again" << endl;
        getCategory();
    } else {
        original = getQuote(category);
        popString();
        printGameBoard();
    }
}

void gameQuote::printWelcomeBoard() {
    cout << "WHEEL OF QUOTES" << endl;
    cout << "Rules: \n"
            "1. You will choose a category for the quote\n"
            "2. You will be presented with a quote and the author as a hint\n"
            "3. You will enter a character to reveal from the quote, each input is one attempt\n"
            "4. You have ten attempts to enter the entire string before you reveal all the missing characters\n"
            << endl;
    cout << "Enter START to play!" << endl;
    string input;
    getline(cin, input);
    cout << endl;
    if(input == "START" || input == "start"){
        getCategory();
    } else {
        cout << "Oops! Invalid input." << endl;
        printWelcomeBoard();
    }
}

void gameQuote::printGameBoard() {
    //checks if the player has run out of attempts
    if (attempts == 0){
        cout << "Game over! Out of attempts :(" << endl;
        restart();
    } else { //otherwise print current stats
        cout << endl << mod << endl << "Author: " << author << endl;
        cout << "Attempts remaining: " << getAttempts() << endl;
        cout << "Letters used: ";

        for (auto it = letters_guessed.begin(); it != letters_guessed.end(); it++) {
            cout << *it << " ";
        }

        toggleGameBoard();
    }
}

void gameQuote::toggleGameBoard() {
    //prompts user to guess a letter or the full quote
    cout << endl << "Enter a letter or \"!\" to guess the full quote: " << endl;
    string in;
    getline(cin, in);
    char input;
    input = in[0];

    //if the user wants to input the full quote, gets input and checks accuracy
    //user input does not have to have accurate punctuation/spacing
    if (input == '!'){
        attempts--;
        cout << "Enter the whole quote including accurate punctuation: " << endl;
        string guess;
        getline(cin, guess);
        transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
        isGameOver(guess);
    } else {
        //checks if input is valid
        if (!isalpha(input)){
            cout << "Invalid input! Try again." << endl;
            printGameBoard();
        }
        //standardizes input to uppercase
        input = toupper(in[0]);
        //checks for cases where input was already guess, or already in the quote
        auto it = letters_guessed.find(input);
        if (it != letters_guessed.end()) {
            cout << "Letter already guessed. Try again!" << endl;
            printGameBoard();
        }

        auto iter = not_popped.find(input);
        if (iter != not_popped.end()) {
            cout << "Letter already in the quote. Try again!" << endl;
            printGameBoard();
        }

        //otherwise, decrement attempts and check if the letter
        //is a valid guess or if the whole string has been revealed
        //without an attempt of guessing the whole string
        attempts--;
        auto i = letters.find(input);
        if (i == letters.end()) {
            cout << "Wrong! Try again." << endl;
            printGameBoard();

        } else {
            letters_guessed.insert(input);
            editMod(input);

            if (filter(mod) == filter(original)){
                cout << "Game over :( You never guessed the quote!" << endl;
                restart();
            }

            printGameBoard();
        }
    }
}

void gameQuote::editMod(char input){ //if the inputted char is missing, edit the mod string
    for(int i = 0; i < original.length(); i++){
        for (int j = 0; j < mod.length(); j++){
            if (original[i] == input){
                mod[i] = original[i];
            }
        }
    }
}

void gameQuote::popString() {
    //populate the letters set with all unique letters in the quote
    for (int i = 0; i < original.length(); i++){
        if(isalpha(original[i])) {
            letters.emplace(original[i]);
        }
    }

    //calculate how many letters to remove from the quote based on amount of unique chars
    int remove_factor = letters.size() * 0.5;
    random_device rd;
    mt19937 gen(rd());

    while (remove_factor > 0 && !letters.empty()) {
        uniform_int_distribution<> dis(0, letters.size() - 1); //set size of generator so not out of rance

        auto it = letters.begin();
        advance(it, dis(gen)); //move it to random position

        not_popped.insert(*it);
        letters.erase(it); //delete ele at random position
        remove_factor--;
    }

    //assign mod to the original quote, and iterate through the modified letters set and remove the chars
    mod = original;
    for (int i = 0; i < original.length(); i++){
        for (auto iter= letters.begin(); iter != letters.end(); iter++){
            if (original[i] == *iter){
                mod[i] = '_';
            }
        }
    }
}


void gameQuote::isGameOver(string& guess) {
    cout << endl;
    //check if the guess quote is equal to the original, indicating win condition
    if (filter(guess) == filter(original)) {
        cout << "Nice work! Thanks for playing :3" << endl;
        restart();
    } else {
        //else continue the game
        cout << "Not the correct quote!" << endl;
        printGameBoard();
    }
}

string gameQuote::getQuote(string& category) {
    //checks if categories map is empty
    if (categories.empty()) {
        throw runtime_error("The map is empty.");
    }

    random_device rd;
    mt19937 gen(rd());

    //select a random pair from the vector at this key
    const auto& pairs = categories.at(category);
    if (pairs.empty()) {
        throw runtime_error("The vector for the selected key is empty.");
    }
    uniform_int_distribution<> current(0, pairs.size() - 1);
    const auto& random_pair = pairs[current(gen)];

    string quote = random_pair.first;

    //standardize the quote to uppercase
    transform(quote.begin(), quote.end(), quote.begin(), ::toupper);

    //assign author with the author corresponding to the randomly selected quote
    author = random_pair.second;
    return quote;
}


int gameQuote::getAttempts() {
    return attempts;
}

void gameQuote::restart() {
    cout << R"(Enter "1" to restart, or "2" to quit.)" << endl;
    string input;
    getline(cin, input);

    //if user wishes to restart, create new game object
    if (input == "1"){
        gameQuote gameQuote1(categories);
        gameQuote1.printWelcomeBoard();
    } else if (input == "2"){
        return;
    } else {
        cout << "Invalid input! Try again" << endl;
    }
}

string gameQuote::filter(string& str) {

    //filter the string so only compares entered chars and order so spaces and punctuation are not relevant
    string filtered;
    for (int i = 0; i < str.length(); i++){
        if(isalpha(str[i])){
            filtered += str[i];
        }
    }

    return filtered;
}

