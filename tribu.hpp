#ifndef TRIBU_HPP
#define TRIBU_HPP

#include "clavier.hpp"

class Tribu {
    public:
    Tribu(int cardinal);
    int getCount();
    Clavier getClavier(int index);
    void displayPopulation(int sort, int nbColonnes);

    private:
    Clavier population[500]; //bien cradax, voir comment paramétriser ca
    int count;
};

#endif