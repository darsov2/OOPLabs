//
// Created by David Arsov on 16.3.2022.
//
#include <bits/stdc++.h>

using namespace std;

class Rabotnik
{
    private:
    char ime[30], prezime[30];
    int plata;

    public:
    Rabotnik()
    {

    }

    Rabotnik(char *i, char *p, int pl)
    {
        strncpy(ime, i, 50);
        strncpy(prezime, p, 50);
        plata = pl;
    }

    int getPlata()
    {
        return plata;
    }

    void pecati()
    {
        cout << ime << " " << prezime << " " << plata << endl;
    }
};

class Fabrika
{
    private:
    Rabotnik rabotnik[100];
    int brojVraboteni;

    public:
    Fabrika()
    {

    }

    Fabrika(Rabotnik r[], int br)
    {
        brojVraboteni = br;
        for(int i = 0; i < brojVraboteni; i++)
        {
            rabotnik[i] = r[i];
        }
    }

    void pecatiVraboteni()
    {
        cout << "Site vraboteni:" << endl;
        for(int i = 0; i < brojVraboteni; i++)
        {
            rabotnik[i].pecati();
        }
    }

    void pecatiSoPlata(int plata)
    {
        cout << "Vraboteni so plata povisoka od " << plata << " :" << endl;
        for(int i = 0; i < brojVraboteni; i++)
        {
            if(rabotnik[i].getPlata() > plata)
            {
                rabotnik[i].pecati();
            }
        }
    }
};

int main() {
    int n;
    cin >> n;
    char ime[30], prezime[30];
    int plata;
    Rabotnik rab[100];
    for (int i = 0; i < n; i++)
    {
        cin >> ime >> prezime >> plata;
        rab[i] = Rabotnik(ime, prezime, plata);
    }
    int minPlata;
    cin >> minPlata;
    Fabrika fabrika(rab, n);
    fabrika.pecatiVraboteni();
    fabrika.pecatiSoPlata(minPlata);
}