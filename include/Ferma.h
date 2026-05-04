//
// Created by maria-parapeanu on 5/4/26.
//

#ifndef OOP_FERMA_H
#define OOP_FERMA_H

#include "Hambar.h"
#include "Portofel.h"
#include "Parcela.h"
#include "Magazin.h"
#include "Animal.h"
#include <vector>

class Ferma {

    std::string numeFerma;
    Hambar hambar;
    Portofel portofel;
    Magazin magazin;
    int ziuaCurenta;
    int numarParcele;
    Parcela* parcele = nullptr; //pointer catre heap
    std::vector<Animal> animale;

public:
    //Ferma() {}
    explicit Ferma(std::string  nume, int nrParcele);

    Ferma(const Ferma& other);

    ~Ferma();

    void extindeFerma(int parceleAdaugate);

    void adaugaAnimal(const Animal& a);

    void hranesteAnimale();

    void vinde(const std::string& numeProdus, int cantitate);

    void planteaza(int index, const Planta& p);

    void udaParcela(int index);

    void recolteaza(int index);

    void ziuaUrmatoare();

    Ferma& operator=(const Ferma& other);

    friend std::ostream& operator<<(std::ostream &os, const Ferma &f);
};


#endif //OOP_FERMA_H
