//
// Created by maria-parapeanu on 5/4/26.
//

#include "../include/Ferma.h"
#include <algorithm>


Ferma::Ferma(std::string nume, int nrParcele):
    numeFerma(std::move(nume)), ziuaCurenta(0), numarParcele(nrParcele) {
    parcele = new Parcela[numarParcele]; //parcele = pointer catre primul element din array
    std::cout << "Bine ai venit la ferma: " << numeFerma << "!\n";
    std::cout << "Ziua " << ziuaCurenta << "\n";
    std::cout << "Numar parcele: " << numarParcele << "\n";
}

Ferma::Ferma(const Ferma &other): //constructor de copiere, salvarea progresului pentru a putea reseta greseli
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

Ferma::~Ferma() { delete[] parcele; parcele = nullptr;}

void Ferma::extindeFerma(int parceleAdaugate) {
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

void Ferma::adaugaAnimal(const Animal &a) {
    int pret = magazin.getPretCumparare(a.getSpecie());
    if (portofel.getBani() < pret) {
        std::cout << "Bani insuficienti! Mai ai nevoie de " << pret - portofel.getBani() << " monede!\n";
        return;
    }
    portofel.cheltuie(pret);
    animale.push_back(a);
    std::cout << "Animal nou adaugat: " << a.getNume() << " ( " << a.getSpecie() << " )\n";

}

void Ferma::hranesteAnimale() {
    for (auto& animal : animale) {
        animal.hraneste();
    }
    std::cout << "Toate animalele au fost hranite!\n";
}

void Ferma::vinde(const std::string &numeProdus, int cantitate) {
    int pretBucata = magazin.getPretVanzare(numeProdus);

    if (hambar.extrageDinHambar(numeProdus, cantitate)) {
        int baniPrimiti = pretBucata * cantitate;
        portofel.adaugaBani((baniPrimiti));
        std::cout << "[Magazin] Ai vandut " << cantitate << " " << numeProdus << "\n";
    }
    else std::cout << "[Hambar] Nu ai suficiente " << numeProdus << "\n";

}

void Ferma::planteaza(int index, const Planta &p) {
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

void Ferma::udaParcela(int index) {
    if (index < 0 || index >= numarParcele) return;
    if (parcele[index].isOcupata()) {
        parcele[index].ingrijestePlanta();
        std::cout << "Ai udat planta " << parcele[index].numePlanta() << " de pe parcela " << index << "\n";
    }
    else std::cout << "Parcela e goala, ai udat degeaba !\n";
}

void Ferma::recolteaza(int index) {
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

void Ferma::ziuaUrmatoare() {
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

Ferma & Ferma::operator=(const Ferma &other) {
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

std::ostream & operator<<(std::ostream &os, const Ferma &f) {
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