#ifndef LAB1_EXCEPTIONS_HPP
#define LAB1_EXCEPTIONS_HPP
#include <exception>
#include <stdexcept>

class GenderError: public std::runtime_error{
public:
    GenderError(): std::runtime_error("Wrong gender for family member!"){};
};

class EmptyTreeError: public std::runtime_error{
public:
    EmptyTreeError(): std::runtime_error("The Family tree is empty"){};
};

#endif //LAB1_EXCEPTIONS_HPP
