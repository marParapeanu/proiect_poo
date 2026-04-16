#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>
#include <limits>

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

class Animal {
    std::string numeAnimal;
    std::string specie;
    int varsta;
    bool esteHranit;
    bool traieste;
public:
    Animal(std::string  nume, std::string  specieA) : numeAnimal(std::move(nume)), specie(std::move(specieA)), varsta(0), esteHranit(false), traieste(true) {}
    [[nodiscard]] const std::string& getNume() const {return numeAnimal;}
    [[nodiscard]] const std::string& getSpecie() const {return specie;}
    //[[nodiscard]] bool isAlive() const { return traieste;}

    void hraneste() {
        if (traieste) esteHranit = true;
    }

    void cresteZi() {
        if (!traieste) return;
        if (esteHranit) {
            varsta++;
            esteHranit= false;
        }
        else traieste = false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Animal& a) {
        if (!a.traieste) {
            os << " [ DECEDAT ]" << a.specie << " (a.nume) " << "a murit\n";
        }
        else {
            os << " a.specie:  " << a.numeAnimal << " | Varsta: " << a.varsta << " zile | " << (a.esteHranit ? " [ ESTE HRANIT ]" : " [ FOAME ] -> trebuie hranit!") << "\n";
        }
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
    std::vector<Animal> animale;

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
            std::cout << "Fonduri insuficiente pentru extindere!\n" << "Mai ai nevoie de " << costTotal - portofel.getBani() << " Monede!\n";
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

    void adaugaAnimal(const Animal& a) {
        int pret = magazin.getPretCumparare(a.getSpecie());
        if (portofel.getBani() < pret) {
            std::cout << "Bani insuficienti! Mai ai nevoie de " << pret - portofel.getBani() << " monede!\n";
            return;
        }
        portofel.cheltuie(pret);
        animale.push_back(a);
        std::cout << "Animal nou adaugat: " << a.getNume() << " ( " << a.getSpecie() << " )\n";
    }

    void hranesteAnimale() {
        for (auto& animal : animale) {
            animal.hraneste();
        }
        std::cout << "Toate animalele au fost hranite!\n";
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
        std::cout << "Ai plantat " << p.getNume() << " pe parcela " << index+1 << "\n";

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

        for (auto& animal : animale) {
            animal.cresteZi();
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
                os << "Parcela " << i+1 << " -> " << f.parcele[i] << "\n"; //apeleaza operatorul din Parcela
        os << "ANIMALE:\n";
        if (f.animale.empty()) {
            os << " Nu exista animale in ferma\n";
        }
        else {
            for (const auto& animal : f.animale) {
                os << " " << animal << "\n";
            }
        }

        return os;
    }
};

class Joc {
    Ferma* ferma;
    Ferma* salvare;
    bool ruleaza;
    static void titlu(const std::string& text) {
        std::cout << " " << text << "\n";
    }
    static void invalid() {std::cout << "Optiune invalida!\n";}
    static int citesteInt(const std::string& mesaj) {
        int val;
        std::cout << mesaj;
        while (!(std::cin >> val)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input invalid! \n" << mesaj;
        }
        return val;
    }

    void meniuTeren() {
        titlu("GESTIUNE TEREN");
        std::cout << "1. Planteaza\n" << "2. Uda o parcela\n" << "3. Recolteaza\n" << "0. Inapoi\n";
        int opt = citesteInt("> ");
        switch (opt) {
            case 1: {
                int index = citesteInt("Index parcela: ");
                titlu("SELECTEAZA PLANTA: ");
                std::cout << "1. Rosie (cost: 10 monede, maturitate 5 zile) \n"
                          << "2. Lalea (cost: 5 monede, maturitate 3 zile) \n";
                int alegere = citesteInt("> ");
                if (alegere == 1)
                    ferma->planteaza(index, Planta("Rosie", "Leguma", 5));
                else if (alegere == 2)
                    ferma->planteaza(index, Planta("Lalea", "Floare", 2));
                else invalid();
                break;
            }

            case 2: {
                int index = citesteInt("Index parcela: ");
                ferma->udaParcela(index);
                break;
            }

            case 3: {
                int index = citesteInt("Index parcela: ");
                ferma->recolteaza(index);
                break;
            }

            case 0: break;

            default: invalid();
        }
    }

    void meniuAnimale() {
        titlu("GESTIUNE ANIMALE");
        std::cout << "1. Cumpara animal\n" << "2. Hraneste toate animalele\n" << "0. Inapoi\n";
        int opt = citesteInt("> ");
        switch (opt) {
            case 1: {
                titlu("SELECTEAZA ANIMAL");
                std::cout << "1. Vaca  (cost: 50 monede)\n"
                          << "2. Gaina (cost: 20 monede)\n"
                          << "3. Porc (cost: 80 monede)\n";
                int alegere = citesteInt("> ");
                std::string numeAnimal;
                std::cout << "Numele animalului: ";
                std::cin >> numeAnimal;
                if (alegere == 1)
                    ferma->adaugaAnimal(Animal(numeAnimal, "Vaca"));
                else if (alegere == 2)
                    ferma->adaugaAnimal(Animal(numeAnimal, "Gaina"));
                else if (alegere == 3)
                    ferma->adaugaAnimal(Animal(numeAnimal, "Porc"));
                else invalid();
                break;
            }

            case 2: {
                ferma->hranesteAnimale();
                break;
            }

            case 0: break;
            default: invalid();
        }
    }

    void meniuMagazin() {
        titlu("MAGAZIN - VANZARE RECOLTA");
        std::cout << "1. Vinde Rosii\n"
                  << "2. Vinde Lalele\n"
                  << "0. Inapoi\n";
        int opt = citesteInt("> ");
        std::string produs;
        if (opt == 1) produs = "Rosie";
        else if (opt == 2) produs = "Lalea";
        else return;
        int cantitate = citesteInt("Cantitate: ");
        ferma->vinde(produs, cantitate);
    }

    void meniuFerma() {
        titlu("GESTIONARE FERMA");
        std::cout << "1. Extinde ferma\n"
                  << "2. Salveaza progresul\n"
                  << "3. Incarca salvare\n"
                  << "0. Inapoi\n";
        int opt = citesteInt("> ");
        switch (opt) {
            case 1: {
                int nrParcele = citesteInt("Cate parcele vrei sa adaugi? (cost: 50/parcela): ");
                ferma->extindeFerma(nrParcele);
                break;
            }
            case 2:
                delete salvare;
                salvare = new Ferma(*ferma);
                std::cout << "Progres salvat!\n";
                break;
            case 3:
                if (salvare == nullptr) {
                    std::cout << "Nu exista nicio salvare!\n";
                } else {
                    *ferma = *salvare;
                    std::cout << "Salvare incarcata cu succes!\n";
                }
                break;
            case 0: break;
            default: std::cout << "Optiune invalida.\n";
        }
    }

public:
    explicit Joc(const std::string& numeFerma, int nrParcele)
    : ferma(new Ferma(numeFerma, nrParcele)),
    salvare(nullptr),
    ruleaza(true) {}

    ~Joc() {
        delete ferma;
        delete salvare;
    }

    Joc(const Joc&) = delete;
    Joc& operator=(const Joc&) = delete;
    void ruleazaJocul() {
        while (ruleaza) {
            titlu("MENIU PRINCIPAL");
            std::cout << "1. Vezi status ferma\n"
                      << "2. Gestioneaza teren\n"
                      << "3. Gestioneaza animale\n"
                      << "4. Magazin (vinde recolta)\n"
                      << "5. Treci la ziua urmatoare\n"
                      << "6. Gestioneaza ferma (save/load/extinde)\n"
                      << "0. Iesi din joc\n";
            int opt = citesteInt("> ");
            switch (opt) {
                case 1: std::cout << *ferma; break;
                case 2: meniuTeren();         break;
                case 3: meniuAnimale();       break;
                case 4: meniuMagazin();       break;
                case 5: ferma->ziuaUrmatoare(); break;
                case 6: meniuFerma();         break;
                case 0: ruleaza = false;
                    std::cout << "La revedere! Multumim ca ai jucat!\n";
                    break;
                default: std::cout << "Optiune invalida.\n";
            }
        }
    }
};


int main() {

    std::string numeFerma;
    std::cout << "Introdu numele fermei tale! \n";
    std::cin >> numeFerma;
    Joc joc(numeFerma, 3);
    joc.ruleazaJocul();
    return 0;

}
