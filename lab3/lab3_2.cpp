//
// Created by David Arsov on 16.3.2022.
//
#include <bits/stdc++.h>

using namespace std;

class Dogovor;

class Potpisuvac
{
    private:
    char ime[20], prezime[20], embg[14];

    public:
    Potpisuvac()
    {

    }

    Potpisuvac(char *i, char *p, char *mb)
    {
        strncpy(ime, i, 20);
        strncpy(prezime, p, 20);
        strncpy(embg, mb, 14);
    }

    Potpisuvac(Potpisuvac *p1)
    {
        strncpy(ime, p1->ime, 20);
        strncpy(prezime, p1->prezime, 20);
        strncpy(embg, p1->embg, 14);
    }

    friend Dogovor;
};

class Dogovor
{
private:
    int broj;
    char kategorija[50];
    Potpisuvac potpisuvaci[3];

public:
    Dogovor()
    {

    }

    Dogovor(int br, char *kat, Potpisuvac p[])
    {
        broj = br;
        strncpy(kategorija, kat, 50);
        for(int i = 0; i < 3; i++)
        {
            potpisuvaci[i] = p[i];
        }
    }

    bool proverka()
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = i + 1; j < 3; j++)
            {
                if(strcmp(potpisuvaci[i].embg, potpisuvaci[j].embg) == 0)
                {
                    return true;
                }
            }
        }
        return false;
    }
};


int main()
{
    char embg[13], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> embg >> ime >> prezime;
        cout << "Maticniot e: " << embg;
        Potpisuvac p1(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        cout << "Maticniot e: " << embg;
        Potpisuvac p2(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        cout << "Maticniot e: " << embg;
        Potpisuvac p3(ime, prezime, embg);
        cin >> broj >> kategorija;
        Potpisuvac p[3];
        p[0] = p1; p[1] = p2; p[2] = p3;
        Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl;
        if(d.proverka() == true)
            cout << "Postojat potpishuvaci so ist EMBG" << endl;
        else
            cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}