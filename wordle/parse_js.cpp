//
// Created by rasmu on 26/02/2023.
//

#include <iomanip>
#include "parse_js.h"

std::vector<std::string> wordle::parse_js_file(std::istream &&is) {
    std::vector<std::string> words;
    auto word = std::string{};
    while (is) { // check for EOF and potential I/O errors
        if (is.peek() == '"') { // look for an opening quote
            is >> std::quoted(word); // read the word in quotes and remove quotes
            if (word.length() == 5 && // must be 5-letter word
                std::all_of(std::cbegin(word), std::cend(word), // all lower-case letters
                            [](char c) { return std::isalpha(c) && std::islower(c); }))
                words.push_back(word);
        } else
            is.get(); // skip one character
    }
    std::sort(std::begin(words), std::end(words));
    words.erase(std::unique(std::begin(words), std::end(words)), words.end());
    return words;
}
