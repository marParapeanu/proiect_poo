//
// Created by maria-parapeanu on 5/4/26.
//

#include "../include/Animal.h"


Animal::Animal(std::string nume, std::string specieA): numeAnimal(std::move(nume)), specie(std::move(specieA)), varsta(0), esteHranit(false), traieste(true) {}

const std::string & Animal::getNume() const {return numeAnimal;}

const std::string & Animal::getSpecie() const {return specie;}

void Animal::hraneste() {
    if (traieste) esteHranit = true;
}

void Animal::cresteZi() {
    if (!traieste) return;
    if (esteHranit) {
        varsta++;
        esteHranit= false;
    }
    else traieste = false;
}

std::ostream & operator<<(std::ostream &os, const Animal &a) {
    if (!a.traieste) {
        os << " [ DECEDAT ]" << a.specie << a.numeAnimal << "a murit\n";
    }
    else {
        os <<  a.specie << " " << a.numeAnimal << " | Varsta: " << a.varsta << " zile | " << (a.esteHranit ? " [ ESTE HRANIT ]" : " [ FOAME ] -> trebuie hranit!") << "\n";
    }
    return os;
}