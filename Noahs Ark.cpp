// Fasih Javed CIS 142 Programming Assignment 7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

class Animal {

public:
    string type, gender;
    int age;
    Animal(std::string type, std::string gender, int age = 0) {
        this->type = type;
        this->gender = gender;
        this->age = age;
    }
    
    virtual void ageMonth() {
        age++;
        }

    virtual bool inHeat() const = 0;

    virtual string get_species() = 0;

    string animalInfo() {
        if (age == 1) {
            return "I am a " + gender + " " + type + ", " + to_string(age) + " month old";
        }
        else {
            return "I am a " + gender + " " + type + ", " + to_string(age) + " months old";
        }
    }
};

class Mammal : public Animal {
public:
    Mammal(string species, string gender, int age = 0) : Animal(species, gender, age) {}

    bool inHeat() const override {
        return age > 0 && age % 12 == 0 && gender == "female";
    }

    string get_species() override {
        return type;
    }
};

class Fish : public Animal {
public:
    Fish(string species, string gender, int age = 0) : Animal(species, gender, age) {}

    bool inHeat() const override {
        return age > 0 && age % 6 == 0 && gender == "female";
    }

    string get_species() override {
        return type;
    }
};

class Bird : public Animal {
public:
    Bird(string species, string gender, int age = 0) : Animal(species, gender, age) {}

    bool inHeat() const override {
        return age > 0 && age % 9 == 0 && gender == "female";
    }

    string get_species() override {
        return type;
    }
};

class Ark {
public:
    Ark() {
        add_animal<Mammal>("cat", "female", 0);
        add_animal<Mammal>("cat", "male", 0);
        add_animal<Mammal>("dog", "female", 0);
        add_animal<Mammal>("dog", "male", 0);
        add_animal<Fish>("shark", "female", 0);
        add_animal<Fish>("shark", "male", 0);
        add_animal<Fish>("dolphin", "female", 0);
        add_animal<Fish>("dolphin", "male", 0);
        add_animal<Bird>("crow", "female", 0);
        add_animal<Bird>("crow", "male", 0);
        add_animal<Bird>("eagle", "female", 0);
        add_animal<Bird>("eagle", "male", 0);
    }

    void pass_month() {
        int initial_size = animals.size();
        for (int i = 0; i < initial_size; i++) {
            animals[i]->ageMonth();
            if (animals[i]->inHeat()) {
                add_random_animal(animals[i]->get_species(), 0);
            }
        }
        months++;
    }

    void check_inventory() {
        for (size_t i = 0; i < animals.size(); i++) {
            cout << "Animal #" << i + 1 << ": " << animals[i]->animalInfo() << endl;
        }
    }

    int get_months() {
        return months;
    }

private:
    vector<shared_ptr<Animal>> animals;
    int months = 0;


    void add_random_animal(string species, int age) {
        string gender = (rand() % 2 == 0) ? "male" : "female";
        if (species == "cat" || species == "dog") {
            animals.push_back(make_shared<Mammal>(species, gender, age));
        }
        else if (species == "shark" || species == "dolphin") {
            animals.push_back(make_shared<Fish>(species, gender, age));
        }
        else if (species == "crow" || species == "eagle") {
            animals.push_back(make_shared<Bird>(species, gender, age));
        }
    }
    
    template <typename T>
    void add_animal(string species, string gender, int age) {
        animals.push_back(make_shared<T>(species, gender, age));
    }
};


int main()
{
    srand(static_cast<unsigned>(time(0)));

    Ark ark;
    int choice;

    cout << "Welcome to Noah's Ark Inventory App!" << endl;
    cout << "Instructions for the game will be below!" << endl;

    do {
        cout << "You have been on the ark for " << ark.get_months() << " months" << endl;
        cout << "1 - Let another month pass" << endl;
        cout << "2 - Check inventory" << endl;
        cout << "3 - Quit" << endl;

        cin >> choice;

        switch (choice) {
        case 1:
            ark.pass_month();
            break;
        case 2:
            ark.check_inventory();
            break;

        case 3:
            cout << "Goodbye!" << endl;
            break;
        
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}