//
// Created by maria-parapeanu on 5/4/26.
//

#include "Portofel.h"
#include <iostream>

Portofel::Portofel(): bani(100) {}

int Portofel::getBani() const {return bani;}

void Portofel::adaugaBani(int suma) {
    if (suma > 0) bani += suma;
}

bool Portofel::cheltuie(int suma) {
    if (suma > 0) {
        if (suma <= this -> bani) {
            bani -= suma;
            return true;
        }
    }
    std::cout << "Fonduri insuficiente!\n";
    return false;
}

std::ostream & operator<<(std::ostream &os, const Portofel &p) {
    os << "BANI: " << p.bani << " monede";
    return os;
}
