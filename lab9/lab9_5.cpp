//
// Created by David Arsov on 9.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class InvalidDateException
{
private:
    int den, mesec, godina;

public:
    InvalidDateException(int d, int m, int g)
    {
        den = d;
        mesec = m;
        godina = g;
    }

    void poraka()
    {
        cout << "Invalid Date " << den << "/" << mesec << "/" << godina << endl;
    }
};

class NotSupportedCurrencyException
{
private:
    char valuta[4];

public:
    NotSupportedCurrencyException(char *v)
    {
        strncpy(valuta, v, 4);
    }

    void poraka()
    {
        cout << valuta << " is not a supported currency" << endl;
    }
};

class Transakcija
{
protected:
    int den, mesec, godina;
    double iznos;
    static double EUR, USD;

public:
    Transakcija(int d = 1, int m = 1, int g = 1900, double iz = 0)
    {
        if(d > 31 || d < 1 || m > 12 || m < 1)
        {
            throw InvalidDateException(d, m, g);
        }
        else
        {
            den = d;
            mesec = m;
            godina = g;
            iznos = iz;
        }
    }

    static void setEUR(double k)
    {
        EUR = k;
    }

    static void setUSD(double k)
    {
        USD = k;
    }

    static double getKursEur()
    {
        return EUR;
    }

    static double getKursUsd()
    {
        return USD;
    }

    virtual double voDenari() = 0;
    virtual double voEvra() = 0;
    virtual double voDolari() = 0;
    virtual void pecati() = 0;
};

class DeviznaTransakcija : public Transakcija
{
private:
    char valuta[4];

public:
    DeviznaTransakcija(int d = 1, int m = 1, int g = 1900, double iz = 0, char *v = "") : Transakcija(d, m, g, iz)
    {
        if(!strcmp(v, "EUR") || !strcmp(v, "USD"))
        {
            strncpy(valuta, v, 4);
        }
        else
        {
            throw NotSupportedCurrencyException(v);
        }
    }

    void pecati()
    {
        cout << den << "/" << mesec << "/" << godina << " " << iznos << " " << valuta << endl;
    }

    double voDenari()
    {
        if(!strcmp(valuta, "EUR"))
        {
            return iznos * EUR;
        }
        else if(!strcmp(valuta, "USD"))
        {
            return iznos * USD;
        }
    }

    double voEvra()
    {
        if(!strcmp(valuta, "EUR"))
        {
            return iznos;
        }
        else if(!strcmp(valuta, "USD"))
        {
            return iznos * USD / EUR;
        }
    }

    double voDolari()
    {
        if(!strcmp(valuta, "USD"))
        {
            return iznos;
        }
        else if(!strcmp(valuta, "EUR"))
        {
            return iznos * EUR / USD;
        }
    }

};

class DenarskaTransakcija : public Transakcija
{
public:
    DenarskaTransakcija(int d = 1, int m = 1, int g = 1900, double iz = 0) : Transakcija(d, m, g, iz)
    {

    }

    void pecati()
    {
        cout << den << "/" << mesec << "/" << godina << " " << iznos << " MKD" << endl;
    }

    double voDenari()
    {
        return iznos;
    }

    double voEvra()
    {
        return iznos / EUR;
    }

    double voDolari()
    {
        return iznos / USD;
    }
};

class Smetka
{
private:
    Transakcija **transakcii;
    int brTransakcii;
    char brSmetka[16];
    double pocSos;

public:
    Smetka(char *b = "", double p = 0)
    {
        strncpy(brSmetka, b, 16);
        pocSos = p;
        transakcii = new Transakcija*[0];
        brTransakcii = 0;
    }

    ~Smetka()
    {
        delete [] transakcii;
    }

    Smetka &operator+=(Transakcija *trs)
    {
        Transakcija **temp = new Transakcija*[brTransakcii + 1];
        for(int i = 0; i < brTransakcii; i++)
        {
            temp[i] = transakcii[i];
        }
        delete [] transakcii;
        transakcii = temp;
        transakcii[brTransakcii] = trs;
        brTransakcii++;
        return *this;
    }

    void izvestajVoDenari()
    {
        double saldoDenari = pocSos;
        for(int i = 0; i < brTransakcii; i++)
        {
            saldoDenari += transakcii[i]->voDenari();
        }
        cout << "Korisnikot so smetka: " << brSmetka << " ima momentalno saldo od " << saldoDenari << " MKD" << endl;
    }

    void izvestajVoEvra()
    {
        double saldoEvra = pocSos / Transakcija::getKursEur();
        for(int i = 0; i < brTransakcii; i++)
        {
            saldoEvra += transakcii[i]->voEvra();
        }
        cout << "Korisnikot so smetka: " << brSmetka << " ima momentalno saldo od " << saldoEvra << " EUR" << endl;
    }

    void izvestajVoDolari()
    {
        double saldoDolari = pocSos / Transakcija::getKursUsd();
        for(int i = 0; i < brTransakcii; i++)
        {
            saldoDolari += transakcii[i]->voDolari();
        }
        cout << "Korisnikot so smetka: " << brSmetka << " ima momentalno saldo od " << saldoDolari << " USD" << endl;
    }

    void pecatiTransakcii()
    {
        for(int i = 0; i < brTransakcii; i++)
        {
            transakcii[i]->pecati();
        }
    }
};

double Transakcija::EUR = 61;
double Transakcija::USD = 50;

int main () {

    Smetka s ("300047024112789",1500);

    int n, den, mesec, godina, tip;
    double iznos;
    char valuta [3];

    cin>>n;
    cout<<"===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI==="<<endl;
    for (int i=0;i<n;i++){
        cin>>tip>>den>>mesec>>godina>>iznos;
        if (tip==2){
            cin>>valuta;
            try
            {
                Transakcija * t = new DeviznaTransakcija(den,mesec,godina,iznos,valuta);
                s+=t;
                //delete t;
            }
            catch(NotSupportedCurrencyException &valuta)
            {
                valuta.poraka();
            }
            catch(InvalidDateException &datum)
            {
                datum.poraka();
            }
        }
        else {
            try
            {
                Transakcija * t = new DenarskaTransakcija(den,mesec,godina,iznos);
                s+=t;
                //delete t;
            }
            catch(NotSupportedCurrencyException &valuta)
            {
                valuta.poraka();
            }
            catch(InvalidDateException &datum)
            {
                datum.poraka();
            }
        }
    }

    cout<<"===PECHATENJE NA SITE TRANSAKCII==="<<endl;
    s.pecatiTransakcii();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();

    cout<<"\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n"<<endl;


    double newEUR, newUSD;
    cin>>newEUR>>newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();


    return 0;
}