#ifndef CLAVIER_HPP
#define CLAVIER_HPP

#include <vector>

class Clavier {
public:
Clavier(); // constructeur par défaut
void randomize();
char getTouche(int ln, int col);
char getTouche(std::vector<int> index);
void setTouche(int ln, int col, char newTouche);
void setTouche(std::vector<int> index, char newTouche);
std::vector<int> getKeyCoordinates(char touche);
float getDistanceBetweenKeys(char touche1, char touche2);


private:
    char touches[40];
};

#endif