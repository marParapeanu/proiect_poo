#include "../include/Vaca.h"

Vaca::Vaca(std::string nume) : Animal(std::move(nume)) {}

std::string Vaca::produce() const { return "Vaca " + getNume() + " a facut un litru de lapte!"; }
std::string Vaca::getResursa() const { return "Lapte"; }
std::unique_ptr<Animal> Vaca::clone() const { return std::make_unique<Vaca>(*this); }
void Vaca::afisare(std::ostream& os) const {
    os << "[Vaca] "; Animal::afisare(os); os << " | Produs: Lapte";
}