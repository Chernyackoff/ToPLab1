#ifndef LAB1_FAMILYMEMBER_HPP
#define LAB1_FAMILYMEMBER_HPP

#include "Person.hpp"
#include "Vector.cpp"

enum Gender{
    MALE,
    FEMALE
};

class FamilyMember : public Person {
private:
    FamilyMember *mother;
    FamilyMember *father;
    FamilyMember *spouse;
    Gender gender;
    Vector<FamilyMember *> children;
protected:
    void print(std::ostream& stream) const override;
public:
    FamilyMember() = default;

    FamilyMember(std::string &nm, std::string &bd, int a, Gender g);

    FamilyMember(const FamilyMember &source);

    FamilyMember(FamilyMember &&source) noexcept ;

    ~FamilyMember() = default;

    FamilyMember &operator=(const FamilyMember &source);

    FamilyMember &operator=(FamilyMember &&source) noexcept;

    friend std::ostream &operator<<(std::ostream &stream, const FamilyMember& fm);

    void set_father(FamilyMember* person);
    void set_mother(FamilyMember* person);
    void set_spouse(FamilyMember* person);
    void set_child(FamilyMember* person);

    FamilyMember* get_father();
    FamilyMember* get_mother();
    FamilyMember* get_spouse();
    Gender get_gender();
    Vector<FamilyMember*>& get_children();
};

#endif //LAB1_FAMILYMEMBER_HPP
