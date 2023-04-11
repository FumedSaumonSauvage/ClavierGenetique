#include <iostream>
#include <stdlib.h>
#include "clavier.hpp"
#include "tribu.hpp"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    int nbIndividus, tailleLigne, sort;
    if(argc>1){
        nbIndividus = atoi(argv[1]);
        tailleLigne = atoi(argv[2]);
        sort = 0;
    } else {
        nbIndividus = 50;
        tailleLigne = 10;
        sort = 0;
    }
    Tribu t(nbIndividus);
    t.displayPopulation(0, tailleLigne);

    //test de la sélection
    cout << "Meilleurs: ";
    for(int i : t.jeVeuxLesMeilleurs(10)){
        cout << i << ", ";
    }
    cout << endl;
    t.croiserPopulation(10);
    return 0;
}


//TODO : implémenter le tri dans l'affichage de la population