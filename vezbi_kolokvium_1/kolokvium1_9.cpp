//
// Created by David Arsov on 24.2.2022.
//

#include <iostream>
#include <cstring>

using namespace std;

struct Laptop
{
    char firma[100];
    float monitor;
    bool touch;
    int cena;
};

struct ITStore
{
    char ime[100], lokacija[100];
    Laptop laptopi[100];
    int brLaptopi;
};

void print (ITStore its)
{
    cout << its.ime << " " << its.lokacija << endl;
    for(int i = 0; i < its.brLaptopi; i++)
    {
        cout << its.laptopi[i].firma << " " << its.laptopi[i].monitor << " " << its.laptopi[i].cena << endl;
    }
}

void najeftina_ponuda (ITStore its[], int n)
{
    int najStore = 0, najLaptop = 0, maxCena = INT32_MAX;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < its[i].brLaptopi; j++)
        {
            if(its[i].laptopi[j].touch == true)
            {
                if(its[i].laptopi[j].cena < maxCena)
                {
                    najStore = i;
                    najLaptop = j;
                    maxCena = its[i].laptopi[j].cena;
                }
            }
        }
    }
    cout << "Najeftina ponuda ima prodavnicata: " << endl << its[najStore].ime << " " << its[najStore].lokacija << endl;
    cout << "Najniskata cena iznesuva: " << its[najStore].laptopi[najLaptop].cena;
}

int main()
{
    ITStore s[100];
    int n;
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cin >> s[i].ime >> s[i].lokacija >> s[i].brLaptopi;
        for(int j = 0; j < s[i].brLaptopi; j++)
        {
            cin >> s[i].laptopi[j].firma >> s[i].laptopi[j].monitor >> s[i].laptopi[j].touch >> s[i].laptopi[j].cena;
        }
    }

    for(int i = 0; i < n; i++)
    {
        print(s[i]);
    }

    najeftina_ponuda(s, n);
    return 0;
}