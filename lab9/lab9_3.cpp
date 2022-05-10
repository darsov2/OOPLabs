//
// Created by David Arsov on 9.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class ImaMasa
{
private:

public:
    virtual double vratiMasa() = 0;
    virtual void pecati() = 0;
};

class PaketPijalok
{
protected:
    double volumenEden;
    int kolicina;
    static double gustina, ambalaza;

public:
    PaketPijalok(double v = 0, int k = 0)
    {
        volumenEden = v;
        kolicina = k;
    }

    double vratiMasa()
    {
        return (volumenEden * gustina + ambalaza) * kolicina;
    }

    void pecati()
    {

    }

    int getKolicina()
    {
        return kolicina;
    }
};

class PaketSok : public ImaMasa, public PaketPijalok
{
private:
    bool daliGaziran;

public:
    PaketSok(double v = 0, int k = 0, bool g = 0) : PaketPijalok(v, k)
    {
        daliGaziran = g;
    }

    double vratiMasa()
    {
        if(!daliGaziran)
        {
            return (volumenEden * gustina + ambalaza + 0.1) * kolicina;
        }
        else
        {
            return (volumenEden * gustina + ambalaza) * kolicina;
        }
    }

    void pecati()
    {
        cout << "Paket sok" << endl;
        cout << "kolicina " << kolicina << ", so po " << volumenEden * gustina<< " l(dm3)" << endl;
    }
};

class PaketVino : public ImaMasa, public PaketPijalok
{
private:
    double procentAlkohol;

public:
    PaketVino(double v = 0, int k = 0, double pa = 0) : PaketPijalok(v, k)
    {
        procentAlkohol = pa;
    }

    double vratiMasa()
    {
        return (volumenEden * gustina + ambalaza) * kolicina * (0.9 + procentAlkohol);
    }

    double getProcentAlkohol()
    {
        return procentAlkohol;
    }

    void pecati()
    {
        cout << "Paket vino" << endl;
        cout << "kolicina " << kolicina << ", " << procentAlkohol * 100<< "% alkohol od po " << volumenEden * gustina<< " l(dm3)" << endl; //volumen ne se mnozi so gustina???
    }
};

class Kamion
{
private:
    char *registracija, *vozac;
    ImaMasa **tovar;
    int brTovar;

public:
    Kamion(char *r, char *v) {
        vozac = new char[strlen(v) + 1];
        strcpy(vozac, v);
        registracija = new char[0];
        try {
            registriraj(r);
        }
        catch (int n) {
            throw n;
        }
        tovar = new ImaMasa *[0];
        brTovar = 0;
    }

    ~Kamion()
    {
        delete [] tovar;
    }

    void registriraj(char *r)
    {
        if(strlen(r) == 8 && isalpha(r[0]) && isalpha(r[1]) && isalpha(r[7]) && isalpha(r[6]))
        {
            delete [] registracija;
            registracija = new char[strlen(r) + 1];
            strcpy(registracija, r);
        }
        else
        {
            throw 1;
        }
    }

    void dodadiElement(ImaMasa *im)
    {
        ImaMasa **temp = new ImaMasa*[brTovar];
        for(int i = 0; i < brTovar; i++)
        {
            temp[i] = tovar[i];
        }
        delete [] tovar;
        tovar = temp;
        tovar[brTovar] = im;
        brTovar++;
    }

    double vratiVkupnaMasa()
    {
        double vkMasa = 0;

        for(int i = 0; i < brTovar; i++)
        {
            vkMasa += tovar[i]->vratiMasa();
        }

        return vkMasa;
    }

    void pecati()
    {
        cout << "Kamion so registracija " << registracija << " i vozac " << vozac << " prenesuva:" << endl;
        for(int i = 0; i < brTovar; i++)
        {
            tovar[i]->pecati();
        }
    }

    Kamion pretovar(char *v, char *r)
    {
        int maxMasa = 0;
        for(int i = 0; i < brTovar; i++)
        {
            if(tovar[i]->vratiMasa() > tovar[maxMasa]->vratiMasa())
            {
                maxMasa = i;
            }
        }

        Kamion novKamion(v, r);
        for(int i = 0; i < brTovar; i++)
        {
            if(i != maxMasa)
            {
                novKamion.dodadiElement(tovar[i]);
            }
        }

        return novKamion;
    }
};

double PaketPijalok::gustina = 0.8;
double PaketPijalok::ambalaza = 0.2;

int main()
{
    char ime[20], reg[9];
    double vol;
    int kol;
    bool g;
    double proc;

    cin>>reg;
    cin>>ime;
    try
    {
        Kamion A(reg, ime);
        ImaMasa **d = new ImaMasa*[5];
        cin>>vol>>kol;
        cin>>g;
        d[0] = new PaketSok(vol, kol, g);
        cin>>vol>>kol;
        cin>>proc;
        d[1] = new PaketVino(vol, kol, proc);
        cin>>vol>>kol;
        cin>>proc;
        d[2] = new PaketVino(vol, kol, proc);
        cin>>vol>>kol;
        cin>>g;
        d[3] = new PaketSok(vol, kol, g);
        cin>>vol>>kol;
        cin>>proc;
        d[4] = new PaketVino(vol, kol, proc);

        A.dodadiElement(d[0]);
        A.dodadiElement(d[1]);
        A.dodadiElement(d[2]);
        A.dodadiElement(d[3]);
        A.dodadiElement(d[4]);
        A.pecati();
        cout<<"Vkupna masa: "<<A.vratiVkupnaMasa()<<endl;
        cin>>reg;
        cin>>ime;
        Kamion B = A.pretovar(reg, ime);
        B.pecati();
        cout<<"Vkupna masa: "<<B.vratiVkupnaMasa()<<endl;
    }
    catch(int n)
    {
        if(n == 1)
        {
            cout << "Pogresno vnesena registracija" << endl;
        }
    }


}
