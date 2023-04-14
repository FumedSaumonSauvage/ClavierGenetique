#ifndef TRIBU_HPP
#define TRIBU_HPP

#include "clavier.hpp"

class Tribu {
    public:
    Tribu(int cardinal);
    int getCount();
    Clavier getClavier(int index);
    void displayPopulation(int nbColonnes);
    std::vector<int> jeVeuxLesMeilleurs(int percentage);
    void croiserPopulation(int percentageDeMeilleurs, bool remplacerParents);
    void sortByBest();
    void mutation(int percentage, int maxMutations);
    void eliminerConsanguinité(int maxPercentageConsanguin, int percentageCroisement);

    private:
    Clavier population[500]; //bien cradax, voir comment paramétriser ca
    int count;
};

#endif