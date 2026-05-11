#ifndef OOP_GAINA_H
#define OOP_GAINA_H
#include "Animal.h"

class Gaina : public Animal {
public:
    explicit Gaina(std::string nume);
    [[nodiscard]] std::unique_ptr<Animal> clone() const override;
    [[nodiscard]] std::string produce() const override;
    [[nodiscard]] std::string getResursa() const override;
private:
    void afisare(std::ostream& os) const override;
};
#endif