#ifndef CLAVIER_HPP
#define CLAVIER_HPP

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

class Clavier {
public:
Clavier(); //constructeur par défaut
Clavier(int ajoutEntropie); // constructeur avec ajout de hasard
void randomize(int ajoutEntropie);
char getTouche(int ln, int col);
char getTouche(std::vector<int> index);
void setTouche(int ln, int col, char newTouche);
void setTouche(std::vector<int> index, char newTouche);
std::string affichageClavier();
std::vector<int> getKeyCoordinates(char touche);
float getDistanceBetweenKeys(char touche1, char touche2);
float getScore();
std::string getStringLigne(int ligne);


private:
    char touches[40];
};

#endif