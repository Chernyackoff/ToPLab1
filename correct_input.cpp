#include <iostream>
#include <numeric>

template <typename T>
T correct_input(){
    T temp;
    std::cin >> temp;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // fool proofing
        std::cout << "Wrong input! Enter correct value" << std::endl;
        std::cin >> temp;
    }
    return temp;
}


