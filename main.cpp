#include <string>
#include "Quotes.h"
#include <random>
#include <chrono>

using namespace std;

int main() {
    //rng to select one of the quotes files
    mt19937 rng_mt(time(nullptr));
    uniform_int_distribution<> current(1, 3);
    const auto& random = current(rng_mt);
    string filename;

    //assigns the filename based on rng
    if (random == 1){
        filename = "quotes.txt";
    } else if (random == 2){
        filename = "quotes_2.txt";
    } else if (random == 3){
        filename = "quotes_3.txt";
    }

    //beings program
    Quotes quotes;
    quotes.readFile(filename);
    quotes.removeQuotesfromQuotes();
    quotes.startGame();
    return 0;
}
