#ifndef OOP_VACA_H
#define OOP_VACA_H
#include "Animal.h"

class Vaca : public Animal {
public:
    explicit Vaca(std::string nume);
    [[nodiscard]] std::unique_ptr<Animal> clone() const override;
    [[nodiscard]] std::string produce() const override;
    [[nodiscard]] std::string getResursa() const override;
private:
    void afisare(std::ostream& os) const override;
};
#endif