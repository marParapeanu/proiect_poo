#include <iostream>
#include <Joc.h>

int main() {

    std::string numeFerma;
    std::cout << "Introdu numele fermei tale! \n";
    std::cin >> numeFerma;
    Joc joc(numeFerma, 3);
    joc.ruleazaJocul();
    return 0;
}
