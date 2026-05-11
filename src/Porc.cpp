#include "../include/Porc.h"

Porc::Porc(std::string nume) : Animal(std::move(nume)) {}

std::string Porc::produce() const { return "Porc " + getNume() + " a produs slanina!"; }
std::string Porc::getResursa() const { return "Slanina"; }
std::unique_ptr<Animal> Porc::clone() const { return std::make_unique<Porc>(*this); }
void Porc::afisare(std::ostream& os) const {
    os << "[Porc] "; Animal::afisare(os); os << " | Produs: Slanina";
}