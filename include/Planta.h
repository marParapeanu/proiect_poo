//
// Created by maria-parapeanu on 5/4/26.
//

#ifndef OOP_PLANTA_H
#define OOP_PLANTA_H
#include <iostream>

class Planta {
    std::string numePlanta;
    std::string categorie; //Leguma, Fruct, Floare
    int zileMaturitate; //cate zile e nevoie pana ajunge la maturitate
    int stadiuCrestere;
    bool nivelApa;
    bool traieste;
public:
    Planta(std::string  numeP, std::string cat, int zileM);

    [[nodiscard]] std::string getNume() const;

    [[nodiscard]] std::string getCategorie() const;

    [[nodiscard]] bool isAlive() const;

    [[nodiscard]] bool esteMatura() const;

    void udaPlanta();

    void cresteZi();

    friend std::ostream& operator << (std::ostream& os, const Planta& p);
};

#endif //OOP_PLANTA_H
