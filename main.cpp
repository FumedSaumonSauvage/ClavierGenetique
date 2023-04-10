#include <iostream>
#include <stdlib.h>
#include "clavier.hpp"
#include "tribu.hpp"

using namespace std;

//obsolète, que pour du débug
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
    Tribu t(30);
    t.displayPopulation(0, 5);
    return 0;
}


//TODO : implémenter le tri dans l'affichage de la population
//TODO : ajouter de l'entropie dans le générateur de hasard de la population