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
void Tribu::displayPopulation(int nbColonnes){
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
        //affichage des scores
        for(int i = cptClavier; i<nbCol + cptClavier; i++){
            if(i < this->count){
                cout << "       " << population[i].getScore() << "       ";
            }
        }

        cout << endl << endl;

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


//croise les meilleurs de la population entre eux
//selon l'état du bit de remplacement, on remplace les parents par leurs enfants, ou alors on garde les parents et on remplace les pires par les enfants
void Tribu::croiserPopulation(int percentageDeMeilleurs, bool remplacerParents){
    if(percentageDeMeilleurs > 50 && !remplacerParents){
        cerr << "Stratégie impossible: Trop de progénitures pour remplacer les non-parents sans augmenter la population" << endl;
    }

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
    vector<Clavier> ensembleSuccesseurs;
    for(vector<Clavier> couple : coupleClaviers){
        Clavier successeur;
        successeur.blank();
        vector<int> touchesCommunes;
        //si une lettre est à la même place dans les deux, on la garde
        for(int j = 0; j < 40; j++){
            if(couple.at(0).getTouche(j) == couple.at(1).getTouche(j) && couple.at(1).getTouche(j) != '.'){
                successeur.setTouche(j, couple.at(0).getTouche(j));
                touchesCommunes.push_back(j);
            }
        }
        //sinon, on croise les touches en prenant au pif le parent chez qui on garde
        for(int j = 0; j < 40 && find(touchesCommunes.begin(), touchesCommunes.end(), j) == touchesCommunes.end(); j++){
            srand(time(NULL)+j);
            successeur.setTouche(j, couple.at(rand()%2).getTouche(j));
        }
        successeur.correctErrors();
        ensembleSuccesseurs.push_back(Clavier(successeur));
    }

    if(remplacerParents){ //on remplace les parent par leurs enfants
        for(int i = 0; i < ensembleSuccesseurs.size(); i++){
            population[i] = ensembleSuccesseurs.at(i);
        }
    } else{ //on remplace les autres de la population par leurs enfants
        for(int i = 0; i < ensembleSuccesseurs.size(); i++){ //ARCHI PAS TESTÉ
            population[count - i -1] = ensembleSuccesseurs.at(i);
        }
    }
    

    this->sortByBest();
}

void Tribu::sortByBest(){
    //copie du tableau
    Clavier temp[count];
    for(int i = 0; i < count; i++){
        temp[i] = population[i];
    }

    vector<int> res = this->jeVeuxLesMeilleurs(100);

    if(res.size() != count) cerr << "Erreur taille res" << endl;

    //implantation des meilleurs
    for(int i = 0; i < count; i++){
        population[i] = temp[res.at(i)];
    }
}

//modifier pour accueillir une probabilité à la gauss?
void Tribu::mutation(int percentage, int maxMutations){
    for(int i = 0; i < count*percentage / 100; i++){
        population[rand() % count].mutationAleatoire(rand()%maxMutations); //à changer, gros n'importe quoi de mettre 4 mutations max
    }
}

//TODO : comprendre pourquoi ca marche pas!
//Si deux calviers sont identiques, on mute un des deux
//On ne traite que ceux qu'on croise pour économiser du cpu: les autres ne seront que peu ou pas atteints
void Tribu::eliminerConsanguinité(int maxPercentageConsanguin, int percentageCroisement){
    int nbConsanguins = (int)count * maxPercentageConsanguin/100;
    int champiooooons = (int)count * percentageCroisement/100; //autocorrect en sueur
    for(int i = 0; i < count; i++){
        for(int j = 0; j < i; j++){
            if(population[j].equals(population[i])){
                if(nbConsanguins>0){
                    nbConsanguins--;
                    cout << "nbConsanguins = " << nbConsanguins << endl;
                } else {
                    population[i].mutationAleatoire(1); //une seule permutation devrait suffire
                    cout << "mutation d'un consanguin" << endl;
                }
            } 
        }
    }

}

//renvoi le meilleur score de la tribu actuelle
//on suppose que la tribu a été triée
float Tribu::getHighScore(){
    return population[0].getScore();
}