//
// Created by maria-parapeanu on 5/4/26.
//

#include "Joc.h"
#include <limits>

void Joc::titlu(const std::string &text) {
    std::cout << " " << text << "\n";
}

void Joc::invalid() {std::cout << "Optiune invalida!\n";}

int Joc::citesteInt(const std::string &mesaj) {
    int val;
    std::cout << mesaj;
    while (!(std::cin >> val)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Input invalid! \n" << mesaj;
    }
    return val;
}

void Joc::meniuTeren() {
    titlu("GESTIUNE TEREN");
    std::cout << "1. Planteaza\n" << "2. Uda o parcela\n" << "3. Recolteaza\n" << "0. Inapoi\n";
    int opt = citesteInt("> ");
    switch (opt) {
        case 1: {
            int index = citesteInt("Index parcela: ");
            titlu("SELECTEAZA PLANTA: ");
            std::cout << "1. Rosie (cost: 10 monede, maturitate 5 zile) \n"
                    << "2. Lalea (cost: 5 monede, maturitate 3 zile) \n";
            int alegere = citesteInt("> ");
            if (alegere == 1)
                ferma->planteaza(index, Planta("Rosie", "Leguma", 5));
            else if (alegere == 2)
                ferma->planteaza(index, Planta("Lalea", "Floare", 2));
            else invalid();
            break;
        }

        case 2: {
            int index = citesteInt("Index parcela: ");
            ferma->udaParcela(index);
            break;
        }

        case 3: {
            int index = citesteInt("Index parcela: ");
            ferma->recolteaza(index);
            break;
        }

        case 0: break;

        default: invalid();
    }
}

void Joc::meniuAnimale() {
    titlu("GESTIUNE ANIMALE");
    std::cout << "1. Cumpara animal\n" << "2. Hraneste toate animalele\n" << "0. Inapoi\n";
    int opt = citesteInt("> ");
    switch (opt) {
        case 1: {
            titlu("SELECTEAZA ANIMAL");
            std::cout << "1. Vaca  (cost: 50 monede)\n"
                    << "2. Gaina (cost: 20 monede)\n"
                    << "3. Porc (cost: 80 monede)\n";
            int alegere = citesteInt("> ");
            std::string numeAnimal;
            std::cout << "Numele animalului: ";
            std::cin >> numeAnimal;
            if (alegere == 1)
                ferma->adaugaAnimal(Animal(numeAnimal, "Vaca"));
            else if (alegere == 2)
                ferma->adaugaAnimal(Animal(numeAnimal, "Gaina"));
            else if (alegere == 3)
                ferma->adaugaAnimal(Animal(numeAnimal, "Porc"));
            else invalid();
            break;
        }

        case 2: {
            ferma->hranesteAnimale();
            break;
        }

        case 0: break;
        default: invalid();
    }
}

void Joc::meniuMagazin() {
    titlu("MAGAZIN - VANZARE RECOLTA");
    std::cout << "1. Vinde Rosii\n"
            << "2. Vinde Lalele\n"
            << "0. Inapoi\n";
    int opt = citesteInt("> ");
    std::string produs;
    if (opt == 1) produs = "Rosie";
    else if (opt == 2) produs = "Lalea";
    else return;
    int cantitate = citesteInt("Cantitate: ");
    ferma->vinde(produs, cantitate);
}

void Joc::meniuFerma() {
    titlu("GESTIONARE FERMA");
    std::cout << "1. Extinde ferma\n"
            << "2. Salveaza progresul\n"
            << "3. Incarca salvare\n"
            << "0. Inapoi\n";
    int opt = citesteInt("> ");
    switch (opt) {
        case 1: {
            int nrParcele = citesteInt("Cate parcele vrei sa adaugi? (cost: 50/parcela): ");
            ferma->extindeFerma(nrParcele);
            break;
        }
        case 2:
            delete salvare;
            salvare = new Ferma(*ferma);
            std::cout << "Progres salvat!\n";
            break;
        case 3:
            if (salvare == nullptr) {
                std::cout << "Nu exista nicio salvare!\n";
            } else {
                *ferma = *salvare;
                std::cout << "Salvare incarcata cu succes!\n";
            }
            break;
        case 0: break;
        default: std::cout << "Optiune invalida.\n";
    }
}

Joc::Joc(const std::string &numeFerma, int nrParcele): ferma(new Ferma(numeFerma, nrParcele)),
                                                       salvare(nullptr),
                                                       ruleaza(true) {}

Joc::~Joc() {
    delete ferma;
    delete salvare;
}

void Joc::ruleazaJocul() {
    while (ruleaza) {
        titlu("MENIU PRINCIPAL");
        std::cout << "1. Vezi status ferma\n"
                << "2. Gestioneaza teren\n"
                << "3. Gestioneaza animale\n"
                << "4. Magazin (vinde recolta)\n"
                << "5. Treci la ziua urmatoare\n"
                << "6. Gestioneaza ferma (save/load/extinde)\n"
                << "0. Iesi din joc\n";
        int opt = citesteInt("> ");
        switch (opt) {
            case 1: std::cout << *ferma; break;
            case 2: meniuTeren();         break;
            case 3: meniuAnimale();       break;
            case 4: meniuMagazin();       break;
            case 5: ferma->ziuaUrmatoare(); break;
            case 6: meniuFerma();         break;
            case 0: ruleaza = false;
                std::cout << "La revedere! Multumim ca ai jucat!\n";
                break;
            default: std::cout << "Optiune invalida.\n";
        }
    }
}