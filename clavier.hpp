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


private:
    char touches[40];
};

#endif