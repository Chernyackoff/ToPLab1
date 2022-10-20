#include "FamilyTree.hpp"

FamilyTree::FamilyTree(std::string sn) {
    surname = std::move(sn);
}

FamilyTree &FamilyTree::operator=(const FamilyTree &source) {
    if (this == &source) return *this;
    surname = source.surname;
    members = source.members;
    return *this;
}

FamilyTree::FamilyTree(const FamilyTree &source) {
    *this = source;
}

FamilyTree &FamilyTree::operator=(FamilyTree &&source) noexcept {
    std::swap(surname, source.surname);
    std::swap(members, source.members);
    return *this;
}

FamilyTree::FamilyTree(FamilyTree &&source) noexcept {
    std::swap(surname, source.surname);
    std::swap(members, source.members);
}

void FamilyTree::set_surname(std::string sn) {
    surname = std::move(sn);
}

std::string FamilyTree::get_surname() {
    return surname;
}

Vector<FamilyMember *> &FamilyTree::get_members() {
    return members;
}

void FamilyTree::append_family_member(FamilyMember *new_member) {
    members.append(new_member);
}
