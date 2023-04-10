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
    int nbCol = (nbColonnes>0) ? nbColonnes : 1 ;
    int cptClavier = 0;
    while(cptClavier < this->count){
        for(int ligne = 1; ligne <=4; ligne++){
            string res = "";
            for(int i = cptClavier; i<nbCol + cptClavier; i++){
                //get ligne clavier
                res = res + population[i].getStringLigne(ligne) + "     ";
            }
            cout << res << endl;
        }
        cout << endl;

        cptClavier+=nbCol;
    }
}