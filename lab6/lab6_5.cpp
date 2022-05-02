//
// Created by David Arsov on 1.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Ekipa
{
protected:
    char ime[15];
    int brPobedi, brPorazi;

public:
    Ekipa(char *i = " ", int bpb = 0, int bpo = 0)
    {
        strncpy(ime, i, 15);
        brPobedi = bpb;
        brPorazi = bpo;
    }

    void pecati()
    {
        cout << "Ime: " << ime << " Pobedi: " << brPobedi << " Porazi: " << brPorazi << endl;
    }
};

class FudbalskaEkipa : public  Ekipa
{
private:
    int brCrveni, brZolti, brNereseni;

public:
    FudbalskaEkipa(char *i = " ", int bpb = 0, int bpo = 0, int ck = 0, int zk = 0, int ner = 0) : Ekipa(i, bpb, bpo)
    {
        brCrveni = ck;
        brZolti = zk;
        brNereseni = ner;
    }

    void pecati()
    {
        cout << "Ime: " << ime << " Pobedi: " << brPobedi << " Porazi: " << brPorazi << " Nereseni: " << brNereseni << " Poeni: " << brPobedi * 3 + brNereseni * 1;
    }
};

int main(){
    char ime[15];
    int pob,por,ck,zk,ner;
    cin>>ime>>pob>>por>>ck>>zk>>ner;
    FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
    f1.pecati();
    return 0;
}