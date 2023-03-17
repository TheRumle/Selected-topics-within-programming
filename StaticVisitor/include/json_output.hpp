#ifndef STATIC_VISITOR_JSON_OUTPUT_HPP
#define STATIC_VISITOR_JSON_OUTPUT_HPP

#include <iostream>
#include "meta.hpp"

/** TODO: implement json_ostream adapter with json output operations
 * The goal is to exercise meta-programming and not have complete JSON (Unicode support is beyond the scope).
 */
struct json_ostream
{
    std::ostream& os;
};

/** Visitor pattern support for writing JSON */
struct json_writer_t //this is the visitor
{
private:
    json_ostream stream;
    std::string value = "";

public:
    inline std::string get_value(){return value;}
    json_writer_t(const json_ostream &stream) : stream(stream) {}
    
    template <typename Data>
    void visit(const std::string& name, const Data& value)
    {
        auto s = json_ostream{std::cout};
        value << "field:" << (s.os << value);
    }
};

template <typename T>
json_ostream& operator<<(json_ostream& j, const T& value)
{
    if constexpr (is_bool_v<T>){
        j.os << (value ? "true" : "false");
    } else if constexpr (is_number_v<T>){
        j.os << value;
    } else if constexpr (is_string_v<T>){
        j.os <<  "\"" << value << "\"";
    } else if constexpr (is_container_v<T>){
        j.os << '[';
        const auto it = value.begin();
        const auto end = value.end();
        for (it; it != end-1; ++it) { // move to last second to last element 
             j << *it;
             j.os <<',';
        }
        j << *(value.end()-1); // take the end element
        j.os << ']';
    } else if constexpr (accepts_v<T,json_writer_t>){
        auto writer = json_writer_t{j};
        value.accept(writer);
        
        
    }
    
    return j;
}

template <typename T>
json_ostream& operator<<(json_ostream&& j, const T& value)
{
    return j << value;
}

#endif  // STATIC_VISITOR_JSON_OUTPUT_HPP
