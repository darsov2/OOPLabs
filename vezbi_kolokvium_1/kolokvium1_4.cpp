//
// Created by David Arsov on 25.3.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Patnik
{
    private:
    char ime[100];
    int klasa;
    bool tocak;

    public:
    Patnik(char *i = "", int k = 0, bool t = false)
    {
        strncpy(ime, i, 100);
        klasa = k;
        tocak = t;
    }

    bool imaTocak() const
    {
        return tocak;
    }

    int getKlasa()
    {
        return klasa;
    }

    friend ostream &operator<<(ostream &o, Patnik &p)
    {
        return o << p.ime << endl << p.klasa << endl << p.tocak << endl;
    }
};

class Voz
{
    private:
    char destinacija[100];
    Patnik *patnici;
    int brPatnici, brVelosipedi;

    public:
    Voz(char *d = "", int bv = 0, Patnik p[] = 0, int bp = 0)
    {
        strncpy(destinacija, d, 100);
        patnici = new Patnik[bp];
        brPatnici = bp;
        brVelosipedi = bv;
        for(int i = 0; i < brPatnici; i++)
        {
            patnici[i] = p[i];
        }
    }

    Voz(const Voz &v)
    {
        strncpy(destinacija, v.destinacija, 100);
        patnici = new Patnik[v.brPatnici];
        brPatnici = v.brPatnici;
        brVelosipedi = v.brVelosipedi;
        for(int i = 0; i < brPatnici; i++)
        {
            patnici[i] = v.patnici[i];
        }
    }

    Voz &operator=(const Voz &v)
    {
        strncpy(destinacija, v.destinacija, 100);
        delete [] patnici;
        patnici = new Patnik[v.brPatnici];
        brPatnici = v.brPatnici;
        brVelosipedi = v.brVelosipedi;
        for(int i = 0; i < brPatnici; i++)
        {
            patnici[i] = v.patnici[i];
        }
    }

    Voz &operator+=(const Patnik &p)
    {
        if(p.imaTocak() && brVelosipedi || !p.imaTocak())
        {
            Patnik *temp = new Patnik[brPatnici + 1];
            for(int i = 0; i < brPatnici; i++)
            {
                temp[i] = patnici[i];
            }
            delete [] patnici;
            patnici = temp;
            patnici[brPatnici] = p;
            brPatnici++;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &o, const Voz &v)
    {
        o << v.destinacija << endl;
        for(int i = 0; i < v.brPatnici; i++)
        {
            o << v.patnici[i] << endl;
        }
        return o;
    }

    void patniciNemaMesto()
    {
        int kl1 = 0, kl2 = 0;
        for(int i = 0; i < brPatnici; i++)
        {
            if(patnici[i].getKlasa() == 1 && patnici[i].imaTocak())
            {
                kl1++;
            }
            else if(patnici[i].getKlasa() == 2 && patnici[i].imaTocak())
            {
                kl2++;
            }
        }
        if(brVelosipedi >= kl1)
        {
            cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << 0;
            if(brVelosipedi - kl1 >= kl2)
            {
                cout << endl << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << 0;
            }
            else
            {
                cout << endl << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << kl2 - (brVelosipedi - kl1);
            }
        }
        else
        {
            cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << kl1 - brVelosipedi;
            cout << endl << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << kl2;
        }
    }
};
int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}