//
// Created by David Arsov on 2.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class ZicanInstrument
{
protected:
    char ime[20];
    int brZici;
    double osnCena;

public:
    ZicanInstrument(char *i = " ", int bz = 0, double oc = 0)
    {
        strncpy(ime, i, 20);
        brZici = bz;
        osnCena = oc;
    }

    bool operator==(ZicanInstrument &v)
    {
        return brZici == v.brZici;
    }

    friend ostream &operator<<(ostream &o, const ZicanInstrument &v)
    {
        return o << v.ime << " " << v.brZici << " " << v.osnCena << endl;
    }

    virtual double cena() = 0;
};

class Mandolina : public ZicanInstrument
{
private:
    char forma[20];

public:
    Mandolina(char *i = " ", int bz = 0, double oc = 0, char *f = " ") : ZicanInstrument(i, bz, oc)
    {
        strncpy(forma, f, 20);
    }

    double cena()
    {
        if(!strcmp(forma, "Neapolitan"))
        {
            return osnCena * 1.15;
        }
        else
        {
            return osnCena;
        }
    }
};

class Violina : public ZicanInstrument
{
private:
    double golemina;

public:
    Violina(char *i = " ", int bz = 0, double oc = 0, double g = 0) : ZicanInstrument(i, bz, oc)
    {
        golemina = g;
    }

    double cena()
    {
        if(golemina == 0.25)
        {
            return osnCena * 1.1;
        }
        else if(golemina == 1)
        {
            return osnCena * 1.2;
        }
        else
        {
            return osnCena;
        }
    }
};

void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **in, int n)
{
    for(int i = 0; i < n; i++)
    {

        if(*in[i] == zi)
        {
            cout << in[i]->cena() << endl;
        }
    }
}

int main() {
    char ime[20];
    int brojZici;
    float cena;
    char forma[20];
    cin >> ime >> brojZici >> cena >> forma;
    Mandolina m(ime, brojZici, cena, forma);
    int n;
    cin >> n;
    ZicanInstrument **zi = new ZicanInstrument*[2 * n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> brojZici >> cena >> forma;
        zi[i] = new Mandolina(ime, brojZici, cena, forma);
    }
    for(int i = 0; i < n; ++i) {
        float golemina;
        cin >> ime >> brojZici >> cena >> golemina;
        zi[n + i] = new Violina(ime, brojZici, cena, golemina);
    }
    pecatiInstrumenti(m, zi, 2 * n);
    for(int i = 0; i < 2 * n; ++i) {
        delete zi[i];
    }
    delete [] zi;
    return 0;
}