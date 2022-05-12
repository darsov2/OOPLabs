//
// Created by David Arsov on 11.5.2022.
//

#include<bits/stdc++.h>

using namespace std;

enum tip
{
    smartphone,
    computer
};

class InvalidProductionDate
{
public:
    void poraka()
    {
        cout << "Невалидна година на производство" << endl;
    }
};

class Device
{
private:
    char model[101];
    tip type;
    int godina;
    static double casoviOP;

public:
    Device(const char *m = "", tip t = smartphone, int g = 0)
    {
        strncpy(model, m, 100);
        type = t;
        godina = g;
    }

    static void setPocetniCasovi(double t)
    {
        casoviOP = t;
    }

    double vremeProverka() const
    {
        double dodatok = 0;
        if(godina > 2015)
        {
            dodatok += 2;
        }
        if(type == 1)
        {
            dodatok += 2;
        }
        return casoviOP + dodatok;
    }

    friend ostream &operator<<(ostream &o, const Device &d)
    {
        return o << d.model << endl << (d.type == 0 ? "Mobilen" : "Laptop") << " " << d.vremeProverka() << endl;
    }

    int getGodina() const
    {
        return godina;
    }
};

class MobileServis
{
private:
    char adresa[101];
    Device *uredi;
    int brUredi;

public:
    MobileServis(const char *a = "")
    {
        brUredi = 0;
        uredi = new Device[0];
        strncpy(adresa, a, 100);
    }

    MobileServis(const MobileServis &ms)
    {
        brUredi = ms.brUredi;
        uredi = new Device[brUredi];
        for(int i = 0; i < brUredi; i++)
        {
            uredi[i] = ms.uredi[i];
        }
        strncpy(adresa, ms.adresa, 100);
    }

    MobileServis &operator+=(const Device &d)
    {
        if(d.getGodina() > 2019 || d.getGodina() < 2000)
        {
            throw InvalidProductionDate();
        }
        Device *temp = new Device[brUredi + 1];
        for(int i = 0; i < brUredi; i++)
        {
            temp[i] = uredi[i];
        }
        delete [] uredi;
        uredi = temp;
        uredi[brUredi] = d;
        brUredi++;
        return *this;
    }

    void pecatiCasovi()
    {
        cout << "Ime: " << adresa << endl;
        for(int i = 0; i < brUredi; i++)
        {
            cout << uredi[i];
        }
    }
};

double Device::casoviOP = 1;

int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try
            {
                t+=tmp;
            }
            catch(InvalidProductionDate &ip)
            {
                ip.poraka();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try
            {
                t+=tmp;
            }
            catch(InvalidProductionDate &ip)
            {
                ip.poraka();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try
            {
                t+=tmp;
            }
            catch(InvalidProductionDate &ip)
            {
                ip.poraka();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try
            {
                t+=tmp;
            }
            catch(InvalidProductionDate &ip)
            {
                ip.poraka();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try
            {
                t+=tmp;
            }
            catch(InvalidProductionDate &ip)
            {
                ip.poraka();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}