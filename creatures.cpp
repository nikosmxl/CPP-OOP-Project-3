#include <iostream>
#include <cstring>
#include <ctime>
#include "creatures.h"

// Constructors/Destructors/Copy Constructors
Creature::Creature(const char* name1, int L1, info* place1){

    name = new char[strlen(name1) + 1];
    strcpy(name, name1);
    place = place1;

    L = L1;

    std::cout << "Constructed a Creature." << std::endl;
}

Creature::Creature(const Creature& creature1){
    name = new char[strlen(creature1.name) + 1];
    strcpy(name, creature1.name);

    L = creature1.L;

    std::cout << "Constructed a Creature by copy construction." << std::endl;
}

Creature::~Creature(){
    delete[] name;

    std::cout << "Destructed a Creature." << std::endl;
}

Good_Creature::Good_Creature(const char* name1, int L1, info* place1, int good_thrsh1) : Creature(name1, L1, place1){
    good_thrsh = good_thrsh1;

    std::cout << "Constructed a Good Creature." << std::endl;
}

Good_Creature::Good_Creature(const Creature& cr, int good_thrsh1) : Creature(cr) {
    good_thrsh = good_thrsh1;

    std::cout << "Constructed a Good Creature by helping copy constructor" << std::endl;
}

Bad_Creature::Bad_Creature(const char* name1, int L1, info* place1, int bad_thrsh1) : Creature(name1, L1, place1){
    bad_thrsh = bad_thrsh1;

    std::cout << "Constructed a Bad Creature." << std::endl;
}

Bad_Creature::Bad_Creature(const Creature& cr, int bad_thrsh1) : Creature(cr) {
    bad_thrsh = bad_thrsh1;

    std::cout << "Constructed a Good Creature by helping copy constructor" << std::endl;
}

Creature_Society::Creature_Society(int N_given, int L_given, int good_thrsh1, int bad_thrsh1){
    unsigned long currtime = time(NULL);
    srand( (unsigned int) currtime);
    
    //Creatures' names

    int number_of_names = 5;
    const char* goodnames[number_of_names] = {"God" , "Angel" , "White Soldier", "White Shooter" , "Good citizen"};
    const char* badnames[number_of_names] = {"Devil" , "Demon" , "Black Soldier" , "Black Shooter" , "Bad citizen"};
    
    // Variables' initialization
    N = N_given;
    good_thrsh = good_thrsh1;
    bad_thrsh = bad_thrsh1;
    good_creatures = 0;
    zombies = 0;

    // Society
    society = new info*[N];

    for (int i = 0 ; i < N ; i++){
        society[i] = new info;

        if (rand() % 2 == 0){
            std::string name = goodnames[i % number_of_names] + std::to_string(i + 1);
            const char* charname = name.c_str();
            society[i]->creat = new Good_Creature(charname, L_given, society[i], good_thrsh);
            good_creatures++;
        }
        else{
            std::string name = badnames[i % number_of_names] + std::to_string(i + 1);
            const char* charname = name.c_str();
            society[i]->creat = new Bad_Creature(charname, L_given, society[i], bad_thrsh);
        }
        society[i]->soc = this;
        society[i]->index = i;
    }
    
    std::cout << "Constructed a Creature Society." << std::endl;
}

Creature_Society::~Creature_Society(){
    for (int i = N - 1 ; i >= 0 ; i--){
        delete society[i]->creat;
        delete society[i];
    }

    delete[] society;

    std::cout << "Destructed a Creature Society." << std::endl;
}

bool Good_Creature::bless(void){
    Creature::bless();
    if (L > good_thrsh){
        return true;
    }
    
    return false;
}

bool Bad_Creature::bless(void){
    Creature::bless();
    if (L > bad_thrsh){
        return true;
    }

    return false;
}

bool Good_Creature::beat(void){
    
    if (Creature::beat() == false){
        return true;
    }

    return false;
}

bool Bad_Creature::beat(void){

    if (Creature::beat() == false){
        return true;
    }

    return true;
}

void Creature_Society::clone_next(int i){
    //Zombies and good_creatures info
    if (society[(i + 1) % N]->creat->is_a_zombie() == true){
        zombies--;
    }
    else if (society[(i + 1) % N]->creat->is_a_good() == true){
        good_creatures--;
    }

    //Cloning
    delete society[(i + 1) % N]->creat;
    society[(i + 1) % N]->creat = new Good_Creature(*(society[i]->creat), good_thrsh);
    good_creatures++;

    std::cout << "Cloned the " << i + 1 << "th creature to the next position" << std::endl;
}

void Creature_Society::clone_zombies(int i){
    // Cloning + zombies info
    for (int j = i + 1 ; j < N ; j++){
        if (society[j]->creat->is_a_zombie() == true){
            delete society[j]->creat;
            society[j]->creat = new Bad_Creature(*(society[i]->creat), bad_thrsh);
            zombies--;
        }
        else{
            break;
        }
    }

    std::cout << "Cloned the " << i + 1 << "th creature to all next zombies" << std::endl;
}

void Creature_Society::bless(int i){
    std::cout << "Blessing the " << i + 1 << "th creature" << std::endl;

    if (society[i]->creat->bless() == true){
        if (society[i]->creat->is_a_good() == true){
            clone_next(i);
        }
        else{
            clone_zombies(i);
        }
    }
    
}

void Creature_Society::beat(int i){
    std::cout << "Beating the " << i + 1 << "th creature" << std::endl;

    if (society[i]->creat->beat() == true){
        // If it was not a zombie before and now it is.
        if (society[i]->creat->is_a_zombie() == true){
            zombies++;
            // If it is a zombie its not a good creature anymore.
            if (society[i]->creat->is_a_good() == true){
                good_creatures--;
            }

        }
    }
    
}

unsigned int Creature_Society::no_of_good(void) const{
    return good_creatures;
}

unsigned int Creature_Society::no_of_zombies(void) const{
    return zombies;
}

