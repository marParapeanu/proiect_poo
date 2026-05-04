//
// Created by maria-parapeanu on 5/4/26.
//

#ifndef OOP_PORTOFEL_H
#define OOP_PORTOFEL_H

#include <iostream>

class Portofel {
    int bani;
public:
    Portofel();

    [[nodiscard]] int getBani() const;

    void adaugaBani(int suma);

    bool cheltuie(int suma);

    friend std::ostream& operator<<(std::ostream& os, const Portofel& p);
};


#endif //OOP_PORTOFEL_H
