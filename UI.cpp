#include "UI.hpp"
#include "Exceptions.hpp"
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
//TODO
}

// saves a members to a file. If empty throws error
void UI::save_tree() {
    std::string filename;
    std::cout << "Enter file name:" << std::endl;
    std::cin >> filename;
    std::ofstream out("output.txt");
    if (tree->get_members().is_empty()) throw EmptyTreeError();
    auto members = tree->get_members();
    // Save all persons' data to file
    for (int i = 0; i < members.size(); i++) {
        out << i << ';' << members[i]->get_name() << ';' << members[i]->get_gender() << members[i]->get_birth_date()
            << ';' << members[i]->get_age() << ';' << members[i]->get_death() << '\n';
    }
    // define end of persons data
    out << "end" << '\n';
    // print all relations in form: person's index \n father mother\n spouse \n children
    for (int i = 0; i < members.size(); i++) {
        out << i << '\n';
        // TODO: check if not nullptr
        auto father = members[i]->get_father();
        auto mother = members[i]->get_mother();
        auto spouse = members[i]->get_spouse();
        auto children = members[i]->get_children();
        out << members.find(father) << ' ' << members.find(mother) << '\n';
        out << members.find(spouse) << '\n';
        for (int j = 0; j < children.size(); j++) {
            out << members.find(children[j]) << ' ';
        }
        out << '\n';
        out << "block";
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
        while(temp != "block"){
            child = std::stoi(temp);
            member->set_child(members[child]);
            in >> temp;
        }
    }

}
