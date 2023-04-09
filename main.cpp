#include <iostream>
#include <stdlib.h>
#include "clavier.hpp"

using namespace std;

string affichageClavier(Clavier c){
    string res = "";
    for(int j = 1; j<=4; j++){
        for(int i = 1; i <= 10; i++){
            res = res + " " + c.getTouche(i, j);
        }
        res = res + "\n";
    }
    return res;
}

int main() {
    std::cout << "Essentiellement, il n'y a rien.";
    Clavier c;
    std::cout << affichageClavier(c);
    return 0;
}


//TODO: implémenter les états d'un clavier (créer une classe clavier?)
//TODO: définir une norme sur le clavier puis sa distance associée (voir pour un truc qui marche en diagonale, genre distance euclidienne)
//TODO: faire un affichage à peu pres clair
//TODO: revoir la base de l'algo génétique pur éviter de se planter dans les probabilités de mutation, et revoir comment on fait du crossing over