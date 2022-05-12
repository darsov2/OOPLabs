//
// Created by David Arsov on 11.5.2022.
//

#include<bits/stdc++.h>

using namespace std;

class Delo
{
private:
    char ime[51], zemjaPoteklo[51];
    int godina;

public:
    Delo(const char *i = "", int g = 0, const char *zp = "")
    {
        strncpy(ime, i, 51);
        strncpy(zemjaPoteklo, zp, 51);
        godina = g;
    }

    bool operator==(const Delo &d)
    {
        return !strcmp(ime, d.ime);
    }

    int getGodina() const
    {
        return godina;
    }

    const char* getPoteklo() const
    {
        return zemjaPoteklo;
    }

    const char* getIme() const
    {
        return ime;
    }
};

class Pretstava
{
private:
    Delo delo;
    int brKarti;
    char datum[16];

public:
    Pretstava(Delo d = 0, int k = 0, const char *dat = "01.01.1900")
    {
        strncpy(datum, dat, 15);
        delo = d;
        brKarti = k;
    }

    virtual double cena()
    {
        double c = 0;
        if(delo.getGodina() >= 1900)
        {
            c += 50;
        }
        else if(delo.getGodina() >= 1800)
        {
            c += 75;
        }
        else
        {
            c += 100;
        }

        if(!strcmp("Rusija", delo.getPoteklo()))
        {
            c += 150;
        }
        else if(!strcmp("Italija", delo.getPoteklo()))
        {
            c += 100;
        }
        else
        {
            c += 80;
        }

        return c;
    }

    Delo getDelo()
    {
        return delo;
    }

    int getKarti()
    {
        return brKarti;
    }
};

class Balet : public Pretstava
{
private:
    static int dodatok;

public:
    Balet(Delo d = 0, int k = 0, const char *dat = "01.01.1900") : Pretstava(d, k, dat)
    {

    }

    double cena()
    {
        return Pretstava::cena() + dodatok;
    }

    static int setCenaBalet(int n)
    {
        dodatok = n;
    }
};

class Opera : public Pretstava
{
public:
    Opera(Delo d = 0, int k = 0, const char *dat = "01.01.1900") : Pretstava(d, k, dat)
    {

    }

    double cena()
    {
        return Pretstava::cena();
    }
};

double prihod(Pretstava **pretstavi, int n)
{lp
    double vkp = 0;
    for(int i = 0; i < n; i++)
    {
        vkp += pretstavi[i]->cena() * pretstavi[i]->getKarti();
    }
    return vkp;
}

int brojPretstaviNaDelo(Pretstava **pretstavi, int n, Delo d)
{
    int br = 0;
    for(int i = 0; i < n; i++)
    {
        if(pretstavi[i]->getDelo() == d)
        {
            br++;
        }
    }
    return br;
}

Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}

int Balet::dodatok = 150;

int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}