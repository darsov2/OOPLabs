//
// Created by David Arsov on 1.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Automobile
{
private:
    char *ime;
    int *registracija;
    int maxBrzina;

public:
    Automobile (char *i = "", int *reg = 0, int mb = 0)
    {
        registracija = new int[5];
        if(reg != 0)
        {
            for(int i = 0; i < 5; i++)
            {
                registracija[i] = reg[i];
            }
        }
        ime = new char [strlen(i) + 1];
        strcpy(ime, i);
        maxBrzina = mb;
    }

    Automobile (const Automobile &a)
    {
        registracija = new int[5];
        ime = new char[strlen(a.ime) + 1];
        for(int i = 0; i < 5; i++)
        {
            registracija[i] = a.registracija[i];
        }
        strcpy(ime, a.ime);
        maxBrzina = a.maxBrzina;
    }

    ~Automobile()
    {
        delete [] registracija;
        delete [] ime;
    }

    bool operator==(const Automobile &a)
    {
        for(int i = 0; i < 5; i++)
        {
            if(registracija[i] != a.registracija[i])
            {
                return false;
            }
        }
        return true;
    }

    friend ostream &operator<<(ostream &o, Automobile &a)
    {
        o << "Marka\t" << a.ime << "\tRegistracija[ ";
        for(int i = 0; i < 5; i++)
        {
            o << a.registracija[i] << " ";
        }
        o << "]";
        return o;
    }

    Automobile &operator=(const Automobile &a)
    {
        if(this != &a)
        {
            delete [] registracija;
            delete [] ime;
            registracija = new int[5];
            ime = new char[strlen(a.ime) + 1];
            for(int i = 0; i < 5; i++)
            {
                registracija[i] = a.registracija[i];
            }
            maxBrzina = a.maxBrzina;
            strcpy(ime, a.ime);
        }
        return *this;
    }

    int getBrzina()
    {
        return maxBrzina;
    }
};

class RentACar
{
private:
    char ime[100];
    Automobile *koli;
    int brKoli;

public:
    RentACar(char *i = 0)
    {
        strncpy(ime, i, 100);
        brKoli = 0;
        koli = new Automobile[0];
    }

    RentACar &operator+=(const Automobile &a)
    {
        Automobile *temp = new Automobile[brKoli + 1];
        for(int i = 0; i < brKoli; i++)
        {
            temp[i] = koli[i];
        }
        delete [] koli;
        koli = temp;
        koli[brKoli] = a;
        brKoli++;
        return *this;
    }

    RentACar &operator-=(const Automobile &a)
    {
        Automobile *temp = new Automobile[brKoli - 1];
        int j = 0;
        for(int i = 0; i < brKoli; i++)
        {
            if(!(koli[i] == a))
            {
                temp[j] = koli[i];
                j++;
            }
        }
        delete [] koli;
        koli = temp;
        brKoli = j;
    }

    void pecatiNadBrzina(int max)
    {
        cout << ime << endl;
        for(int i = 0; i < brKoli; i++)
        {
            if(koli[i].getBrzina() > max)
            {
                cout << koli[i];
            }
        }
    }
};

int main()
{
    RentACar agencija("FINKI-Car");
    int n;
    cin>>n;

    for (int i=0;i<n;i++)
    {
        char marka[100];
        int regisracija[5];
        int maximumBrzina;

        cin>>marka;

        for (int i=0;i<5;i++)
            cin>>regisracija[i];

        cin>>maximumBrzina;

        Automobile nov=Automobile(marka,regisracija,maximumBrzina);

        //dodavanje na avtomobil
        agencija+=nov;

    }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin>>marka;
    for (int i=0;i<5;i++)
        cin>>regisracija[i];
    cin>>maximumBrzina;

    Automobile greshka=Automobile(marka,regisracija,maximumBrzina);

    //brishenje na avtomobil
    agencija-=greshka;

    agencija.pecatiNadBrzina(150);

    return 0;
}
