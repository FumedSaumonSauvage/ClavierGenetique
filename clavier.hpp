#ifndef CLAVIER_HPP
#define CLAVIER_HPP

class Clavier {
public:
Clavier(); // constructeur par défaut
void randomize();
int getAttribute() const;

private:
    char touches[40];
};

#endif