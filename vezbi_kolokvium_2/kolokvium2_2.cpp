//
// Created by David Arsov on 9.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Vozac
{
protected:
    char ime[101];
    int vozrast, brTrki;
    bool veteran;

public:
    Vozac(const char *i = "", int v = 0, int br = 0, bool vet = false)
    {
        strncpy(ime, i, 100);
        vozrast = v;
        brTrki = br;
        veteran = vet;
    }

    friend ostream &operator<<(ostream &o, const Vozac &v)
    {
        return o << v.ime << endl << v.vozrast << endl << v.brTrki << endl << (v.veteran ? "VETERAN\n" : "");
    }

    virtual double zarabotuvacka() = 0;
    virtual double danok() = 0;

    bool operator==(Vozac &v)
    {
        return zarabotuvacka() == v.zarabotuvacka();
    }
};

class Avtomobilist : public Vozac
{
private:
    double cenaAuto;

public:
    Avtomobilist(const char *i = "", int v = 0, int br = 0, bool vet = false, double c = 0) : Vozac(i, v, br, vet)
    {
        cenaAuto = c;
    }

    double zarabotuvacka()
    {
        return cenaAuto / 5;
    }

    double danok()
    {
        if(brTrki > 10)
        {
            return zarabotuvacka() * 0.15;
        }
        return zarabotuvacka() * 0.1;
    }
};

class Motociklist : public Vozac
{
private:
    int moknost;

public:
    Motociklist(const char *i = "", int v = 0, int br = 0, bool vet = false, int m = 0) : Vozac(i, v, br, vet)
    {
        moknost = m;
    }

    double zarabotuvacka()
    {
        return moknost * 20;
    }

    double danok()
    {
        if(veteran)
        {
            return zarabotuvacka() * 0.25;
        }
        return zarabotuvacka() * 0.2;
    }
};

int soIstaZarabotuvachka(Vozac **vozaci, int brVozaci, Vozac *vozac)
{
    int ista = 0;
    for(int i = 0; i < brVozaci; i++)
    {
        if(*vozaci[i] == *vozac)
        {
            ista++;
        }
    }
    return ista;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}