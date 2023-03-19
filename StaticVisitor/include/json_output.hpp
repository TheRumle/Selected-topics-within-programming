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

    void open_json_object() { os << '{'; }

    void close_json_object() { os << '}'; }

    /** overload the << operator for boolean values */
    template <Boolean B>
    json_ostream& operator<<(const B& value) {
        os << (value ? "true" : "false");
        return *this;
    }

    /** overload the << operator for number values */
    template <Number N>
    json_ostream& operator<<(const N& value) {
        os << value;
        return *this;
    }

    /** overload the << operator for string values */
    template <SString T>
    json_ostream& operator<<(const T& value) {
        static const std::unordered_set<std::string> keywords = {
                ":", ",", "{", "}", "[", "]", "true", "false", "null"
        };

        if (keywords.find(value) != keywords.end()) {
            os << value;
        } else {
            os << '"' << value << '"';
        }

        return *this;
    }

    /** overload the << operator for container values */
    template <Container C>
    json_ostream& operator<<(const C& value) {
        os << '[';
        auto it = value.begin();
        auto end = value.end();
        for (it; it != end-1; ++it) { // move to last second to last element 
            os << *it;
            os <<',';
        }
        os << *(end-1); // take the end element
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

    /** Helper function to write keys so that commas are added between fields, but not before the firstInSequence one */
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

  

    /** write JSON string */
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

    /** write JSON container */
    template <Container T>
    void visit(const std::string& key, const T& value) {
        out << write_key(key) << ':' << '[';

        for (const auto& item : value) {
            if (&item != &value.front()) {
                out << ',';
            }

            out << item;
        }

        out << ']';
    }
};


template <typename T>
json_writer_t& operator<<(json_writer_t& j, const T& value)
{
    j.visit("", value);
    return j;
}

template <typename T>
json_writer_t& operator<<(json_writer_t&& j, const T& value)
{
    return j << value;
}


#endif  // STATIC_VISITOR_JSON_OUTPUT_HPP
