#include "../include/Oaie.h"

Oaie::Oaie(std::string nume) : Animal(std::move(nume)) {}

std::string Oaie::produce() const { return "Oaie " + getNume() + " a produs lana!"; }
std::string Oaie::getResursa() const { return "Lana"; }
std::unique_ptr<Animal> Oaie::clone() const { return std::make_unique<Oaie>(*this); }
void Oaie::afisare(std::ostream& os) const {
    os << "[Oaie] "; Animal::afisare(os); os << " | Produs: Lana";
}