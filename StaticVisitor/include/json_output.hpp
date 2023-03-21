#ifndef STATIC_VISITOR_JSON_OUTPUT_HPP
#define STATIC_VISITOR_JSON_OUTPUT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include "meta.hpp"


struct json_ostream
{
    std::ostream& os;
    inline void open_json_object() { os << '{'; }
    inline void close_json_object() { os << '}'; }

    template <Boolean B>
    json_ostream& operator<<(const B& value) {
        os << (value ? "true" : "false");
        return *this;
    }

    template <Number N>
    json_ostream& operator<<(const N& value) {
        os << value;
        return *this;
    }

    template <SString T>
    json_ostream& operator<<(const T& value) {
        static const std::unordered_set<std::string> keywords = {
                ":", ",", "{", "}", "[", "]", "true", "false", "null"
        };

        if (keywords.find(value) != keywords.end()) 
            os << value;
        else
            os << '"' << value << '"';
        

        return *this;
    }

    template <Container C>
    json_ostream& operator<<(const C& value) {
        os << '[' << *std::begin(value); 
        for (auto it = std::begin(value)+1; it != std::end(value); ++it)
            os<<',' << *it;
        
        os << ']';
        return *this;
    }
};


template<typename T>
concept Writable = Boolean<T> || Number<T>;

struct json_writer_t
{
    json_ostream& out;
    json_writer_t(json_ostream& out) : out(out) {}
    bool firstInSequence = true;

    std::string write_key(const std::string& key) {
        if (!firstInSequence) 
            out.os << ',';
        
        firstInSequence = false;
        return key;
    }

    template <typename Data>
    void write_json_object(const Data& value) {
        out.open_json_object();
        value.accept(*this);
        out.close_json_object();
    }

    template <typename T>
    void visit(const std::string& key, const T& value) {
        if (!key.empty())
            out << write_key(key) << ':';
        
        bool temp = firstInSequence;
        firstInSequence = true;
        write_json_object(value);
        firstInSequence = temp;
    }
    
    void visit(const std::string& key, std::nullptr_t) {
        out << write_key(key) << ":null";
    }

    template <Writable B> //Handles boolean and Numbers in the same manner.
    void visit(const std::string& key, const B& value) {
        out << write_key(key) << ":" << value;
    }
    
 
    template <SString S>
    void visit(const std::string& key, const S& value) {
        out << write_key(key) << ":" << '"';

        for (char c : value) 
            switch (c) {
                case '\"': out << "\\\"";
                case '\\': out << "\\\\";
                case '\b': out << "\\b";
                case '\f': out << "\\f";
                case '\n': out << "\\n";
                case '\r': out << "\\r";
                case '\t': out << "\\t";
                break;
                default: out << c; break;
            }

        out << '"';
    }
    
    
    template <Container T>
    void visit(const std::string& key, const T& value) {
        out << write_key(key) << ':' << '[' << *std::begin(value); //No comma for first element in list

        for (auto it = std::begin(value)+1; it != std::end(value); ++it)
            out<<',' << *it;
        
        out << ']';
    }
};

template <typename T>
json_writer_t& operator<<(json_writer_t& j, const T& value) {
    return json_writer_t{j}.visit("", value), j;
}

template <typename T>
json_writer_t& operator<<(json_writer_t&& j, const T& value) {
    return j << value;
}


#endif  // STATIC_VISITOR_JSON_OUTPUT_HPP
