#include "correct_input.cpp"
#include "UI.hpp"

int main() {
    UI ui;
    while (true) {
        std::cout << "Welcome to Family tree builder" << std::endl;
        std::cout << "\t1. Create a tree." << std::endl;
        std::cout << "\t2. Restore a tree from file." << std::endl;
        std::cout << "\t3. Exit." << std::endl;
        std::cout << "Choose an action:" << std::endl;

        int ans = correct_input<int>();
        switch (ans) {
            case 1:
                ui.create_tree();
                break;
            case 2:
                std::cout << "Not implemented yet!" << std::endl;
                //ui.restore_tree();
                break;
            case 3:
                return 0;
            default:
                std::cout << "Wrong input! Try again. Available actions 1 - 3" << std::endl;
                break;
        }
    }
}
