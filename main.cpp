#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>

class Planta {
    std::string numePlanta;
    std::string categorie; //Leguma, Fruct, Floare
    int zileMaturitate; //cate zile e nevoie pana ajunge la maturitate
    int stadiuCrestere;
    //int nivelApa;
public:
    Planta(std::string  numeP, std::string cat, int zileM) :
    numePlanta(std::move(numeP)), categorie(std::move(cat)), zileMaturitate(zileM), stadiuCrestere(0) {} //nivelApa de adaugat dupa warninguri

    [[nodiscard]] std::string getNume() const { return this -> numePlanta; }
    [[nodiscard]] std::string getCategorie() const { return this -> categorie; }

    friend std::ostream& operator << (std::ostream& os, const Planta& p) {
        os << "[ " << p.categorie << " ] : " << p.numePlanta << " are " << p.stadiuCrestere << " zile";
        return os;
    }

    void cresteZi(){ stadiuCrestere++;}
    [[nodiscard]] bool esteMatura() const {return stadiuCrestere >= zileMaturitate;}

};

class Parcela {
    Planta plantaCrt;
    bool esteOcupata; //daca avem ceva plantat versurs daca parcela e goala
public:
    Parcela() : plantaCrt("Nicio planta", "-", 0), esteOcupata(false){}
    void planteaza(const Planta &p) {
        esteOcupata = true;
        plantaCrt = p;
    }
    [[nodiscard]] bool isOcupata() const {return esteOcupata;}
    void ingrijestePlanta() {
        if (esteOcupata) plantaCrt.cresteZi();
    }
    [[nodiscard]] bool gataDeRecoltat() const { return esteOcupata && plantaCrt.esteMatura();}
    std::string recolteaza() {
        std::string nume = plantaCrt.getNume();
        esteOcupata = false;
        plantaCrt = Planta("Nicio planta", "-", 0);
        return nume;
    }
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
    friend std::ostream& operator<<(std::ostream& os, const Hambar &h) {
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
    //Ferma() {}
    explicit Ferma(std::string  nume, int nrParcele) :
    numeFerma(std::move(nume)), ziuaCurenta(0), numarParcele(nrParcele) {
        parcele = new Parcela[numarParcele]; //parcele = pointer catre primul element din array
        std::cout << "Bine ai venit la ferma: " << numeFerma << "!\n";
        std::cout << "Ziua " << ziuaCurenta << "\n";
        std::cout << "Numar parcele: " << numarParcele;
    }
    Ferma(const Ferma& other) : //constructor de copiere, salvarea progresului pentru a putea reseta greseli
    numeFerma(other.numeFerma),
    hambar(other.hambar),
    ziuaCurenta(other.ziuaCurenta),
    numarParcele(other.numarParcele) {
        if (other.numarParcele > 0 && other.parcele != nullptr) { //daca ferma copiata are macar o parcela
            parcele = new Parcela[other.numarParcele]; //alocam un nou spatiu de memorie pentru ferma salvata

            for (int i = 0; i < other.numarParcele; i++)
                parcele[i] = other.parcele[i];
        }
        else parcele = nullptr;
        std::cout << "Progresul fermei " << other.numeFerma << " a fost salvat! " << "Nume copie: " << numeFerma << "\n";
    }
    ~Ferma() { delete[] parcele; parcele = nullptr;}

    void extindeFerma(int parceleAdaugate) {
        if (parceleAdaugate <= 0) {
            std::cout << "Dimensiune interzisa! Trebuie sa adaugi cel putin o parcela!";
            return;
        }
        int capacitateNoua = this->numarParcele + parceleAdaugate; //parcelele initiale plus parcelele pe care vrem sa le adaugam
        auto *parceleNoi = new Parcela[capacitateNoua]; //aloc un nou bloc de memorie avand noua capacitate
        std::move(parcele, parcele+numarParcele, parceleNoi);
         // for (int i = 0; i < numarParcele; i++) {
         //     parceleNoi[i] = parcele[i];
         // }

        delete[] parcele; //dezaloc vechia memorie unde erau puse parcelele
        parcele = parceleNoi;
        numarParcele = capacitateNoua;
        std::cout << "Ferma a fost extinsa cu succes! Numar curent de parcele: " << numarParcele << "\n";
    }

    void planteaza(int index, const Planta& p) {
        if (index < 0 || index >= numarParcele) return;
        if (parcele[index].isOcupata()) {
            std::cout << "Parcela cu numarul " << index << " este ocupata!\n";
            return;
        }
        std::string cat = p.getCategorie();
        if (cat == "Leguma" || cat == "Fruct" || cat == "Floare") {
            parcele[index].planteaza(p);
            std::cout << "Ai plantat " << p.getNume() << " pe parcela cu numarul " << index << "\n";
        }
        else {
            std::cout << "EROARE " << p.getNume() << " nu este o planta valida!\n";
        }
    }

    friend std::ostream& operator<<(std::ostream &os, const Ferma &f) {
        os << "Ferma: " << f.numeFerma << "\n";
        os << "Ziua curenta: " << f.ziuaCurenta << "\n";
        os << "Numar parcele: " << f.numarParcele << "\n";
        os << "Hambar: " << f.hambar << "\n";

        return os;
    }
};


int main() {
    std::string numeFerma;
    std::cout << "Introdu numele fermei tale!: ";
    std::cin  >> numeFerma;
    Ferma fermaMea(numeFerma, 5);
    Planta rosie("Rosie", "Leguma", 3);
    Planta lalea("Lalea", "Floare", 2);
    fermaMea.planteaza(0, rosie);
    fermaMea.planteaza(1, lalea);
    fermaMea.planteaza(2, rosie);
    fermaMea.planteaza(3, rosie);
    fermaMea.planteaza(4, lalea);
    fermaMea.planteaza(5,lalea);
    fermaMea.extindeFerma(1);
    std::cout << fermaMea;




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