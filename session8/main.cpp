#include <iostream>

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>

template <typename T, typename = void>
struct is_container_t:std::false_type{};

template <typename T>
struct is_container_t<
        T,
        std::void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>
        >:std::true_type{};


template <typename T>
concept Container = requires(T a)
{
    std::begin(a),
    std::end(a);
};

template<Container T>
std::ostream& operator<<(std::ostream& os, const T& v)
{
    auto b = v.begin(), e = v.end();
    os << "{";
    if (b != e) {
        os << *b;
        while (++b != e)
            os << "," << *b;
    }
    return os << "}";
}

template<typename T>
// use std::remove_cvref to remove const, volatile, and reference qualifiers from the type
    constexpr bool is_string_v = std::is_same_v<std::remove_cvref_t<T>, std::basic_string<char>> ||  //it is a basic string
                                 (std::is_same_v<std::remove_cvref_t<T>, T> // it is not a pointer
                                  &&  std::is_same_v<typename T::value_type, char> // it is some container with value_type char 
                                  && !std::is_same_v<std::remove_cvref_t<T>, const char*>); //it is not c strings
                              
template <typename T, typename = std::enable_if_t<is_string_v<T>>>
void function_that_can_only_be_called_on_strings(const T& s) {
    std::cout << "function_that_can_only_be_called_on_strings called with " << s << std::endl;
}

template<typename T>
constexpr bool is_non_char_container = !is_string_v<T> && is_container_t<T>::value;


// create a function using is_non_string_container to check if the type is a container
template <typename T, typename = std::enable_if_t<is_non_char_container<T>>>
void function_on_non_string_containers(const T& s) {
    std::cout << "function_on_non_string_containers called with " << s << std::endl;
}

int main(){

    std::cout << std::vector{1,2,3} << std::endl; // should print "{1,2,3}"
    std::cout << std::vector{2.7,3.14} << std::endl; // should print "{2.7,3.14}"
    std::cout << std::vector{std::vector{"hello", "template"}, std::vector{"world"}} << std::endl;

    auto vec_of_strings = std::vector{"hello", "world"};
    auto vec_of_chars = std::vector{'a', 'b', 'c'};
    auto vec_of_ints = std::vector{1, 2, 3};

    auto arr_of_strings = std::array{"hello", "world"};
    auto arr_of_chars = std  ::array{'a', 'b', 'c'};
    auto arr_of_ints = std   ::array{1, 2, 3};


    std::cout << vec_of_strings << std::endl; // should print "{hello,world}"
    std::cout << arr_of_strings << std::endl; // should print "{hello,world}"
    std::cout << arr_of_chars<< std::endl; // should print "{a,b,c}"

    function_that_can_only_be_called_on_strings(vec_of_chars); // should compile
    function_that_can_only_be_called_on_strings(arr_of_chars); // should compile
    function_that_can_only_be_called_on_strings(vec_of_ints); // should not compile
    function_that_can_only_be_called_on_strings(arr_of_ints); // should not compile

    function_on_non_string_containers(vec_of_chars); // should not compile
    function_on_non_string_containers(arr_of_chars); // should not compile
    function_on_non_string_containers(arr_of_ints); // should compile
    function_on_non_string_containers(vec_of_ints); // should compile
}