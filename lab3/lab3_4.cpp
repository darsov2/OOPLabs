//
// Created by David Arsov on 16.3.2022.
//
#include <bits/stdc++.h>

using namespace std;

class Masa
{
    private:
    int dolzina, sirina;

    public:
    Masa()
    {

    }

    Masa(int d, int s)
    {
        dolzina = d;
        sirina = s;
    }

    void pecati()
    {
        cout << "Masa: " << dolzina << " " << sirina << endl;
    }
};

class Soba
{
    private:
    Masa masa;
    int dolzina, sirina;
    public:
    Soba()
    {

    }

    Soba(int s, int d, Masa m)
    {
        masa = m;
        dolzina = d;
        sirina = s;
    }

    void pecati()
    {
        cout << "Soba: " << sirina << " " << dolzina << " ";
        masa.pecati();
    }
};

class Kukja
{
    private:
    Soba soba;
    char adresa[50];

    public:
    Kukja()
    {

    }

    Kukja(Soba s, char *a)
    {
        soba = s;
        strncpy(adresa, a, 50);
    }

    void pecati()
    {
        cout << "Adresa: " << adresa << " ";
        soba.pecati();
    }
};

int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int masaSirina,masaDolzina;
        cin>>masaSirina;
        cin>>masaDolzina;
        Masa m(masaSirina,masaDolzina);
        int sobaSirina,sobaDolzina;
        cin>>sobaSirina;
        cin>>sobaDolzina;
        Soba s(sobaSirina,sobaDolzina,m);
        char adresa[30];
        cin>>adresa;
        Kukja k(s,adresa);
        k.pecati();
    }

    return 0;
}