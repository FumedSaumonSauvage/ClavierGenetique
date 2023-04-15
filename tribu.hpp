#ifndef TRIBU_HPP
#define TRIBU_HPP

#include "clavier.hpp"
#include "liste.cpp"



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
    void eliminerConsanguinite(int maxPercentageConsanguin, int percentageCroisement);
    float getHighScore();
    bool convergence();
    float convergenceScore();

    private:
    Clavier population[500]; //bien cradax, voir comment paramétriser ca
    int count;
    Liste <float> highscores; 
};

#endif