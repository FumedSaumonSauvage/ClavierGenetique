#include <iostream>
#include <stdlib.h>
#include "clavier.hpp"
#include "tribu.hpp"
#include <vector>
#include <unistd.h>

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
    t.sortByBest();
    t.displayPopulation(0, tailleLigne);

    for(int i = 0; i < 10; i++){
        t.croiserPopulation(30);
        t.displayPopulation(0, tailleLigne);
        cout << "Croisement " << i << endl;
        sleep(1); //mettre plus court
    }

    //test de la sélection
    cout << "Meilleurs: ";
    for(int i : t.jeVeuxLesMeilleurs(10)){
        cout << i << ", ";
    }
    cout << endl;

    cout << "fin exec" << endl;
    return 0;
}