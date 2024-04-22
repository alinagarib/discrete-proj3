#include <string>
#include "Quotes.h"

using namespace std;

int main() {
    Quotes quotes;
    string filename = "quotes (1).txt";
    quotes.readFile(filename);
    quotes.removeQuotesfromQuotes();
    quotes.startGame(quotes.categories);
    return 0;
}
