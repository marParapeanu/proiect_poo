#include <iostream>
#include <utility>
#include <vector>
#include <string>
//#include <ctime>
#include <stdexcept>
#include <chrono>

class data {
    int zi;
    int luna;
    int an;
    static bool validareData(int z, int l, int a); // definita cu static ptc apartine clasei in sine
public:
    data(int zi_, int luna_, int an_)  {
        if (validareData(zi_, luna_, an_)) {
            zi = zi_;
            luna = luna_;
            an = an_;
        }
        else {zi = 0; luna = 0; an = 0;}
    }
};

bool data::validareData(int z, int l, int a) {
    if (a < 0) return false;
    if (l > 12 || l < 1) return false;
    if (z > 31 || z < 1) return false;
    if (z == 31 && (l == 4 || l == 6 || l == 9 || l == 11)) return false;
    if (a % 400 == 0 || (a % 4 == 0 && a % 100 != 0)) {
        if (l == 2 && z > 29) return false;
    }
    else if (l == 2 && z > 28) return false;
    return true;
}

class nrTelefon {
    std::string nr;
    std::string prefix;
public:
    nrTelefon() : nr("unknown"), prefix("+40") {} //constructor fara parametri pentru numerele de telefon necunoscute
    explicit nrTelefon(const std::string &numar, const std::string &pref = "+40") {
        if (numar.length() != 9) {
            throw std::invalid_argument("Numarul trebuie sa aiba 10 cifre!");
        }
        for (char c : numar)
            if (!isdigit(c))
                throw std::invalid_argument("Numar invalid!");

        nr = numar;
        prefix = pref;
    }//constructor de initializare nr de Telefon, cu validari

    std::string get_nr() const { return prefix + " " + nr;}

};

class CardBancar {
    std::string nrCard;
    int cvc;
    data dataExpirarii;
public:
    CardBancar(std::string numar, int codCVC, const data &exp) : nrCard(std::move(numar)), cvc(codCVC), dataExpirarii(exp){}
};

class Depozit {
    data dataDeschidere;
    data dataInchidere;
    float rata;
    std::string moneda;
public:
    Depozit(const data &dataD, const data &dataI, float r, std::string &m)
    : dataDeschidere(dataD), dataInchidere(dataI), rata(r), moneda(m){}

};

class ContBancar {
    double sold;
    std::string moneda;
    std::vector<CardBancar> carduri;
    std::vector<Depozit> depozite;
public:
    explicit ContBancar(std::string m) : sold(0), moneda(std::move(m)){}
    double getSold() const {return sold;}

};

class Client {
    std::string numeClient;
    std::string prenumeClient;
    nrTelefon telefon;
    std::vector <ContBancar> conturi;

public:
    Client(std::string nume, std::string prenume, nrTelefon tel) : numeClient(std::move(nume)), prenumeClient(std::move(prenume)), telefon(std::move(tel)) {
        std::cout << "Constructor de initializare cu parametri pentru client\n";
    }
    //nu vrem sa avem un constructor fara parametri sau un constructor cu parametri impliciti aici pentru ca nu vrem sa avem un obiect de tip Client depsre care sa nu stim nimic
    //ca atare, este obligatoriu sa introducem informatii la construire
    const std::string &getNume() const { return numeClient; }
    const std::string &getPrenume() const {return prenumeClient;}
    const nrTelefon &getTelefon() const { return telefon;}

};



int main() {
    Client client1("Paun", "Mariana", nrTelefon("720747100"));
    std::cout << client1.getNume() << " " << client1.getPrenume() << " "  << client1.getTelefon().get_nr();



    //std::array<int, 100> v{};
    // int nr;
    // std::cout << "Introduceți nr: ";
    /////////////////////////////////////////////////////////////////////////
    /// Observație: dacă aveți nevoie să citiți date de intrare de la tastatură,
    /// dați exemple de date de intrare folosind fișierul tastatura.txt
    /// Trebuie să aveți în fișierul tastatura.txt suficiente date de intrare
    /// (în formatul impus de voi) astfel încât execuția programului să se încheie.
    /// De asemenea, trebuie să adăugați în acest fișier date de intrare
    /// pentru cât mai multe ramuri de execuție.
    /// Dorim să facem acest lucru pentru a automatiza testarea codului, fără să
    /// mai pierdem timp de fiecare dată să introducem de la zero aceleași date de intrare.
    ///
    /// Pe GitHub Actions (bife), fișierul tastatura.txt este folosit
    /// pentru a simula date introduse de la tastatură.
    /// Bifele verifică dacă programul are erori de compilare, erori de memorie și memory leaks.
    ///
    /// Dacă nu puneți în tastatura.txt suficiente date de intrare, îmi rezerv dreptul să vă
    /// testez codul cu ce date de intrare am chef și să nu pun notă dacă găsesc vreun bug.
    /// Impun această cerință ca să învățați să faceți un demo și să arătați părțile din
    /// program care merg (și să le evitați pe cele care nu merg).
    ///
    /////////////////////////////////////////////////////////////////////////
    // std::cin >> nr;
    // /////////////////////////////////////////////////////////////////////////
    // for(int i = 0; i < nr; ++i) {
    //     std::cout << "v[" << i << "] = ";
    //     std::cin >> v[i];
    // }
    // std::cout << "\n\n";
    // std::cout << "Am citit de la tastatură " << nr << " elemente:\n";
    // for(int i = 0; i < nr; ++i) {
    //     std::cout << "- " << v[i] << "\n";
    // }
    ///////////////////////////////////////////////////////////////////////////
    /// Pentru date citite din fișier, NU folosiți tastatura.txt. Creați-vă voi
    /// alt fișier propriu cu ce alt nume doriți.
    /// Exemplu:
    /// std::ifstream fis("date.txt");
    /// for(int i = 0; i < nr2; ++i)
    ///     fis >> v2[i];
    ///
    ///////////////////////////////////////////////////////////////////////////
    return 0;
}