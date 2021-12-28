#include <iostream>
#include <ctime>
#include "creatures.h"

int main(int argc, char *argv[]){

    if (argc != 6){
        std::cout << "Give the right data" << std::endl;
        return 1;
    }

    unsigned long currtime = time(NULL);
    srand( (unsigned int) currtime);

    const unsigned int N = std::stoi(argv[1]);              // Number of creatures
    const unsigned int M = std::stoi(argv[2]);              // Number of blessing and beatings
    const unsigned int L = std::stoi(argv[3]);              // Life of creatures
    const unsigned int good_thrsh = std::stoi(argv[4]);     // Good creatures cloning limit
    const unsigned int bad_thrsh = std::stoi(argv[5]);      // Bad creature cloning limit

    Creature_Society soc(N, L, good_thrsh, bad_thrsh);

    for (int i = 0 ; i < M ; i++){
        if (rand() % 2 == 0){
            soc.bless(rand() % N);
        }
        else{
            soc.beat(rand() % N);
        }
    }

    if (soc.no_of_good() == N){
        std::cout << "Good Dominates The World!" << std::endl;
    }
    else if(soc.no_of_zombies() == N){
        std::cout << "This is a dead society!" << std::endl;
    }
    else{
        std::cout << "Try again to improve the world!" << std::endl;
    }

    return 0;
}