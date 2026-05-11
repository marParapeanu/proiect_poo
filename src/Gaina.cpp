#include "../include/Gaina.h"

Gaina::Gaina(std::string nume) : Animal(std::move(nume)) {}

std::string Gaina::produce() const { return "Gaina " + getNume() + " a ouat un ou!"; }
std::string Gaina::getResursa() const { return "Ou"; }
std::unique_ptr<Animal> Gaina::clone() const { return std::make_unique<Gaina>(*this); }
void Gaina::afisare(std::ostream& os) const {
    os << "[Gaina] "; Animal::afisare(os); os << " | Produs: Ou";
}