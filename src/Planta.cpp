//
// Created by maria-parapeanu on 5/4/26.
//

#include "../include/Planta.h"


Planta::Planta(std::string numeP, std::string cat, int zileM):
    numePlanta(std::move(numeP)), categorie(std::move(cat)), zileMaturitate(zileM), stadiuCrestere(0), nivelApa(false), traieste(true) {}

std::string Planta::getNume() const { return this -> numePlanta; }

std::string Planta::getCategorie() const { return this -> categorie; }

bool Planta::isAlive() const {return this -> traieste; }

bool Planta::esteMatura() const {return stadiuCrestere >= zileMaturitate;}

void Planta::udaPlanta() {nivelApa = true; }

void Planta::cresteZi() {
    if (!traieste) return;
    if (nivelApa) {
        stadiuCrestere++;
        nivelApa = false;
    }
    else traieste = false;
}

std::ostream & operator<<(std::ostream &os, const Planta &p) {
    if (!p.traieste) {
        os << "[ MOARTA ] " << p.numePlanta << "\n";
    }
    else
        os << "[ " << p.categorie << " ] : " << p.numePlanta << " are " << p.stadiuCrestere << " zile. /" <<
                (p.nivelApa == 0 ? " [ TREBUIE UDATA ] " : " [ ESTE UDATA ] ");
    return os;
}