#ifndef LAB1_PERSON_HPP
#define LAB1_PERSON_HPP

#include <string>
#include <utility>

class Person {
protected:
    std::string name;
    std::string birth_date;
    std::string death_date;
    int age = 0;

    virtual void print(std::ostream& stream) const = 0;

public:
    Person() = default;

    Person(const Person &copy);

    Person(Person &&source) noexcept;

    Person(std::string &nm, std::string &bd, int a);

    ~Person() = default;

    void set_name(std::string &n);

    void set_birth_date(std::string bd);

    void set_death(std::string dd);

    void set_age(int a);

    const std::string &get_name();

    const std::string &get_birth_date();

    const std::string &get_death();

    int get_age();

    Person &operator=(const Person &source);

    Person &operator=(Person &&source) noexcept;
};


#endif //LAB1_PERSON_HPP
