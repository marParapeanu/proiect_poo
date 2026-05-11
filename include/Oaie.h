//
// Created by maria-parapeanu on 5/11/26.
//

#ifndef OOP_OAIE_H
#define OOP_OAIE_H
#include "Animal.h"

class Oaie : public Animal {
public:
    explicit Oaie(std::string nume);
    [[nodiscard]] std::unique_ptr<Animal> clone() const override;
    [[nodiscard]] std::string produce() const override;
    [[nodiscard]] std::string getResursa() const override;
private:
    void afisare(std::ostream& os) const override;
};

#endif //OOP_OAIE_H
