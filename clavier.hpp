#ifndef CLAVIER_HPP
#define CLAVIER_HPP

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

class Clavier {
public:
Clavier(); //constructeur par défaut
Clavier(const Clavier& c);
Clavier(int ajoutEntropie); // constructeur avec ajout de hasard
void randomize(int ajoutEntropie);
char getTouche(int ln, int col);
char getTouche(int index) const; //commence à 0
char getTouche(std::vector<int> index);
void setTouche(int ln, int col, char newTouche);
void setTouche(std::vector<int> index, char newTouche);
void setTouche(int index, char newTouche); //commence à 0
std::string affichageClavier();
std::vector<int> getKeyCoordinates(char touche);
float getDistanceBetweenKeys(char touche1, char touche2);
float getScore();
std::string getStringLigne(int ligne);
void blank();
int correctErrors();
void mutationAleatoire(int nbPermutation);
bool equals(const Clavier& c);

private:
    char touches[40];
    int ajoutEntropie;
};

#endif