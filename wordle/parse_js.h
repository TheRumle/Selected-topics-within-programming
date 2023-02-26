//
// Created by rasmu on 26/02/2023.
//

#ifndef WORDLE_PARSE_JS_H
#define WORDLE_PARSE_JS_H

#include <iosfwd>
#include <vector>

namespace wordle {
    std::vector <std::string> parse_js_file(std::istream &&is);
}

#endif //WORDLE_PARSE_JS_H
