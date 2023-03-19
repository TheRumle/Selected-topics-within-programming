#ifndef STATIC_VISITOR_JSON_INPUT_HPP
#define STATIC_VISITOR_JSON_INPUT_HPP

#include <iostream>
#include <vector>
#include "meta.hpp"

/** TODO: implement json_istream adapter with json input operations
 * The goal is to exercise meta-programming and not have complete JSON (Unicode support is beyond the scope).
 * Parsing should follow the type structure rather than the content of the input stream.
 * GoodVisitorPattern parsing may depend on the order of fields, which is OK for this exercise.
 */

struct json_reader_t;

struct json_istream
{
    std::istream& is;
    json_istream& operator>>(bool& value) {
        is >> std::boolalpha >> value; //"true" is parsed as 1 and "false" as 0
        return *this;
    }

    template<Number T>
    json_istream& operator>>(T& value) {
        is >> value; //"true" is parsed as 1 and "false" as 0
        return *this;
    }

    json_istream& operator>>(int& value) {
        is >> value;
        return *this;
    }
    

    //TODO use the concept of a Container.
    template <typename T>
    json_istream& operator>>(std::vector<T>& value) {
        is.get(); //skip the [
        while (is.good() ) {
            const char c = is.get();
            if (c == ',') continue;
            if (c == ']') break;
            is.unget();
            
            T element;
            is >> element;
            value.push_back(element);
        }

        return *this;
    }
    
    
};


template <typename T>
json_istream& operator>>(json_istream& j, T&)
{
    /** TODO: implement input of arbitrary types so that tests in json_input_test pass.
     * Focus on one test at a time: begin from the first and then continue to next.
     * In order to support various types, develop and test meta-predicates (see meta_test.cpp)
     * Tip: either use if-constexpr or overloading with SFINAE/concepts
     */
    return j;
}
/** Helper for rvalue reference */
template <typename T>
json_istream& operator>>(json_istream&& j, T& value)
{
    return j >> value;
}

/** GoodVisitorPattern pattern support for reading JSON */
struct json_reader_t
{
    template <typename Data>
    void visit(const std::string& name, Data& value)
    {
        /** TODO: use static visitor pattern to read class fields from input stream */
    }
};





#endif  // STATIC_VISITOR_JSON_INPUT_HPP
