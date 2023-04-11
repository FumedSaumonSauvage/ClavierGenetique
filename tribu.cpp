#include "tribu.hpp"
#include "clavier.hpp"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cctype> //toupper
#include <time.h> //init rand

using namespace std;

Tribu::Tribu(int cardinal){
    this->count = (cardinal < 500) ? cardinal : 500; //max 500 individus
    for(int i = 0; i < this->count; i++){
        this->population[i] = Clavier(i);
    }
}

int Tribu::getCount(){
    return this->count;
}

Clavier Tribu::getClavier(int index){
    if(index >= this->count) cerr << "Index d'accès aux claviers trop grand!" << endl;
    return population[index];
}

//affiche à l'écran la population de claviers
//sort = 0: pas de tri ; sort = 1 : tri par meilleur ; sort = 3: tri par pire
//nbColonnes : nombre de claviers en largeur à afficher
void Tribu::displayPopulation(int sort, int nbColonnes){

    //IMPLÉMENTER LE TRI!!!!!!

    int nbCol = (nbColonnes>0) ? nbColonnes : 1 ;
    int cptClavier = 0;
    while(cptClavier < this->count){
        for(int ligne = 1; ligne <=4; ligne++){
            string res = "";
            for(int i = cptClavier; i<nbCol + cptClavier; i++){
                if(i < this->count){
                    res = res + population[i].getStringLigne(ligne) + "     ";
                }
            }
            cout << res << endl;
        }
        cout << endl;

        cptClavier+=nbCol;
    }
}

// "Non... Il me faut les meilleurs"
// Renvoie les indices des individus dans le top X%, X en paramètre
vector<int> Tribu::jeVeuxLesMeilleurs(int percentage){
    float scores[this->count];
    for(int i = 0; i < this->count; i++){
        scores[i] = population[i].getScore();
    }
    vector<int> res;
    for(int i = 0; i < percentage*count/100; i++){
        float max = -1;
        int indiceMax = 0;
        for(int j = 0; j < this->count; j++){
            if(max < scores[j]){
                indiceMax = j;
                max = scores[j];
            }
        }
        res.push_back(indiceMax);
        scores[indiceMax] = -1;
    }
    return res;
}

void Tribu::croiserPopulation(int percentageDeMeilleurs){
    //prendre les meilleurs
    //faire des couples de tableaux dans le pifa bsolu
    //pour chaque couple de tableaux:
    //  si une lettre est en position dans les deux, la garder
    //  sinon, prendre une lettre de chaque tour à tour
    //corriger la sortie des tableaux:
    //  Remplacer les doublons par un point (pur pif)
    //  S'il manque une lettre quelque part, la caser au hasard parmis les points
    
}