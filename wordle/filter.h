//
// Created by rasmu on 26/02/2023.
//

#ifndef WORDLE_FILTER_H
#define WORDLE_FILTER_H

#include <string>
#include <vector>

namespace wordle{
    std::vector<std::string> filter(std::vector<std::string> &&words, const std::string &pattern);   
}


#endif //WORDLE_FILTER_H
