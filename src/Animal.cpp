#include "../include/Animal.h"

Animal::Animal(std::string nume)
    : numeAnimal(std::move(nume)), varsta(0), esteHranit(false), traieste(true) {}

const std::string& Animal::getNume() const { return numeAnimal; }
bool Animal::esteViu() const { return traieste; }

void Animal::hraneste() {
    if (traieste) esteHranit = true;
}

void Animal::cresteZi() {
    if (!traieste) return;
    if (esteHranit) { varsta++; esteHranit = false; }
    else traieste = false;
}

void Animal::afisare(std::ostream& os) const {
    if (!traieste) {
        os << "[ DECEDAT ] " << numeAnimal << " a murit.";
    } else {
        os << numeAnimal << " | Varsta: " << varsta << " zile | "
           << (esteHranit ? "[ HRANIT ]" : "[ FOAME ] -> trebuie hranit!");
    }
}

std::ostream& operator<<(std::ostream& os, const Animal& a) {
    a.afisare(os); // interfata non-virtuala
    return os;
}