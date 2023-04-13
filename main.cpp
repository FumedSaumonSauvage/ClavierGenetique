#include <iostream>
#include <stdlib.h>
#include "clavier.hpp"
#include "tribu.hpp"
#include <vector>
#include <unistd.h>



using namespace std;

int main(int argc, char* argv[]) {
    int nbIndividus, tailleLigne, sort;

    int nbiterations = 1000;
    int percentageConsanguinite = 5;
    int percentageCroisement = 30;
    int percentageMutation = 50;
    int nbMaxMutations = 4;

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

    for(int i = 0; i < nbiterations; i++){
        cout << "Croisement " << i << " sur " << nbiterations << endl;
        t.croiserPopulation(percentageCroisement, false); //stratégie de remplacement : écrasement des parents
        t.mutation(percentageMutation, nbMaxMutations);
        t.eliminerConsanguinité(percentageConsanguinite); //par défaut on accepte 5% de consanguinité
        t.displayPopulation(0, tailleLigne);
        usleep(100000);
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




//TODO : ajouter la stratégie de remplacement "si l'enfant n'est pas meilleur que la moyenne de ses parents, il est éliminé".