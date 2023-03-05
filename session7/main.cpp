#include <iostream>
#include <vector>
#include <iomanip>
#include <list>

//Declare a function print taking vector<int> argument, which prints 
//the elements in a comma-separated-format inside curly braces
void print(const std::vector<int>& vector){
    auto end = vector.size() - 1;
    std::cout << "{";
    for (int i = 0; i < end; ++i) std::cout << vector.at(i) << ',';
    std::cout << vector.back();
    std::cout << "}" << std::endl;
}

//Change the print function signature into 
// an output operator<< for the vector<int> type, test it:
std::ostream& operator<<(std::ostream &os, const std::vector<int> &vector ){
    auto end = vector.size() - 1;
    os << "{";
    for (int i = 0; i < end; ++i) os << vector.at(i) << ',';
    os << vector.back();
    os << "}";
    return os;
}

//    Generalize: change the operator into template operator (template function),
//    where the argument is a std::vector may hold arbitrary (printable) type, test:
template<class T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &vector ){
    auto end = vector.size() - 1;
    os << "{";
    for (int i = 0; i < end; ++i) os << vector.at(i) << ',';
    os << vector.back();
    os << "}";
    return os;
}
// Two template params, one called C. typename e_t = typename C::value_type: This declares a second template parameter
// e_t of type typename, which is optional and has a default value of typename C::value_type
// By defaulting e_t to typename C::value_type, we ensure that e_t represents 
// the same type as the container's element type, unless a different type is explicitly specified.
// This allows us to avoid explicitly specifying the element type when it can be deduced from the container type.
template<typename C, typename e_t = typename C::value_type>
std::ostream& operator<<(std::ostream &os, const C& container ) {
    auto end = std::end(container);
    for (const e_t& a : container) {
        //if the type is a char* (c string)
        if constexpr (std::is_same_v<typename C::value_type, char*> 
                || std::is_same_v<typename C::value_type, char[]>) {
            os << std::quoted(a);
        } else {
            os << a;
        }
    }

    return os;
}



int main() {
    print({1,2,3,4});
    auto q = std::vector{1, 2, 3, 4};
    std::cout << std::vector{1, 2, 3, 4} << std::endl;
    std::cout << std::vector{2.7,3.14} << std::endl; // should print "{2.7,3.14}"
    std::cout << std::vector{{"hello", "template"}, std::vector{"world"}} << std::endl;
    std::cout << std::list<int> {1, 2, 3, 4, 5} << std::endl;
    std::cout << std::list<char*> {"Hello", "there"} << std::endl;
    return 0;
}
