//
// Created by maria-parapeanu on 5/4/26.
//

#ifndef OOP_ANIMAL_H
#define OOP_ANIMAL_H

#include <iostream>

class Animal {
    std::string numeAnimal;
    std::string specie;
    int varsta;
    bool esteHranit;
    bool traieste;
public:
    Animal(std::string  nume, std::string  specieA);

    [[nodiscard]] const std::string& getNume() const;

    [[nodiscard]] const std::string& getSpecie() const;

    //[[nodiscard]] bool isAlive() const { return traieste;}

    void hraneste();

    void cresteZi();

    friend std::ostream& operator<<(std::ostream& os, const Animal& a);
};

#endif //OOP_ANIMAL_H
