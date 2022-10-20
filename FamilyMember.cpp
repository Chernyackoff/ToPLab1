#include "FamilyMember.hpp"
#include "Exceptions.hpp"

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
    spouse = source.spouse;
    gender = source.gender;
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
    std::swap(spouse, source.spouse);
    gender = source.gender;
    return *this;
}

FamilyMember::FamilyMember(FamilyMember &&source) noexcept : Person(source) {
    std::swap(mother, source.mother);
    std::swap(father, source.father);
    std::swap(children, source.children);
    std::swap(spouse, source.spouse);
    gender = source.gender;
}

void FamilyMember::print(std::ostream &stream) const {
    stream << name << ';' << birth_date << ';' << age << ';' << (death_date.empty() ? "alive" : death_date);
}

std::ostream &operator<<(std::ostream &stream, const FamilyMember &fm) {
    fm.print(stream);
    return stream;
}

void FamilyMember::set_father(FamilyMember *person) {
    if (person->gender != MALE) throw GenderError();
    father = person;
    person->set_child(this);
}

void FamilyMember::set_mother(FamilyMember *person) {
    if (person->gender != FEMALE) throw GenderError();
    mother = person;
    person->set_child(this);
}

void FamilyMember::set_spouse(FamilyMember *person) {
    if(gender == person->gender) throw GenderError();
    if(spouse == person) return;
    spouse = person;
    person->spouse = this;
}

void FamilyMember::set_child(FamilyMember *person) {
    children.append(person);
    if (gender == MALE) person->set_father(this);
    else if(gender == FEMALE) person->set_mother(this);
}

FamilyMember *FamilyMember::get_father() {
    return father;
}

FamilyMember *FamilyMember::get_mother() {
    return mother;
}

FamilyMember *FamilyMember::get_spouse() {
    return spouse;
}

Vector<FamilyMember *> &FamilyMember::get_children(){
    return children;
}

Gender FamilyMember::get_gender() {
    return gender;
}

void FamilyMember::set_gender(Gender g) {
    gender = g;
}



