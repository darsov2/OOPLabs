//
// Created by David Arsov on 2.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Vozilo
{
protected:
    double masa;
    int sirina, visina;

public:
    Vozilo(double m = 0, int s = 0, int v = 0)
    {
        masa = m;
        sirina = s;
        visina = v;
    }

    double getMasa()
    {
        return masa;
    }

    int getSirina()
    {
        return sirina;
    }

    virtual int tip() = 0;

    virtual int vratiDnenvaCena() = 0;
};

class Avtomobil : public Vozilo
{
private:
    int brVrati;

public:
    Avtomobil(double m = 0, int s = 0, int v = 0, int bv = 0) : Vozilo(m, s, v)
    {
        brVrati = bv;
    }

    int tip()
    {
        return 1;
    }

    int vratiDnenvaCena()
    {
        if(brVrati < 5)
        {
            return 100;
        }
        else
        {
            return 130;
        }
    }
};

class Avtobus : public Vozilo
{
private:
    int brPatnici;

public:
    Avtobus(double m = 0, int s = 0, int v = 0, int bp = 0) : Vozilo(m, s, v)
    {
        brPatnici = bp;
    }

    int tip()
    {
        return 2;
    }

    int vratiDnenvaCena()
    {
        return brPatnici * 5;
    }
};

class Kamion : public Vozilo
{
private:
    double nosivost;

public:
    Kamion(double m = 0, int s = 0, int v = 0, double n = 0) : Vozilo(m, s, v)
    {
        nosivost = n;
    }

    double getNosivost()
    {
        return nosivost;
    }

    int tip()
    {
        return 3;
    }

    int vratiDnenvaCena()
    {
        return (masa + nosivost) * 0.02;
    }
};

class ParkingPlac
{
private:
    Vozilo **koli;
    int brKoli;

public:
    ParkingPlac(Vozilo **v = 0, int bk = 0)
    {
        brKoli = bk;
        koli = new Vozilo*[brKoli];
        for(int i = 0; i < brKoli; i++)
        {
            koli[i] = v[i];
        }
    }

    ~ParkingPlac()
    {
        delete [] koli;
    }

    ParkingPlac &operator+=(Vozilo *v)
    {
        Vozilo **temp = new Vozilo*[brKoli + 1];
        for(int i = 0; i < brKoli; i++)
        {
            temp[i] = koli[i];
        }
        delete [] koli;
        koli = temp;
        koli[brKoli] = v;
        brKoli++;
        return *this;
    }

    float presmetajVkupnaMasa()
    {
        float vkp = 0;
        for(int i = 0; i < brKoli; i++)
        {
            vkp += koli[i]->getMasa();
        }
        return vkp;
    }

    int brojVozilaPoshirokiOd(int l)
    {
        int br = 0;
        for(int i = 0; i < brKoli; i++)
        {
            if(koli[i]->getSirina() > l)
            {
                br++;
            }
        }
        return br;
    }

    void pecati()
    {
        int kola = 0, bus = 0, kam = 0;
        for(int i = 0; i < brKoli; i++)
        {
            switch (koli[i]->tip())
            {
                case 1:
                    kola++;
                    break;
                case 2:
                    bus++;
                    break;
                case 3:
                    kam++;
                    break;
                default:
                    break;
            }
        }
        cout << "Brojot na avtomobili e " << kola << ", brojot na avtobusi e " << bus << " i brojot na kamioni e " << kam << "." << endl;
    }

    int pogolemaNosivostOd(Vozilo &v)
    {
        int br = 0;
        for(int i = 0; i < brKoli; i++)
        {
            Kamion *kam = dynamic_cast<Kamion *>(koli[i]);
            if(kam != 0 && kam->getNosivost())
            {
                br++;
            }
        }
        return br;
    }

    int vratiDnevnaZarabotka()
    {
        int zar = 0;
        for(int i = 0; i < brKoli; i++)
        {
            zar += koli[i]->vratiDnenvaCena();
        }
        return zar;
    }
};

int main(){
    ParkingPlac p;

    int n;
    cin>>n;
    int shirina,visina, broj;
    float masa,nosivost;
    for (int i=0;i<n;i++){
        int type;
        cin>>type;
        if(type==1){
            cin>>masa>>shirina>>visina>>broj;
            Avtomobil *a=new Avtomobil(masa,shirina,visina,broj);
            p+=a;
        }
        if(type==2){
            cin>>masa>>shirina>>visina>>broj;
            p+=new Avtobus(masa,shirina,visina,broj);
        }
        if(type==3){
            cin>>masa>>shirina>>visina>>nosivost;
            p+=new Kamion(masa,shirina,visina,nosivost);
        }
    }

    p.pecati();

    cout<<"\nZarabotkata e "<<p.vratiDnevnaZarabotka()<<endl;
    cout<<"Vkupnata masa e "<<p.presmetajVkupnaMasa()<<endl;
    cout<<"Brojot poshiroki od 5 e "<<p.brojVozilaPoshirokiOd(5)<<endl;
    Avtomobil a(1200,4,3,5);
    cout<<"Brojot na kamioni so nosivost pogolema od avtomobilot e "<<p.pogolemaNosivostOd(a)<<endl;
}