#ifndef STATIC_VISITOR_META_HPP
#define STATIC_VISITOR_META_HPP

#include <type_traits>
#include <cstdint>
#include <string>

template <typename T>
constexpr auto is_bool_v = std::is_same_v<bool, std::remove_cvref_t<T>>; //remove modifiers

template <typename T>
constexpr auto is_number_v =  std::is_arithmetic_v<std::remove_cvref_t<T>> && !std::is_same_v<bool, T>;

template <typename T>
constexpr auto is_character_v = std::is_same_v<char, std::remove_cvref_t<T>>; //remove modifiers

template <typename T>
constexpr bool is_string_v = std::is_same_v<std::remove_cvref_t<T>,std:: string>
                             || std::is_same_v<std::remove_cvref_t<T>, const char*>
                             || std::is_same_v<std::decay_t<T>, char*>;
                             
                             
template <typename T>
concept Container = requires(T&& a) //why use forward reference?
{
    {std::begin(a) -> std::iterator};
    {std::end(a) -> std::iterator};
};


template <typename T>
constexpr auto is_container_v = Container<T> && !is_string_v<T>;

                                
template <typename Node, typename TVisitor, typename ReturnType>
concept GoodVisitorPattern = requires(Node a, TVisitor v, ReturnType r){
    {a.accept(v) -> r};
};


template <typename Data, typename TVisitor>
concept Accepts = requires(Data&& a, TVisitor&& v){
    a.accept(v);
};
                                
template <typename Data, typename Visitor>
constexpr auto accepts_v = Accepts<Data, Visitor>;  // FIXME: check for Data::accept(Visitor) by using concepts or detection toolkit

#endif  // STATIC_VISITOR_META_HPP
