//
// Created by maria-parapeanu on 5/4/26.
//

#ifndef OOP_JOC_H
#define OOP_JOC_H

#include "Ferma.h"


class Joc {
    Ferma* ferma;
    Ferma* salvare;
    bool ruleaza;
    static void titlu(const std::string& text);

    static void invalid();

    static int citesteInt(const std::string& mesaj);

    void meniuTeren();

    void meniuAnimale();

    void meniuMagazin();

    void meniuFerma();

public:
    explicit Joc(const std::string& numeFerma, int nrParcele);

    ~Joc();

    Joc(const Joc&) = delete;
    Joc& operator=(const Joc&) = delete;
    void ruleazaJocul();
};



#endif //OOP_JOC_H
