#include "UI.hpp"
#include "Exceptions.hpp"
#include "correct_input.cpp"
#include <iostream>
#include <fstream>

void UI::create_tree() {
    std::string surname;
    std::cout << "Enter Family surname:" << std::endl;
    std::cin >> surname;

    tree = new FamilyTree(surname);
    std::cout << "Family tree created!" << std::endl;
    main();
}


void UI::main() {
    bool flag = true;
    while(flag){
        std::cout << "Choose an option:" << std::endl;
        std::cout << "\t1. Add family member" << std::endl;
        std::cout << "\t2. Edit family member" << std::endl;
        std::cout << "\t3. Print info about family member" << std::endl;
        std::cout << "\t4. Print all members" << std::endl;
        std::cout << "\t5. Save family tree to a file" << std::endl;
        std::cout << "\t6 Exit program" << std::endl;
        int opt = correct_input<int>();

        switch (opt) {
            case 1:{
                add_member();
                break;
            }
            case 2:{
                try{
                    edit_member();
                }
                catch (EmptyTreeError &error){
                    std::cout << error.what() <<std::endl;
                    std::cout << "Try to add member!" << std::endl;
                }
                break;
            }
            case 3:{
                try{
                    print_member();
                }
                catch (EmptyTreeError &error){
                    std::cout << error.what() <<std::endl;
                    std::cout << "Try to add member!" << std::endl;
                }
                break;
            }
            case 4:{
                try{
                    print_all_members();
                }
                catch (EmptyTreeError &error){
                    std::cout << error.what() <<std::endl;
                    std::cout << "Try to add member!" << std::endl;
                }
                break;
            }
            case 5:{
                try{
                    save_tree();
                }
                catch (EmptyTreeError &error){
                    std::cout << error.what() <<std::endl;
                    std::cout << "Try to add member" << std::endl;
                }
                break;
            }
            case 6: {
                flag = false;
                break;
            }
            default:{
                std::cout << "No such option! Choose from list above:" << std::endl;
                break;
            }
        }
    }
}

// saves a members to a file. If empty throws error
void UI::save_tree() {
    if (tree == nullptr) throw EmptyTreeError();
    if (tree->get_members().is_empty()) throw EmptyTreeError();
    std::string filename;
    std::cout << "Enter file name:" << std::endl;
    std::cin >> filename;
    std::ofstream out("output.txt");
    auto members = tree->get_members();
    std::string name, birth_date, death_date;
    // Save all persons' data to file
    for (int i = 0; i < members.size(); i++) {
        name = members[i]->get_name();
        birth_date = members[i]->get_birth_date();
        death_date = members[i]->get_death();
        int age = members[i]->get_age();
        Gender gender = members[i]->get_gender();
        out << i << ';' << name << ';' << gender << ';' << birth_date
            << ';' << age << ';' << (death_date.empty() ? death_date : "-1") << '\n';
    }
    // define end of persons data
    out << "end" << '\n';
    // print all relations in form: person's index \n father mother\n spouse \n children
    for (int i = 0; i < members.size(); i++) {
        out << i << '\n';
        auto father = members[i]->get_father();
        auto mother = members[i]->get_mother();
        auto spouse = members[i]->get_spouse();
        auto children = members[i]->get_children();
        out << (father ? members.find(father) : -1) << ' ' << (mother ? members.find(mother) : -1) << '\n';
        out << (spouse ? members.find(spouse) : -1) << '\n';
        if (!children.is_empty()) {
            for (int j = 0; j < children.size(); j++) {
                out << members.find(children[j]) << ' ';
            }
        } else {
            out << -1;
        }
        out << '\n';
        out << "block" << '\n';
    }
    out << "end";

}

void UI::restore_tree() {
    std::cout << "Enter the file name:" << std::endl;
    std::string filename;
    std::cin >> filename;
    std::ifstream in(filename);
    tree = new FamilyTree();
    // Reading personal data. Adding to family members vector
    while (true) {
        std::string temp;
        in >> temp;
        if (temp == "end") break;

        // TODO: read and parse string, add family member
        std::string index, name, gender, birth_date, age, death_date;
    }

    // set relations
    auto members = tree->get_members();
    while (true) {
        std::string temp;
        in >> temp;
        int i, father, mother, spouse, child;
        if (temp == "end") break;
        i = std::stoi(temp);
        auto member = members[i];
        //TODO : Check if there is a relative
        in >> father >> mother >> spouse;
        member->set_father(members[father]);
        member->set_mother(members[mother]);
        member->set_spouse(members[spouse]);
        in >> temp;
        while (temp != "block") {
            child = std::stoi(temp);
            member->set_child(members[child]);
            in >> temp;
        }
    }

}

// prints all members 
void UI::print_all_members() {
    if(tree == nullptr) throw EmptyTreeError();
    if (tree->get_members().is_empty()) throw EmptyTreeError();
    auto members = tree->get_members();
    for (int i = 0; i < members.size(); i++) {
        std::cout << i << ". " << members[i]->get_name() << '\t' << members[i]->get_age() << "y.o." << std::endl;
    }

}

// prints info about one member
void UI::print_member() {
    if(tree == nullptr) throw EmptyTreeError();
    if (tree->get_members().is_empty()) throw EmptyTreeError();
    auto members = tree->get_members();
    std::cout << "Chose a person to get full info:" << std::endl;
    print_all_members();
    int index = correct_input<int>();
    while (index >= members.size() || index < 0) {
        std::cout << "Wrong input! No such index. Try again:" << std::endl;
        index = correct_input<int>();
    }

    auto person = members[index];
    std::cout << person->get_name() << std::endl;
    std::cout << (person->get_gender() == FEMALE ? "Woman" : "Man") << std::endl;
    std::cout << person->get_age() << "y.o." << std::endl;
    std::cout << "birthday: " << person->get_birth_date() << std::endl;
    if (!person->get_death().empty()) std::cout << person->get_death() << std::endl;

    if(person->get_father() != nullptr) std::cout << "Father:" << person->get_father()->get_name() << std::endl;
    if(person->get_mother() != nullptr) std::cout << "Mother:" << person->get_mother()->get_name() << std::endl;
    if(person->get_spouse() != nullptr) std::cout << "Spouse:" << person->get_spouse()->get_name() << std::endl;
    if (!person->get_children().is_empty()) {
        std::cout << "Children:" << std::endl;
        auto children = person->get_children();
        for (int i = 0; i < children.size(); i++) {
            std::cout << children[i]->get_name() << std::endl;
        }
    }
}

void UI::add_member() {
    auto member = new FamilyMember();
    std::cout << "Creating  new family member..." << std::endl;
    std::string temp, surname, name, mid_name;

    std::cout << "Input full name (in format: surname name mid_name):" << std::endl;
    std::cin >> surname >> name >> mid_name;
    temp = surname + ' ' + name + ' ' + mid_name;
    member->set_name(temp);

    std::cout << "Input age:" << std::endl;
    int age = correct_input<int>();
    member->set_age(age);

    std::cout << "Input birth date in format dd.mm.yyyy:" << std::endl;
    std::cin >> temp;
    member->set_birth_date(temp);

    int g;
    std::cout << "Input gender: 1 - Man, 2 - Woman:" << std::endl;
    g = correct_input<int>();
    member->set_gender((g == 1 ? MALE : FEMALE));

    char ans;
    std::cout << "Is person dead? Y/N" << std::endl;
    std::cin >> ans;
    if (ans == 'Y' || ans == 'y') {
        std::cout << "Input death date in format dd.mm.yyyy:" << std::endl;
        std::cin >> temp;
        member->set_birth_date(temp);
    }
    tree->append_family_member(member);
    std::cout << "Person created!" << std::endl;
}

void UI::edit_member() {
    if (tree == nullptr) throw EmptyTreeError();
    if (tree->get_members().is_empty()) throw EmptyTreeError();
    std::cout << "Choose who you want to edit:" << std::endl;
    int ans;
    print_all_members();
    ans = correct_input<int>();
    while (ans < 0 || ans >= tree->get_members().size()) {
        std::cout << "Wrong index, chose from the list above:" << std::endl;
        ans = correct_input<int>();
    }

    auto member = tree->get_members()[ans];
    bool flag = true;
    while (flag) {
        std::cout << "Choose who you want to add:" << std::endl;
        std::cout << "\t1. Father" << std::endl;
        std::cout << "\t2. Mother" << std::endl;
        std::cout << "\t3. Spouse" << std::endl;
        std::cout << "\t4. Child" << std::endl;
        std::cout << "\t5. Exit the menu." << std::endl;
        ans = correct_input<int>();
        switch (ans) {
            case 1: {
                std::cout << "Choose father from list:" << std::endl;
                print_all_members();
                int index = correct_input<int>();
                while (index < 0 || index >= tree->get_members().size() || tree->get_members()[index] == member){
                    std::cout << "No such index or chosen same person! Choose one from list above" << std::endl;
                    index = correct_input<int>();
                }
                try{
                    member->set_father(tree->get_members()[index]);
                }
                catch (GenderError &error){
                    std::cout << "Can't set female as father! Try again!" << std::endl;
                }
                break;
            }
            case 2: {
                std::cout << "Choose mother from list:" << std::endl;
                print_all_members();
                int index = correct_input<int>();
                while (index < 0 || index >= tree->get_members().size() || tree->get_members()[index] == member){
                    std::cout << "No such index or chosen same person! Choose one from list above" << std::endl;
                    index = correct_input<int>();
                }
                try{
                    member->set_mother(tree->get_members()[index]);
                }
                catch (GenderError &error){
                    std::cout << "Can't set male as mother! Try again!" << std::endl;
                }
                break;
            }
            case 3: {
                std::cout << "Choose spouse from list:" << std::endl;
                print_all_members();
                int index = correct_input<int>();
                while (index < 0 || index >= tree->get_members().size() || tree->get_members()[index] == member){
                    std::cout << "No such index or chosen same person! Choose one from list above" << std::endl;
                    index = correct_input<int>();
                }
                try{
                    member->set_spouse(tree->get_members()[index]);
                }
                catch (GenderError &error){
                    std::cout << "Can't set the same gender person as spouse! Try again!" << std::endl;
                }
                break;
            }
            case 4: {
                std::cout << "Choose child from list:" << std::endl;
                print_all_members();
                int index = correct_input<int>();
                while (index < 0 || index >= tree->get_members().size() || tree->get_members()[index] == member){
                    std::cout << "No such index or chosen same person! Choose one from list above" << std::endl;
                    index = correct_input<int>();
                }

                member->set_child(tree->get_members()[index]);
                break;
            }
            case 5:{
                flag = false;
                break;
            }
            default:{
                std::cout << "No such option!" << std::endl;
                break;
            }

        }

    }

}
