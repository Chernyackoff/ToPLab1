#include "FamilyTree.hpp"

FamilyTree::FamilyTree(std::string sn) {
    surname = std::move(sn);
}

FamilyTree &FamilyTree::operator=(const FamilyTree &source) {
    if (this == &source) return *this;
    surname = source.surname;
    members = source.members;
    root = source.root;
    return *this;
}

FamilyTree::FamilyTree(const FamilyTree &source) {
    *this = source;
}

FamilyTree &FamilyTree::operator=(FamilyTree &&source) noexcept {
    std::swap(surname, source.surname);
    std::swap(members, source.members);
    std::swap(root, source.root);
    return *this;
}

FamilyTree::FamilyTree(FamilyTree &&source) noexcept {
    std::swap(surname, source.surname);
    std::swap(members, source.members);
    std::swap(root, source.root);
}

FamilyTree::FamilyTree(std::string sn, FamilyMember *rt) {
    root = rt;
    surname = std::move(sn);
}

FamilyTree::FamilyTree(FamilyMember *rt) {
    root = rt;
}

void FamilyTree::set_surname(std::string sn) {
    surname = std::move(sn);
}

std::string FamilyTree::get_surname() {
    return surname;
}

void FamilyTree::set_root(FamilyMember *person) {
    root = person;
}

FamilyMember *FamilyTree::get_root() {
    return root;
}

Vector<FamilyMember *> &FamilyTree::get_members() {
    return members;
}

void FamilyTree::append_family_member(FamilyMember *new_member) {
    members.append(new_member);
}
