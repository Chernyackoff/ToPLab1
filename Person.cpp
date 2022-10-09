#include "Person.hpp"

Person::Person(std::string &nm, std::string &bd, int a) {
    name = std::move(nm);
    birth_date = std::move(bd);
    age = a;

}

// Copy constructor
Person::Person(const Person &copy) {
    *this = copy;
}

// Move constructor
Person::Person(Person &&source) noexcept {
    name = std::move(source.name);
    birth_date = std::move(source.birth_date);
    age = source.age;
    if (!source.death_date.empty()) {
        death_date = std::move(source.death_date);
    }
}

void Person::set_name(std::string &n) {
    name = std::move(n);
}

void Person::set_birth_date(std::string bd) {
    birth_date = std::move(bd);
}

void Person::set_death(std::string dd) {
    death_date = std::move(dd);
}

void Person::set_age(int a) {
    age = a;
}

Person &Person::operator=(const Person &source) {
    if (this == &source) return *this;
    name = source.name;
    birth_date = source.birth_date;
    age = source.age;
    if (!source.death_date.empty()) {
        death_date = source.death_date;
    }
    return *this;
}

Person &Person::operator=(Person &&source) noexcept {
    name = std::move(source.name);
    birth_date = std::move(source.birth_date);
    age = source.age;
    if (!source.death_date.empty()) {
        death_date = std::move(source.death_date);
    }
    return *this;
}

const std::string &Person::get_name() {
    return name;
}

const std::string &Person::get_birth_date() {
    return birth_date;
}

const std::string &Person::get_death() {
    return death_date;
}

int Person::get_age() {
    return age;
}


