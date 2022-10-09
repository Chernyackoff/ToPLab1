#include "FamilyMember.hpp"

FamilyMember::FamilyMember(std::string &nm, std::string &bd, int a, Gender g) : Person(nm, bd, a), children() {
    mother = nullptr;
    father = nullptr;
    spouse = nullptr;
    gender = g;
}

FamilyMember &FamilyMember::operator=(const FamilyMember &source) {
    if (this == &source) return *this;
    Person::operator=(source);
    mother = source.mother;
    father = source.father;
    children = source.children;
    return *this;
}

FamilyMember::FamilyMember(const FamilyMember &source) {
    *this = source;
}

FamilyMember &FamilyMember::operator=(FamilyMember &&source) noexcept {
    Person::operator=(source);
    std::swap(mother, source.mother);
    std::swap(father, source.father);
    std::swap(children, source.children);
    return *this;
}

FamilyMember::FamilyMember(FamilyMember &&source) : Person(source) {
    std::swap(mother, source.mother);
    std::swap(father, source.father);
    std::swap(children, source.children);
}

void FamilyMember::print(std::ostream &stream) const {
    stream << name << ';' << birth_date << ';' << age << ';' << (death_date.empty() ? "alive" : death_date);
}

std::ostream &operator<<(std::ostream &stream, const FamilyMember &fm) {
    fm.print(stream);
    return stream;
}

void FamilyMember::set_father(FamilyMember *person) {
    if (person->gender != MALE) throw "GenderError";
    father = person;
}

void FamilyMember::set_mother(FamilyMember *person) {
    if (person->gender != FEMALE) throw "GenderError";
    mother = person;
}

void FamilyMember::set_spouse(FamilyMember *person) {
    if(gender == person->gender) throw "GenderError";
    spouse = person;
}

void FamilyMember::set_child(FamilyMember *person) {
    children.append(person);
}



