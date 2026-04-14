#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>

class Portofel {
    int bani;
public:
    Portofel() : bani(100) {}
    [[nodiscard]] int getBani() const {return bani;}
    void adaugaBani(int suma) {
        if (suma > 0) bani += suma;
    }
    bool cheltuie(int suma) {
        if (suma > 0) {
            if (suma <= this -> bani) {
                bani -= suma;
                return true;
            }
        }
        std::cout << "Fonduri insuficiente!\n";
        return false;

    }
    friend std::ostream& operator<<(std::ostream& os, const Portofel& p) {
        os << "BANI: " << p.bani << " monede";
        return os;
    }
};

class Magazin {
    std::map<std::string, int> preturiCumparare; //cat ma costa sa cumar seminte, animale, etc
    std::map<std::string, int> preturiVanzare; //cat primesc cand vand un produs
public:
    Magazin() {
        preturiCumparare["Rosie"] = 10;
        preturiCumparare["Lalea"] = 5;

        preturiVanzare["Rosie"] = 20;
        preturiVanzare["Lalea"] = 15;
    }

    [[nodiscard]] int getPretCumparare(const std::string& produs) const {
        if (preturiCumparare.find(produs) != preturiCumparare.end())
            return preturiCumparare.at(produs);
        return 0;
    }

    [[nodiscard]] int getPretVanzare(const std::string& produs) const {
        if (preturiVanzare.find(produs) != preturiVanzare.end())
            return preturiVanzare.at(produs);
        return 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Magazin& m) {
        os << "CATALOG MAGAZIN: \n";
        os << "Cumpara seminte: \n";
        for (const auto& p : m.preturiCumparare) os << " - " << p.first << ": " << p.second << " monede\n";
        os << "Vinde recolta: \n";
        for (const auto& p : m.preturiVanzare) os << " - " << p.first << ": " << p.second << " monede\n";
        return os;
    }
};

class Planta {
    std::string numePlanta;
    std::string categorie; //Leguma, Fruct, Floare
    int zileMaturitate; //cate zile e nevoie pana ajunge la maturitate
    int stadiuCrestere;
    bool nivelApa;
    bool traieste;
public:
    Planta(std::string  numeP, std::string cat, int zileM) :
    numePlanta(std::move(numeP)), categorie(std::move(cat)), zileMaturitate(zileM), stadiuCrestere(0), nivelApa(false), traieste(true) {}

    [[nodiscard]] std::string getNume() const { return this -> numePlanta; }
    [[nodiscard]] std::string getCategorie() const { return this -> categorie; }
    [[nodiscard]] bool isAlive() const {return this -> traieste; }
    [[nodiscard]] bool esteMatura() const {return stadiuCrestere >= zileMaturitate;}

    void udaPlanta()  {nivelApa = true; }
    void cresteZi() {
        if (!traieste) return;
        if (nivelApa) {
            stadiuCrestere++;
            nivelApa = false;
        }
        else traieste = false;
    }

    friend std::ostream& operator << (std::ostream& os, const Planta& p) {
        if (!p.traieste) {
            os << "[ MOARTA ] " << p.numePlanta << "\n";
        }
        else
            os << "[ " << p.categorie << " ] : " << p.numePlanta << " are " << p.stadiuCrestere << " zile. /" <<
                (p.nivelApa == 0 ? " [ TREBUIE UDATA ] " : " [ ESTE UDATA ] ");
        return os;
    }

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
        if (esteOcupata) plantaCrt.udaPlanta();
    }
    void treciZiua() {
        if (esteOcupata) plantaCrt.cresteZi();
    }
    // void curataParcela() {
    //     esteOcupata = false;
    //     plantaCrt = Planta("Nicio planta", "-", 0);
    // }
    [[nodiscard]] bool gataDeRecoltat() const { return esteOcupata && plantaCrt.esteMatura() && plantaCrt.isAlive();}
    std::string recolteaza() {
        std::string nume = plantaCrt.getNume();
        esteOcupata = false;
        plantaCrt = Planta("Nicio planta", "-", 0);
        return nume;
    }
    [[nodiscard]] std::string numePlanta() const {return plantaCrt.getNume();}
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
    bool extrageDinHambar(const std::string& numeProdus, int cantitate) {
        if (inventar.find(numeProdus) != inventar.end() && inventar[numeProdus] >= cantitate) {
            inventar[numeProdus] -= cantitate;
            if (inventar[numeProdus] == 0) inventar.erase(numeProdus);
            return true;
        }
        return false;
    }

    void adaugaRecolta(const std::string& numePlanta) { inventar[numePlanta]++; }
    friend std::ostream& operator<<(std::ostream& os, const Hambar &h) {
        //os  << "\n";
        if (h.inventar.empty()){ os << "Hambarul este gol!\n";}
        else {
            for (const auto& pereche : h.inventar) {
                os << pereche.first << " - " << pereche.second << " buc\n";
            }
        }
        return os;
    }
};

class Ferma {

    std::string numeFerma;
    Hambar hambar;
    Portofel portofel;
    Magazin magazin;
    int ziuaCurenta;
    int numarParcele;
    Parcela* parcele = nullptr; //pointer catre heap

public:
    //Ferma() {}
    explicit Ferma(std::string  nume, int nrParcele) :
    numeFerma(std::move(nume)), ziuaCurenta(0), numarParcele(nrParcele) {
        parcele = new Parcela[numarParcele]; //parcele = pointer catre primul element din array
        std::cout << "Bine ai venit la ferma: " << numeFerma << "!\n";
        std::cout << "Ziua " << ziuaCurenta << "\n";
        std::cout << "Numar parcele: " << numarParcele << "\n";
    }
    Ferma(const Ferma& other) : //constructor de copiere, salvarea progresului pentru a putea reseta greseli
    numeFerma(other.numeFerma),
    hambar(other.hambar),
    portofel(other.portofel),
    magazin(other.magazin),
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
        int costTotal = parceleAdaugate * 50;
        if (!portofel.cheltuie(costTotal)) {
            std::cout << "Fonduri insuficiente pentru extindere!\n" << "Mai ai nevoie de " << portofel.getBani() << " Monede!\n";
            return;
        }

        int capacitateNoua = this->numarParcele + parceleAdaugate; //parcelele initiale plus parcelele pe care vrem sa le adaugam
        auto *parceleNoi = new Parcela[capacitateNoua]; //aloc un nou bloc de memorie avand noua capacitate

        if (parcele != nullptr && numarParcele>0) {
            std::copy_n(parcele, numarParcele, parceleNoi);
        }

        std::swap(parcele, parceleNoi);
        delete[] parceleNoi;
        numarParcele = capacitateNoua;

        // if (parcele != nullptr)
        //     std::move(parcele, parcele+numarParcele, parceleNoi);
        // delete[] parcele; //dezaloc vechea memorie unde erau puse parcelele
        // parcele = parceleNoi;
        // numarParcele = capacitateNoua;
        std::cout << "Ferma a fost extinsa cu succes! Numar curent de parcele: " << numarParcele << "\n";
    }

    void vinde(const std::string& numeProdus, int cantitate) {
        int pretBucata = magazin.getPretVanzare(numeProdus);

        if (hambar.extrageDinHambar(numeProdus, cantitate)) {
            int baniPrimiti = pretBucata * cantitate;
            portofel.adaugaBani((baniPrimiti));
            std::cout << "[Magazin] Ai vandut " << cantitate << " " << numeProdus << "\n";
        }
        else std::cout << "[Hambar] Nu ai suficiente " << numeProdus << "\n";

    }

    void planteaza(int index, const Planta& p) {
        if (index < 0 || index >= numarParcele) return;
        if (parcele[index].isOcupata()) {
            std::cout << "Parcela cu numarul " << index << " este ocupata!\n";
            return;
        }

        std::string cat = p.getCategorie();
        if (cat != "Leguma" && cat != "Fruct" && cat != "Floare") {
            std::cout << "EROARE: '" << p.getNume() << "' nu este o planta valida!\n";
            return;
        }
        int pret = magazin.getPretCumparare(p.getNume());
        if (portofel.getBani() < pret) {
            std::cout << "Bani insuficienti! Mai ai nevoie de " << pret - portofel.getBani() << " monede!";
            return;
        }
        portofel.cheltuie(pret);
        parcele[index].planteaza(p);
        std::cout << "Ai plantat " << p.getNume() << " pe parcela " << "index" << "\n";

    }

    void udaParcela(int index) {
        if (index < 0 || index >= numarParcele) return;
        if (parcele[index].isOcupata()) {
            parcele[index].ingrijestePlanta();
            std::cout << "Ai udat planta " << parcele[index].numePlanta() << " de pe parcela " << index << "\n";
        }
        else std::cout << "Parcela e goala, ai udat degeaba !\n";
    }

    void recolteaza(int index) {
        if (index < 0 || index >= numarParcele) return;
        if (!parcele[index].isOcupata()) {
            std::cout << "Parcela " << index << " este goala, nu ai ce recolta!\n";
            return;
        }
        if (parcele[index].gataDeRecoltat()) {
            std::string numeRecolta = parcele[index].recolteaza();
            hambar.adaugaRecolta(numeRecolta);
            std::cout << "[ ACTIUNE ]: Ai recoltat " << numeRecolta << " de pe parcela " << index << "\n";

        }
        else std::cout << "Planta nu poate fi recoltata!\n";
    }

    void ziuaUrmatoare() {
        std::cout << "Ziua " << ziuaCurenta << " s-a terminat!\n";
        ziuaCurenta++;
        std::cout << "A inceput ziua " << ziuaCurenta << " !\n";
        for (int i = 0; i < numarParcele; i++) {
            if (parcele[i].isOcupata()) {
                parcele[i].treciZiua();
            }
        }
    }

    Ferma& operator=(const Ferma& other) {
        if (this == &other) {
            return *this;
        }

        delete[] parcele;
        parcele = nullptr;
        numeFerma = other.numeFerma;
        hambar = other.hambar;
        portofel = other.portofel;
        magazin = other.magazin;
        ziuaCurenta = other.ziuaCurenta;
        numarParcele = other.numarParcele;
        if (other.numarParcele > 0 && other.parcele != nullptr) {
            parcele = new Parcela[other.numarParcele];
            for (int i = 0; i < other.numarParcele; i++)
                parcele[i] = other.parcele[i];
        }
        else parcele = nullptr;
        std::cout << "Ferma a fost suprascrisa! (Load Game reusit)\n";
        return *this;
    }

    friend std::ostream& operator<<(std::ostream &os, const Ferma &f) {
        os << "Ferma: " << f.numeFerma << "\n";
        os << "Portofel " << f.portofel << "\n";
        os << "Ziua curenta: " << f.ziuaCurenta << "\n";
        os << "Hambar: " << f.hambar << "\n";
        os << "TEREN: " << f.numarParcele << " parcele\n";
        if (f.parcele != nullptr && f.numarParcele > 0)
            for (int i = 0; i < f.numarParcele; i++)
                os << "Parcela " << i << " -> " << f.parcele[i] << "\n"; //apeleaza operatorul din Parcela
        return os;
    }
};


int main() {

    std::string numeFerma;
    std::cout << "Introdu numele fermei tale!: ";
    std::cin >> numeFerma;
    Ferma fermaMea(numeFerma, 3);

    Planta rosie("Rosie", "Leguma", 2);
    Planta lalea("Lalea", "Floare", 2);
    Planta gaina("Gaina", "Animal", 5);

    fermaMea.planteaza(0, rosie);
    fermaMea.planteaza(1, lalea);
    fermaMea.planteaza(2, gaina);

    fermaMea.udaParcela(0);
    fermaMea.udaParcela(1);
    fermaMea.ziuaUrmatoare();
    Ferma salvareZiua1 = fermaMea;

    fermaMea.udaParcela(0);
    fermaMea.ziuaUrmatoare();

    fermaMea.recolteaza(0);
    fermaMea.recolteaza(1);

    fermaMea.vinde("Rosie", 1);

    std::cout << "Ai pierdut laleaua, asa ca dam Load Game la Ziua 1!\n";
    fermaMea = salvareZiua1;
    fermaMea.extindeFerma(2);
    std::cout << "\n[ Starea Finala ]\n" << fermaMea;
    return 0;

    // std::string numeFerma;
    // std::cout << "Introdu numele fermei tale!: ";
    // std::cin  >> numeFerma;
    // Ferma fermaMea(numeFerma, 5);
    // Planta rosie("Rosie", "Leguma", 3);
    // Planta lalea("Lalea", "Floare", 2);
    // fermaMea.planteaza(0, rosie);
    // fermaMea.planteaza(1, lalea);
    // fermaMea.planteaza(2, rosie);
    // fermaMea.planteaza(3, rosie);
    // fermaMea.planteaza(4, lalea);
    // fermaMea.planteaza(5,lalea);
    // fermaMea.extindeFerma(1);
    // std::cout << fermaMea;


        // Ferma fermaMea("Mar", 3);
        // Planta rosie("Rosie", "Leguma", 2); // creste în 2 zile
        //
        // fermaMea.planteaza(0, rosie);
        // // Ziua 1
        // fermaMea.udaParcela(0);
        // fermaMea.ziuaUrmatoare();
        // fermaMea.extindeFerma(3);
        //
        // // Ziua 2 - Ajunge la maturitate!
        // fermaMea.udaParcela(0);
        // fermaMea.ziuaUrmatoare();
        // std::cout << "\n[Inainte de recoltare manuala]\n" << fermaMea;
        // fermaMea.recolteaza(0);
        //
        // // Afisam din nou ca sa vedem ca Parcela 0 s-a golit si Hambarul s-a umplut
        // std::cout << "\n[Dupa recoltare manuala]\n" << fermaMea;
        //
        // return 0;




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

}