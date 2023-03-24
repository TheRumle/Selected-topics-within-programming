#ifndef STATIC_VISITOR_JSON_INPUT_HPP
#define STATIC_VISITOR_JSON_INPUT_HPP

#include <iostream>
#include <vector>
#include "meta.hpp"


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
    json_istream& operator>>(std::string& value) {
        is.get(); // consume the '"'
        std::getline(is, value, '"'); //use delimiter
        return *this;
    }

    json_istream& operator>>(int& value) {
        is >> value;
        return *this;
    }
    
    
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

template<typename T>
concept parsable = is_string_v<T> || is_number_v<T> || is_container_v<T>;
/** GoodVisitorPattern pattern support for reading JSON */
struct json_reader_t
{
private:
    
    template<typename T>
    void parse_value(const std::string& key, T& value){
        while (in.is.good()) {
            char c = in.is.get();

            if (c == '\"') {
                std::string fieldName;
                std::getline(in.is, fieldName, '\"');

                if (fieldName == key) {
                    in.is.get(); // consume the ':'
                    in >> value; //This gives me error since >> overload is ambigious? Why is that? All tests work? This is definitely smarter? Is it because I need to contraint T?
                    break;
                }
            }
        }
    }
public:
    json_istream& in;
    
    void visit(const std::string& key, bool& value) {
        parse_value(key, value);
    }

    void visit(const std::string& key, int& value) { //Is treated same as double
        double d{};
        visit(key, d);
        value = static_cast<int>(d);
    }

    /* visitor for the double type **/
    void visit(const std::string& key, double& value) {
        parse_value(key, value);
    }
    
    template <typename Data>
    void visit(const std::string& name, Data& value) {
        if constexpr (accepts_v<Data, json_reader_t>)
            value.accept(*this);
        else {
            in.is.get(); // consume the '{'
            value.accept(*this);
            in.is.get(); // consume the '}'
        }
    }

    /* visitor for the string type **/
    void visit(const std::string& key, std::string& value) {
        parse_value(key, value);
    }
    
    /* visitor for vector types **/
    template <typename T>
    void visit(const std::string& key, std::vector<T>& value) {
        parse_value(key, value);
    }
};



template <typename T>
json_istream& operator>>(json_istream& j, T& value)
{
    json_reader_t reader{j};

    if constexpr (accepts_v<T, json_reader_t>) {
        value.accept(reader);
    } else {
        throw std::runtime_error("Unsupported type.");
    }

    return j;
}
/** Helper for rvalue reference */
template <typename T>
constexpr json_istream& operator>>(json_istream&& j, T& value)
{
    return j >> value;
}



#endif  // STATIC_VISITOR_JSON_INPUT_HPP
