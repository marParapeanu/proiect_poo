//
// Created by maria-parapeanu on 5/4/26.
//

#ifndef OOP_PARCELA_H
#define OOP_PARCELA_H

#include "Planta.h"

class Parcela {
    Planta plantaCrt;
    bool esteOcupata; //daca avem ceva plantat versurs daca parcela e goala
public:
    Parcela();

    void planteaza(const Planta &p);

    [[nodiscard]] bool isOcupata() const;

    void ingrijestePlanta();

    void treciZiua();

    // void curataParcela() {
    //     esteOcupata = false;
    //     plantaCrt = Planta("Nicio planta", "-", 0);
    // }
    [[nodiscard]] bool gataDeRecoltat() const;

    std::string recolteaza();

    [[nodiscard]] std::string numePlanta() const;

    friend std::ostream& operator << (std::ostream& os, const Parcela& p);
};

#endif //OOP_PARCELA_H
