//
// Created by David Arsov on 24.2.2022.
//

#include <iostream>
#include <cstring>

using namespace std;

struct Igrac
{
    char korisnickoIme[15];
    int nivo, poeni;
};

struct kompjuterskaIgra
{
    char ime[20];
    Igrac igraci[30];
    int brIgraci;
};

void najdobarIgrac (kompjuterskaIgra *lista, int n)
{
    int maxPopular = 0, maxIgrac = 0, maxIgra = 0;

    for(int i = 0; i < n; i++)
    {
        if(lista[i].brIgraci > maxPopular)
        {
            maxPopular = lista[i].brIgraci;
            maxIgra = i;
            //int igracPoeni = -1;
            for(int j = 0; j < maxPopular; j++)
            {
                if(lista[i].igraci[j].poeni > lista[i].igraci[maxIgrac].poeni )
                {
                    maxIgrac = j;
                }
                else if(lista[i].igraci[j].poeni > lista[i].igraci[maxIgrac].poeni)
                {
                    if(lista[i].igraci[j].nivo > lista[i].igraci[maxIgrac].nivo)
                    {
                        maxIgrac = j;
                    }
                }
            }
        }
    }

    cout << "Najdobar igrac e igracot so korisnicko ime " << lista[maxIgra].igraci[maxIgrac].korisnickoIme << " koj ja igra igrata " << lista[maxIgra].ime;
}

int main()
{
    int n,m;
    char ime[20];
    cin>>n;
    kompjuterskaIgra poleigri[100];
    for (int i=0; i<n; i++) {
        kompjuterskaIgra nova;
        cin>>nova.ime>>nova.brIgraci;
        Igrac pole[30];
        for (int j=0; j<nova.brIgraci; j++) {
            Igrac nov;
            cin>>nov.korisnickoIme>>nov.nivo>>nov.poeni;
            nova.igraci[j]=nov;
        }
        poleigri[i]=nova;
    }

    najdobarIgrac(poleigri,n);
    return 0;
}