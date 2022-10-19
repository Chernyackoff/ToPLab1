#ifndef LAB1_UI_HPP
#define LAB1_UI_HPP

#include <string>
#include <iostream>
#include "FamilyTree.hpp"

class UI {
private:
    FamilyTree *tree = nullptr;
public:
    void create_tree();

    void main();

    void restore_tree();

    void save_tree();

    void edit_member();

    void add_member();

    void print_member();

    void print_all_members();

};

#endif //LAB1_UI_HPP
