#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

class Planta {
    std::string numePlanta;
    int zileMaturitate; //cate zile e nevoie pana ajunge la maturitate
    int stadiuCrestere;
    int nivelApa;
public:
    Planta(const std::string& numeP, int zileM) :
    numePlanta(numeP), zileMaturitate(zileM), stadiuCrestere(0), nivelApa(0) {}

    int get_zileMaturitate() const {return zileMaturitate;}
    int get_stadiuCrestere() const {return stadiuCrestere;}
    int get_nivelApa() const {return nivelApa;}


    friend std::ostream& operator << (std::ostream& os, const Planta& p) {
        os << "Planta " << p.numePlanta << " are " << p.stadiuCrestere << " zile";
        return os;
    }

    void cresteZi(){ stadiuCrestere++;}
    bool esteMatura() const {return stadiuCrestere >= zileMaturitate;}

};

class Parcela {
    Planta plantaCrt;
    bool esteOcupata; //daca avem ceva plantat versurs daca parcela e goala
public:
    Parcela() : plantaCrt("Nicio planta", 0), esteOcupata(false){}

    friend std::ostream& operator << (std::ostream& os, const Parcela& p) {
        if (p.esteOcupata) {
            os << "Ocupata: " << p.plantaCrt;
        }
        else
            os << "Parcela este goala.\n";
        return os;
    }
};

class Hambar {
    std::map<std::string, int> inventar;
public:
    void adaugaRecolta(const std::string& numePlanta) { inventar[numePlanta]++; }
    friend std::ostream& operator<<(std::ostream& os, Hambar &h) {
        os << "Hambar: " << "\n";
        if (h.inventar.empty()){ os << "Hambarul este gol!\n";}
        else {
            for (const auto& pereche : h.inventar) {
                os << pereche.first << " : " << pereche.second << "bucati\n";
            }
        }
        return os;
    }
};

class Ferma {
    std::string numeFerma;
    Hambar hambar;
    int ziuaCurenta;
    int numarParcele;
    Parcela* parcele; //pointer catre heap
public:
    Ferma() {}
    Ferma(int nrParcele) : ziuaCurenta(0), numarParcele(nrParcele) {
        parcele = new Parcela[numarParcele]; //parcele = pointer catre primul element din array
    }
    ~Ferma() { delete[] parcele; parcele = nullptr;}

    void extindeFerma(int parceleAdaugate) {
        if (parceleAdaugate <= 0) {
            std::cout << "Dimensiune interzisa! Trebuie sa adaugi cel putin o parcela!";
            return;
        }
        int capacitateNoua = this->numarParcele + parceleAdaugate; //parcelele initiale plus parcelele pe care vrem sa le adaugam
        Parcela *parceleNoi = new Parcela[capacitateNoua]; //aloc un nou bloc de memorie avand noua capacitate
        std::move(parcele, parcele+numarParcele, parceleNoi); //

        delete[] parcele; //dezaloc vechia memorie unde erau puse parcelele
        parcele = parceleNoi;
        numarParcele = capacitateNoua;
        std::cout << "Ferma a fost extinsa cu succes! Numar curent de parcele: " << numarParcele << "\n";

    }

    friend std::ostream& operator<<(std::ostream &os, Ferma &f) {
        os << "Ferma: " << f.numeFerma << "\n";
        os << "Ziua curenta: " << f.ziuaCurenta << "\n";
        os << "Numar parcele: " << f.numarParcele << "\n";
        os << "Hambar: " << f.hambar << "\n";
    }
};


int main() {
    Ferma ferma1;
    Planta p("Rosie", 5);
    std::cout << "\n";
    std::cout << p;


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