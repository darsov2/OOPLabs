//
// Created by David Arsov on 1.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Nedviznina
{
protected:
    char *adresa;
    int kvadratura, cenaKvadrat;

public:
    Nedviznina(char *a = " ", int k = 0, int c = 0)
    {
        adresa = new char[strlen(a) + 1];
        strcpy(adresa, a);
        kvadratura = k;
        cenaKvadrat = c;
    }

    Nedviznina(const Nedviznina &n)
    {
        adresa = new char[strlen(n.adresa) + 1];
        strcpy(adresa, n.adresa);
        kvadratura = n.kvadratura;
        cenaKvadrat = n.cenaKvadrat;
    }

    int cena()
    {
        return kvadratura * cenaKvadrat;
    }

    void pecati()
    {
        cout << adresa << ", Kvadratura: " << kvadratura << ", Cena po Kvadrat: " << cenaKvadrat << endl;
    }

    double danokNaImot()
    {
        return cena() * 0.05;
    }

    friend istream &operator>>(istream &i, Nedviznina &v)
    {
        i >> v.adresa >> v.kvadratura >> v.cenaKvadrat;
    }

    char *getAdresa()
    {
        return adresa;
    }
};

class Vila : public Nedviznina
{
private:
    int danokLuksuz;

public:
    Vila() : Nedviznina()
    {
        danokLuksuz = 0;
    }

    void pecati()
    {
        cout << adresa << ", Kvadratura: " << kvadratura << ", Cena po Kvadrat: " << cenaKvadrat << ", Danok na luksuz: " << danokLuksuz << endl;
    }

    double danokNaImot()
    {
        return cena() * (0.05 + danokLuksuz / 100.);
    }

    friend istream &operator>>(istream &i, Vila &v)
    {
        i >> v.adresa >> v.kvadratura >> v.cenaKvadrat >> v.danokLuksuz;
    }
};

int main(){
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}