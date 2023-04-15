#include <iostream>
#include <stdlib.h>
#include "clavier.hpp"
#include "tribu.hpp"
#include "liste.cpp"
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

//variables globales pour les options
int nbiterations = 1000;
int percentageConsanguinite = 5;
int percentageCroisement = 30;
int percentageMutation = 80;
int nbMaxMutations = 5;
int nbIndividus = 50;
int tailleLigne = 7;
int waitTime = 1;


void options(int argc, char* argv[]){
    for(int i = 1; i < argc; i++){
        string s = argv[i];
        if(s == "--nbIterations"){
            nbiterations = atoi(argv[i+1]);
        }else if(s == "--percentageConsanguinite"){
            percentageConsanguinite = atoi(argv[i+1]);
        }else if(s == "--percentageCroisement"){
            percentageCroisement = atoi(argv[i+1]);
        }else if(s == "--percentageMutation"){
            percentageMutation = atoi(argv[i+1]);
        }else if(s == "--nbMaxMutations"){
            nbMaxMutations = atoi(argv[i+1]);
        }else if(s == "--nbIndividus"){
            nbIndividus = atoi(argv[i+1]);
        }else if(s == "--tailleLigne"){
            tailleLigne = atoi(argv[i+1]);
        }else if(s == "--waitTime"){
            waitTime = atoi(argv[i+1]);
        }
    }    
}


int main(int argc, char* argv[]) {

    options(argc, argv); //charge les options si elles sont définies
            
    Tribu t(nbIndividus);
    t.sortByBest();
    t.displayPopulation(tailleLigne);

    vector<float> highScores; //contient la liste de tous les scores
    int cptIteration = 0;

    //DAMAGE CONTROL POUR RENDU TANT QUE CONVERGENCE CASSÉE
    float valeurConvergence = 0;
    nbiterations = 500;
    //CCHANGER À 1e-40 et 1000 LES VALEURS SI CONVERGENCE FONCTIONNELLE


    while(!t.convergence(valeurConvergence) && cptIteration < nbiterations){
        cout << "Croisement " << cptIteration << " sur " << nbiterations << endl;
        t.croiserPopulation(percentageCroisement, false); //stratégie de remplacement : écrasement des parents
        t.mutation(percentageMutation, nbMaxMutations);
        t.eliminerConsanguinite(percentageConsanguinite, percentageCroisement); //par défaut on accepte 5% de consanguinité
        t.displayPopulation(tailleLigne);
        highScores.push_back(t.getHighScore());

        cptIteration++;
    }



    //selection finale
    cout << "Resultat final:" << endl;
    t.sortByBest();
    t.displayPopulation(tailleLigne);

    cout << "Fin exec par: ";
    if(cptIteration >= 999){
        cout << "limite d'iterations atteinte" << endl;
        cout << t.convergenceScore() << endl;
    }
    else{
        cout << "Convergence : ";
        cout << t.convergenceScore() << endl;
    }

    return 0;
}




//TODO : ajouter la stratégie de remplacement "si l'enfant n'est pas meilleur que la moyenne de ses parents, il est éliminé".