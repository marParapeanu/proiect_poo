//
// Created by maria-parapeanu on 5/4/26.
//

#ifndef OOP_HAMBAR_H
#define OOP_HAMBAR_H

#include <iostream>
#include <map>

class Hambar {
    std::map<std::string, int> inventar;
public:
    bool extrageDinHambar(const std::string& numeProdus, int cantitate);
    void adaugaRecolta(const std::string& numePlanta);
    friend std::ostream& operator<<(std::ostream& os, const Hambar &h);
};

#endif //OOP_HAMBAR_H
