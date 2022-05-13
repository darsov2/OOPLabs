//
// Created by David Arsov on 11.5.2022.
//

#include<bits/stdc++.h>

using namespace std;

class FudbalskaEkipa
{
protected:
    char imeTrener[100];
    int brGolovi[10];

public:
    FudbalskaEkipa(const char *it = "", int *bg = 0)
    {
        strncpy(imeTrener, it, 100);
        for(int i = 0; i < 10; i++)
        {
            brGolovi[i] = bg[i];
        }
    }

    virtual double uspeh() = 0;

    bool operator>(FudbalskaEkipa &fe)
    {
        return uspeh() > fe.uspeh();
    }

    FudbalskaEkipa &operator+=(int br)
    {
        for(int i = 0; i < 9; i++)
        {
            brGolovi[i] = brGolovi[i + 1];
        }
        brGolovi[9] = br;
    }

    virtual char* getIme() = 0;

    friend ostream &operator<<(ostream &o, FudbalskaEkipa &fe)
    {
        return o << fe.getIme() << endl << fe.imeTrener << endl << fe.uspeh() << endl;
    }

};

class Klub : public FudbalskaEkipa
{
private:
    char ime[101];
    int tituli;

public:
    Klub(const char *it = "", int *bg = 0, const char *im = "", int t = 0) : FudbalskaEkipa(it, bg)
    {
        strncpy(ime, im, 100);
        tituli = t;
    }

    double uspeh()
    {
        double u = 0;
        for(int i = 0; i < 10; i++)
        {
            u += brGolovi[i];
        }
        u *= 3;
        u += tituli * 1000;
    }

    char* getIme()
    {
        return ime;
    }
};

class Reprezentacija : public FudbalskaEkipa
{
private:
    char ime[101];
    int brNastapi;

public:
    Reprezentacija(const char *it = "", int *bg = 0, const char *im = "", int t = 0) : FudbalskaEkipa(it, bg)
    {
        strncpy(ime, im, 100);
        brNastapi = t;
    }

    double uspeh()
    {
        double u = 0;
        for(int i = 0; i < 10; i++)
        {
            u += brGolovi[i];
        }
        u *= 3;
        u += brNastapi * 50;
    }

    char* getIme()
    {
        return ime;
    }

};

void najdobarTrener(FudbalskaEkipa **fe, int n)
{
    int najdobar = 0;
    for(int i = 0; i < n; i++)
    {
        if(*fe[i] > *fe[najdobar])
        {
            najdobar = i;
        }
    }
    cout << *fe[najdobar];
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}