#ifndef OOP_ANIMAL_H
#define OOP_ANIMAL_H

//#include <iostream>
#include <memory>

class Animal {
    std::string numeAnimal;
    int varsta;
    bool esteHranit;
    bool traieste;

protected:
    explicit Animal(std::string nume);
    virtual void afisare(std::ostream& os) const; // virtual privat pt interfata non-virtuala

public:
    virtual ~Animal() = default;

    [[nodiscard]] virtual std::unique_ptr<Animal> clone() const = 0;
    [[nodiscard]] virtual std::string produce() const = 0;
    [[nodiscard]] virtual std::string getResursa() const = 0;

    void hraneste();
    void cresteZi();
    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] bool esteViu() const;

    friend std::ostream& operator<<(std::ostream& os, const Animal& a);
};

#endif