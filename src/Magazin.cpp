//
// Created by maria-parapeanu on 5/4/26.
//

#include "../include/Magazin.h"

Magazin::Magazin() {
    preturiCumparare["Rosie"] = 10;
    preturiCumparare["Lalea"] = 5;
    preturiCumparare["Vaca"] = 50;
    preturiCumparare["Porc"] = 80;
    preturiCumparare["Gaina"] = 20;

    preturiVanzare["Rosie"] = 20;
    preturiVanzare["Lalea"] = 15;
}

int Magazin::getPretCumparare(const std::string &produs) const {
    if (preturiCumparare.find(produs) != preturiCumparare.end())
        return preturiCumparare.at(produs);
    return 0;
}

int Magazin::getPretVanzare(const std::string &produs) const {
    if (preturiVanzare.find(produs) != preturiVanzare.end())
        return preturiVanzare.at(produs);
    return 0;
}

std::ostream & operator<<(std::ostream &os, const Magazin &m) {
    os << "CATALOG MAGAZIN: \n";
    os << "Cumpara seminte: \n";
    for (const auto& p : m.preturiCumparare) os << " - " << p.first << ": " << p.second << " monede\n";
    os << "Vinde recolta: \n";
    for (const auto& p : m.preturiVanzare) os << " - " << p.first << ": " << p.second << " monede\n";
    return os;
}