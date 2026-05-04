//
// Created by maria-parapeanu on 5/4/26.
//

#ifndef OOP_MAGAZIN_H
#define OOP_MAGAZIN_H

#include <iostream>
#include <map>


class Magazin {
    std::map<std::string, int> preturiCumparare; //cat ma costa sa cumar seminte, animale, etc
    std::map<std::string, int> preturiVanzare; //cat primesc cand vand un produs
public:
    Magazin();

    [[nodiscard]] int getPretCumparare(const std::string& produs) const;

    [[nodiscard]] int getPretVanzare(const std::string& produs) const;

    friend std::ostream& operator<<(std::ostream& os, const Magazin& m);
};


#endif //OOP_MAGAZIN_H
