#include "clavier.hpp"
#include <stdlib.h>
#include <vector>
#include <string>
#include <cctype> //toupper
#include <time.h> //init rand

using namespace std;

Clavier::Clavier() {
    this->randomize();
}

//reset le clavier dans un état au hasard
void Clavier::randomize() {
    srand (time(NULL));
    char packTouches[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    
    //on remplit le clavier avec du "rien" (*)
    for(int i = 0; i < 40; i++) touches[i] = '.';

    //on place les nouvelles touches
    for(int i = 0; i < 26; i++){
        int ln = rand() %4 +1;
        int cl = rand() %10 +1;
        vector<int> index = {ln, cl}; //implémentation giga stupide, à revoir etu utiliser la fonction à 2 param
        while(this->getTouche(index) != '.'){ //si c'est pas un caractère filler, on ne doit pas rempacer la touche
            index = {rand() %4 + 1, rand() %10 + 1};
        }
        this->setTouche(index, packTouches[i]);
    }

}

//accès à une touche par un vecteur, la premeire dimension est une ligne et la seconde une colonne
char Clavier::getTouche(vector<int> index){
    return touches[(index.at(0) - 1)*10 + index.at(1) -1];
}

char Clavier::getTouche(int ln, int col){
    return touches[(ln - 1)*10 + col -1];
}

void Clavier::setTouche(vector<int> index, char newTouche){
    touches[(index.at(0) - 1)*10 + index.at(1) -1] = newTouche;
}

void Clavier::setTouche(int ln, int col, char newTouche){
    touches[(ln - 1)*10 + col -1] = newTouche;
}

//renvoie les coordonnées d'une touche en particulier sur le clavier (origine en haut à gauche)
//NOTE : marche aussi avec la touche en minuscule
std::vector<int> Clavier::getKeyCoordinates(char touche){
    char maj = toupper(touche);
    for(int i = 1; i <=4; i++){
        for(int j = 1; j <=10; j++){
            if(maj == this->getTouche(i, j)) return {i, j};
        }
    }
    return {-1, -1};
}

//carré de la distance euclidienne entre deux touches du clavier
float Clavier::getDistanceBetweenKeys(char touche1, char touche2){
    float t1x = this->getKeyCoordinates(touche1).at(0);
    float t2x = this->getKeyCoordinates(touche2).at(0);
    float t1y = this->getKeyCoordinates(touche1).at(1);
    float t2y = this->getKeyCoordinates(touche2).at(1);
    return (t1x - t2x)*(t1x - t2x) + (t1y - t2y)*(t1y - t2y);
}