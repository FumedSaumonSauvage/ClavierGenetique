#include "clavier.hpp"
#include <stdlib.h>


Clavier::Clavier() {
    char packTouches[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for(int i = 0; i < 40; i++){
        touches[i] = rand() %10 ;
    }
}

void Clavier::randomize() {
    return;
}

int Clavier::getAttribute() const {
    return 0; 
}