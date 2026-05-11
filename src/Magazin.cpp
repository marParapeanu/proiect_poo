
#include "../include/Magazin.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

class FermaException : public std::exception {
    std::string mesaj;
public:
    explicit FermaException(std::string msg) : mesaj(std::move(msg)) {}
    [[nodiscard]] const char* what() const noexcept override { return mesaj.c_str(); }
};

class FisierLipsaException : public FermaException {
public:
    explicit FisierLipsaException(const std::string& cale)
        : FermaException("Nu pot deschide fisierul: " + cale) {}
};

class FormatInvalidException : public FermaException {
public:
    explicit FormatInvalidException(const std::string& linie)
        : FermaException("Linie invalida in fisierul de date: '" + linie + "'") {}
};

class PretInvalidException : public FermaException {
public:
    explicit PretInvalidException(const std::string& produs)
        : FermaException("Pret negativ sau invalid pentru produsul: " + produs) {}
};

bool Magazin::parseazaLinie(const std::string& linie) {
    if (linie.empty() || linie[0] == '#') return true;

    std::stringstream ss(linie);
    std::string tip, nume, pretCumpStr, pretVanzStr;

    if (!std::getline(ss, tip, ',') ||
        !std::getline(ss, nume, ',') ||
        !std::getline(ss, pretCumpStr, ',') ||
        !std::getline(ss, pretVanzStr)) {
        throw FormatInvalidException(linie);
    }

    int pretCump, pretVanz;
    try {
        pretCump = std::stoi(pretCumpStr);
        pretVanz = std::stoi(pretVanzStr);
    } catch (...) {
        throw FormatInvalidException(linie);
    }

    if (pretCump < 0 || pretVanz < 0) {
        throw PretInvalidException(nume);
    }

    if (tip != "seminta" && tip != "animal" && tip != "produs") {
        throw FormatInvalidException(linie);
    }

    if (pretCump > 0) preturiCumparare[nume] = pretCump;
    if (pretVanz > 0) preturiVanzare[nume] = pretVanz;
    tipProdus[nume] = tip;

    return true;
}

Magazin::Magazin(const std::string& caleFisier) {
    std::ifstream fisier(caleFisier);
    if (!fisier.is_open()) {
        throw FisierLipsaException(caleFisier);
    }

    std::string linie;
    while (std::getline(fisier, linie)) {
        if (!linie.empty() && linie.back() == '\r') linie.pop_back();
        parseazaLinie(linie);
    }
}

int Magazin::getPretCumparare(const std::string& produs) const {
    auto it = preturiCumparare.find(produs);
    return (it != preturiCumparare.end()) ? it->second : 0;
}

int Magazin::getPretVanzare(const std::string& produs) const {
    auto it = preturiVanzare.find(produs);
    return (it != preturiVanzare.end()) ? it->second : 0;
}

std::vector<std::string> Magazin::produseVandabile() const {
    std::vector<std::string> rezultat;
    for (const auto& p : preturiVanzare) {
        rezultat.push_back(p.first);
    }
    return rezultat;
}

std::vector<std::string> Magazin::animaleDisponibile() const {
    std::vector<std::string> rezultat;
    for (const auto& p : tipProdus) {
        if (p.second == "animal" && preturiCumparare.count(p.first)) {
            rezultat.push_back(p.first);
        }
    }
    return rezultat;
}

std::vector<std::string> Magazin::semintеDisponibile() const {
    std::vector<std::string> rezultat;
    for (const auto& p : tipProdus) {
        if (p.second == "seminta" && preturiCumparare.count(p.first)) {
            rezultat.push_back(p.first);
        }
    }
    return rezultat;
}

std::ostream& operator<<(std::ostream& os, const Magazin& m) {
    os << "=== CATALOG MAGAZIN ===\n";
    os << "Seminte si animale de cumparat:\n";
    for (const auto& p : m.preturiCumparare) {
        os << "  " << p.first << ": " << p.second << " monede\n";
    }
    os << "Produse de vandut:\n";
    for (const auto& p : m.preturiVanzare) {
        os << "  " << p.first << ": " << p.second << " monede\n";
    }
    return os;
}