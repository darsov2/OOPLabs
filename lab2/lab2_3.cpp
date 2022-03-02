//
// Created by David Arsov on 2.3.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Film
{
private:
    char ime[102], reziser[52], zanr[52];
    int godina;

public:
    Film()
    {

    }

    Film(char *ime, char *reziser, char* zanr, int godina)
    {
        strcpy(this->ime, ime);
        strcpy(this->reziser, reziser);
        strcpy(this->zanr, zanr);
        this->godina = godina;
    }

    void pecatiInfo()
    {
        cout << "Ime: " << ime << endl;
        cout << "Reziser: " << reziser << endl;
        cout << "Zanr: " << zanr << endl;
        cout << "Godina: " << godina << endl;
    }

    int getGodina()
    {
        return godina;
    }
};

void pecati_po_godina(Film *f, int n, int godina)
{
    for(int i = 0; i < n; i++)
    {
        if(f[i].getGodina() == godina)
        {
            f[i].pecatiInfo();
        }
    }
}

int main()
{
    int n;
    cin >> n;
    Film f[n];
    for(int i = 0; i < n; ++i) {
        char ime[100];
        char reziser[50];
        char zanr[50];
        int godina;
        cin >> ime;
        cin >> reziser;
        cin >> zanr;
        cin >> godina;
        Film temp(ime, reziser, zanr, godina);
        f[i] = temp;
    }
    int godina;
    cin >> godina;
    pecati_po_godina(f, n, godina);
    return 0;
}