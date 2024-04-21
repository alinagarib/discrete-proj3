#include <string>
#include "Quotes.h"

using namespace std;

int main() {
    Quotes quotes;
    string filename = "quotes.csv";
    quotes.readFile(filename);
    quotes.startGame(quotes.categories);
    return 0;
}
