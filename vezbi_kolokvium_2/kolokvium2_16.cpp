//
// Created by David Arsov on 11.5.2022.
//

#include<bits/stdc++.h>

using namespace std;

class Transport
{
private:
    char destinacija[21];
    int cena, rastojanie;

public:
    Transport(const char *d = "", int c = 0, int r = 0)
    {
        strncpy(destinacija, d, 20);
        cena = c;
        rastojanie = r;
    }

    virtual double cenaTransport()
    {
        return cena;
    }

    bool operator<(Transport &t)
    {
        return rastojanie < t.rastojanie;
    }

    friend ostream &operator<<(ostream &o, Transport &t)
    {
        return o << t.destinacija << " " << t.rastojanie << " " << t.cenaTransport() << endl;
    }
};

class AvtomobilTransport : public Transport
{
private:
    bool platenSofer;

public:
    AvtomobilTransport(const char *d = "", int c = 0, int r = 0, bool s = 0) : Transport(d, c, r)
    {
        platenSofer = s;
    }

    double cenaTransport()
    {
        if(platenSofer)
        {
            return Transport::cenaTransport() * 1.2;
        }
        return Transport::cenaTransport();
    }
};

class KombeTransport : public Transport
{
private:
    int brPatnici;

public:
    KombeTransport(const char *d = "", int c = 0, int r = 0, int bp = 0) : Transport(d, c, r)
    {
        brPatnici = bp;
    }

    double cenaTransport()
    {
        return Transport::cenaTransport() - brPatnici * 200;
    }
};

void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport t)
{
    Transport **polosi = new Transport*[n];
    int j = 0;
    for(int i = 0; i < n; i++)
    {
        if(t.cenaTransport() < ponudi[i]->cenaTransport())
        {
            polosi[j] = ponudi[i];
            j++;
        }
    }

    for(int i = 0; i < j; i++)
    {
        for(int k = i + 1; k < j; k++)
        {
            if(*polosi[k] < *polosi[i])
            {
                swap(polosi[k], polosi[i]);
            }
        }
    }

    for(int i = 0; i < j; i++)
    {
        cout << *polosi[i];
    }
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
