
#ifndef OOP_MAGAZIN_H
#define OOP_MAGAZIN_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

class Magazin {
    std::map<std::string, int> preturiCumparare;
    std::map<std::string, int> preturiVanzare;

    bool parseazaLinie(const std::string& linie);

public:
    // Arunca MagazinException daca fisierul nu poate fi deschis
    explicit Magazin(const std::string& caleFisier);

    [[nodiscard]] int getPretCumparare(const std::string& produs) const;
    [[nodiscard]] int getPretVanzare(const std::string& produs) const;

    // Returneaza toate produsele vanzabile (pretVanzare > 0)
    [[nodiscard]] std::vector<std::string> produseVandabile() const;

    // Returneaza toate animalele disponibile la cumparare
    [[nodiscard]] std::vector<std::string> animaleDisponibile() const;

    // Returneaza toate semintele disponibile la cumparare
    [[nodiscard]] std::vector<std::string> semintеDisponibile() const;

    friend std::ostream& operator<<(std::ostream& os, const Magazin& m);

private:
    // Categorii separate pentru afisare si meniuri
    std::map<std::string, std::string> tipProdus; // nume -> "seminta" | "animal" | "produs"
};

#endif //OOP_MAGAZIN_H