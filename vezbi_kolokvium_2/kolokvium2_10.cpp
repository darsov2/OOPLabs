//
// Created by David Arsov on 11.5.2022.
//

#include<bits/stdc++.h>

using namespace std;

class NegativnaVrednost
{
public:
    void poraka()
    {
        cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
    }
};

class Oglas
{
private:
    char naslov[51], kategorija[31], opis[101];
    double cena;

public:
    Oglas(const char *n = "", const char *k = "", const char *o = "", double c = 0)
    {
        strncpy(naslov, n, 100);
        strncpy(kategorija, k, 30);
        strncpy(opis, o, 100);
        cena = c;
    }

    bool operator>(const Oglas &o)
    {
        return cena > o.cena;
    }

    friend ostream &operator<<(ostream &o, const Oglas &og)
    {
        return o << og.naslov << endl << og.opis << endl << og.cena << " evra" << endl << endl;
    }

    double getCena() const
    {
        return cena;
    }

    const char* getKategorija() const
    {
        return kategorija;
    }
};

class Oglasnik
{
private:
    char ime[21];
    Oglas *oglasi;
    int brOglasi;

public:
    Oglasnik(const char *i = "")
    {
        strncpy(ime, i, 20);
    }

    Oglasnik(const Oglasnik &o)
    {
        strncpy(ime, o.ime, 20);
        oglasi = new Oglas[o.brOglasi];
        brOglasi = o.brOglasi;
        for(int i = 0; i < brOglasi; i++)
        {
            oglasi[i] = o.oglasi[i];
        }
    }

    Oglasnik &operator+=(const Oglas &o)
    {
        if(o.getCena() < 0)
        {
            throw NegativnaVrednost();
        }
        Oglas *temp = new Oglas[brOglasi + 1];
        for(int i = 0; i < brOglasi; i++)
        {
            temp[i] = oglasi[i];
        }
        delete [] oglasi;
        oglasi = temp;
        oglasi[brOglasi] = o;
        brOglasi++;
        return *this;
    }

    friend ostream &operator<<(ostream &o, const Oglasnik &og)
    {
        o << og.ime << endl;
        for(int i = 0; i < og.brOglasi; i++)
        {
            o << og.oglasi[i];
        }
        return o;
    }

    void oglasOdKategorija(const char *k)
    {
        for(int i = 0; i < brOglasi; i++)
        {
            if(!strcmp(oglasi[i].getKategorija(), k))
            {
                cout << oglasi[i];
            }
        }
    }

    void najniskaCena()
    {
        int najniska = 0;
        for(int i = 0; i < brOglasi; i++)
        {
            if(oglasi[i].getCena() < oglasi[najniska].getCena())
            {
                najniska = i;
            }
        }
        cout << oglasi[najniska];
    }
};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try
            {
                ogl+=o;
            }
            catch(NegativnaVrednost &n)
            {
                n.poraka();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try
            {
                ogl+=o;
            }
            catch(NegativnaVrednost &n)
            {
                n.poraka();
            }
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try
            {
                ogl+=o;
            }
            catch(NegativnaVrednost &n)
            {
                n.poraka();
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try
            {
                ogl+=o;
            }
            catch(NegativnaVrednost &n)
            {
                n.poraka();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try
            {
                ogl+=o;
            }
            catch(NegativnaVrednost &n)
            {
                n.poraka();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}