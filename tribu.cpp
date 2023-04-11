#include "tribu.hpp"
#include "clavier.hpp"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cctype> //toupper
#include <time.h> //init rand
#include <algorithm> //find

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

// "Non... Je veux les meilleurs"
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

    //prendre les meilleurs OK
    //faire des couples de tableaux dans le pif absolu OK
    //pour chaque couple de tableaux:
    //  si une lettre est en position dans les deux, la garder
    //  sinon, prendre une lettre de chaque tour à tour
    //corriger la sortie des tableaux:
    //  Remplacer les doublons par un point (pur pif)
    //  S'il manque une lettre quelque part, la caser au hasard parmis les points

    //on récupère les meilleurs
    int nbMeilleurs = percentageDeMeilleurs*count/100;
    Clavier lesMeilleurs[nbMeilleurs];
    int j = 0;
    for(int i : jeVeuxLesMeilleurs(percentageDeMeilleurs)){
        lesMeilleurs[j] =  getClavier(i);
        j++;
    }

    //on fait des couples de claviers dans le hasard le plus total
    vector<Clavier> coupleClaviers[nbMeilleurs]; //autant de couples que de champions, on peut faire un descendant par couple sans perte de population
    for(int i = 0; i < nbMeilleurs; i++){
        coupleClaviers[i].push_back(lesMeilleurs[i]);
        coupleClaviers[i].push_back(lesMeilleurs[rand() % nbMeilleurs]); //on a potentiellement deux fois le même clavier, mais ca arrive peu de fois sur un ensemble grand
    }

    //mixage génétique
    for(vector<Clavier> couple : coupleClaviers){
        Clavier successeur;
        successeur.blank();
        vector<int> touchesCommunes;
        //si une lettre es à la même place dans les deux, on la garde
        for(int j = 0; j < 40; j++){
            if(couple.at(0).getTouche(j) == couple.at(1).getTouche(j) && couple.at(1).getTouche(j) != '.'){
                successeur.setTouche(j, couple.at(0).getTouche(j));
                touchesCommunes.push_back(j);
            }
        }
        //sinon, on croise les touches en prenant au pif le parent chez qui on garde
        for(int j = 0; j < 40 && find(touchesCommunes.begin(), touchesCommunes.end(), j) == touchesCommunes.end(); j++){
            //zbeub zbeub
        }

    }
}