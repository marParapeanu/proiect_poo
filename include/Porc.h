//
// Created by maria-parapeanu on 5/11/26.
//

#ifndef OOP_PORC_H
#define OOP_PORC_H
#include "Animal.h"

class Porc : public Animal {
public:
    explicit Porc(std::string nume);
    [[nodiscard]] std::unique_ptr<Animal> clone() const override;
    [[nodiscard]] std::string produce() const override;
    [[nodiscard]] std::string getResursa() const override;
private:
    void afisare(std::ostream& os) const override;
};


#endif //OOP_PORC_H
