//
// Created by maria-parapeanu on 5/4/26.
//

#include "../include/Hambar.h"

bool Hambar::extrageDinHambar(const std::string &numeProdus, int cantitate) {
    if (inventar.find(numeProdus) != inventar.end() && inventar[numeProdus] >= cantitate) {
        inventar[numeProdus] -= cantitate;
        if (inventar[numeProdus] == 0) inventar.erase(numeProdus);
        return true;
    }
    return false;
}

void Hambar::adaugaRecolta(const std::string &numePlanta) { inventar[numePlanta]++; }

std::ostream & operator<<(std::ostream &os, const Hambar &h) {
    //os  << "\n";
    if (h.inventar.empty()){ os << "Hambarul este gol!\n";}
    else {
        for (const auto& pereche : h.inventar) {
            os << pereche.first << " - " << pereche.second << " buc\n";
        }
    }
    return os;
}