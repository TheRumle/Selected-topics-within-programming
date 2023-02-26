#include <iostream>
#include <vector>
#include <fstream>
#include "parse_js.h"


int main()
{
    std::ifstream file("wordles .js");
    
    const auto database = wordle::parse_js_file(std::move(file)); /* read the database from the javascript file */
    auto words = database; // make a copy of the database
    
    auto guess = std::string{}; // allocate memory to store guess patterns
    while (words.size()>1) {
        std::cout << words.size() << " words remaining\n";
        bool good = true;
        do {
            std::cout << "Enter a guess pattern: ";
            std::cin >> guess;
            /* sanitize: set good to false if input fails to follow the pattern */
        } while (!good);
        /* apply the filter on the words */
        /* pick and announce one of the words for the user to try */
    }

    if (words.size() == 1) {
        std::cout << "Congratulations: " << words.front() << "\n";
    } else {
        std::cerr << "Something got messed up :-(\n";
    }
}

