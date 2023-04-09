#include <iostream>
#include <stdlib.h>
#include "clavier.hpp"

using namespace std;

string affichageClavier(Clavier c){
    string res = "Clavier :\n";
    for(int j = 1; j<=4; j++){
        for(int i = 1; i <= 10; i++){
            res = res + " " + c.getTouche(j, i);
        }
        res = res + "\n";
    }
    return res;
}

int main() {
    std::cout << "Essentiellement, il n'y a rien." <<endl;
    Clavier c;
    std::cout << affichageClavier(c) << endl;
    float zebi = c.getDistanceBetweenKeys('a', 'b');
    std::cout << zebi << endl;
    return 0;
}


//TODO: revoir la base de l'algo génétique pur éviter de se planter dans les probabilités de mutation, et revoir comment on fait du crossing over