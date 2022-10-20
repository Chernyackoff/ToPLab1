#ifndef LAB1_FAMILYTREE_HPP
#define LAB1_FAMILYTREE_HPP

#include <string>
#include "FamilyMember.hpp"

class FamilyTree {
private:
    std::string surname;
    Vector<FamilyMember *> members;
public:
    FamilyTree() = default;

    ~FamilyTree() = default;

    explicit FamilyTree(std::string sn);

    FamilyTree(const FamilyTree &source);

    FamilyTree(FamilyTree &&source) noexcept;

    FamilyTree &operator=(const FamilyTree &source);

    FamilyTree &operator=(FamilyTree &&source) noexcept;

    void set_surname(std::string sn);

    std::string get_surname();

    Vector<FamilyMember *> &get_members();

    void append_family_member(FamilyMember *new_member);
};

#endif //LAB1_FAMILYTREE_HPP
