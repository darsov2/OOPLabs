//
// Created by David Arsov on 1.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Lekar
{
private:
    int faksimil;
    char ime[10], prezime[11];
    double poPlata;

public:
    Lekar(int f = 0, char *i = " ", char *p = " ", double pl = 0)
    {
        faksimil = f;
        strncpy(ime, i, 10);
        strcpy(prezime, p); //greska vo test case
        poPlata = pl;
    }

    Lekar(const Lekar &l)
    {
        faksimil = l.faksimil;
        strcpy(ime, l.ime);
        strcpy(prezime, l.prezime);
        poPlata = l.poPlata;
    }

    void pecati()
    {
        cout << faksimil << ": " << ime << " " << prezime << endl;
    }

    double plata()
    {
        return poPlata;
    }
};

class MaticenLekar : public Lekar
{
private:
    int brPacienti;
    double *kotizacii;

public:
    MaticenLekar(Lekar l = 0, int bp = 0, double *k = 0) : Lekar(l)
    {
        brPacienti = bp;
        kotizacii = new double[brPacienti];
        for(int i = 0; i < brPacienti; i++)
        {
            kotizacii[i] = k[i];
        }
    }

    double prosekKotizacii()
    {
        double pr = 0;
        for(int i = 0; i < brPacienti; i++)
        {
            pr += kotizacii[i];
        }
        return pr / brPacienti;
    }

    void pecati()
    {
        Lekar :: pecati();
        cout << "Prosek na kotizacii: " << prosekKotizacii() << endl;
    }

    double plata()
    {
        return Lekar :: plata() + prosekKotizacii() * 0.3;
    }
};

int main() {
    int n;
    cin>>n;
    int pacienti;
    double kotizacii[100];
    int faksimil;
    char ime [20];
    char prezime [20];
    double osnovnaPlata;

    Lekar * lekari = new Lekar [n];
    MaticenLekar * maticni = new MaticenLekar [n];

    for (int i=0;i<n;i++){
        cin >> faksimil >> ime >> prezime >> osnovnaPlata;
        lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);
    }

    for (int i=0;i<n;i++){
        cin >> pacienti;
        for (int j=0;j<pacienti;j++){
            cin >> kotizacii[j];
        }
        maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1){
        cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
        for (int i=0;i<n;i++){
            lekari[i].pecati();
            cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
        }
    }
    else {
        cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
        for (int i=0;i<n;i++){
            maticni[i].pecati();
            cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
        }
    }

    delete [] lekari;
    delete [] maticni;

    return 0;
}