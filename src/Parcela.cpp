//
// Created by maria-parapeanu on 5/4/26.
//

#include "../include/Parcela.h"
#include "Planta.h"

Parcela::Parcela(): plantaCrt("Nicio planta", "-", 0), esteOcupata(false) {}

void Parcela::planteaza(const Planta &p) {
    esteOcupata = true;
    plantaCrt = p;
}

bool Parcela::isOcupata() const {return esteOcupata;}

void Parcela::ingrijestePlanta() {
    if (esteOcupata) plantaCrt.udaPlanta();
}

void Parcela::treciZiua() {
    if (esteOcupata) plantaCrt.cresteZi();
}

bool Parcela::gataDeRecoltat() const { return esteOcupata && plantaCrt.esteMatura() && plantaCrt.isAlive();}

std::string Parcela::recolteaza() {
    std::string nume = plantaCrt.getNume();
    esteOcupata = false;
    plantaCrt = Planta("Nicio planta", "-", 0);
    return nume;
}

std::string Parcela::numePlanta() const {return plantaCrt.getNume();}

std::ostream & operator<<(std::ostream &os, const Parcela &p) {
    if (p.esteOcupata) {
        os << "Ocupata: " << p.plantaCrt;
    }
    else
        os << "Parcela este goala.\n";
    return os;
}