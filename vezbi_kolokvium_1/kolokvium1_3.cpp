//
// Created by David Arsov on 25.3.2022.
//

#include <bits/stdc++.h>

using namespace std;

class StockRecord
{
    private:
    char id[12], komp[50];
    float cenaKupeni, cenaMom;
    int brAkcii;

    public:
    StockRecord(char *i = "", char *k = "", float ck = 0, int ba = 0, float cm = 0)
    {
        strncpy(id, i, 12);
        strncpy(komp, k, 50);
        cenaKupeni = ck;
        cenaMom = cm;
        brAkcii = ba;
    }

    void setNewPrice(double c)
    {
        cenaMom = c;
    }

    double value()
    {
        return brAkcii * cenaMom;
    }

    double profit() const
    {
        return brAkcii * (cenaMom - cenaKupeni);
    }

    friend ostream &operator<<(ostream &o, const StockRecord &sr)
    {
        return o << sr.komp << " " << sr.brAkcii << " " << sr.cenaKupeni << " " << sr.cenaMom << " " << sr.profit() << endl;
    }
};

class Client
{
    private:
    char imePrezime[60];
    int idSmetka, brKompanii;
    StockRecord *kompanii;

    public:
    Client(char *ip = "", int id = 0, StockRecord sr[] = 0, int br = 0)
    {
        strncpy(imePrezime, ip, 60);
        idSmetka = id;
        kompanii = new StockRecord[br];
        brKompanii = br;
        for(int i = 0; i < brKompanii; i++)
        {
            kompanii[i] = sr[i];
        }
    }

    Client(const Client &c)
    {
        strncpy(imePrezime, c.imePrezime, 60);
        idSmetka = c.idSmetka;
        kompanii = new StockRecord[c.brKompanii];
        brKompanii = c.brKompanii;
        for(int i = 0; i < brKompanii; i++)
        {
            kompanii[i] = c.kompanii[i];
        }
    }

    ~Client()
    {
        delete [] kompanii;
    }

    double totalValue()
    {
        double vred = 0;
        for(int i = 0; i < brKompanii; i++)
        {
            vred += kompanii[i].value();
        }
        return vred;
    }

    Client &operator+=(const StockRecord &sr)
    {
        StockRecord *temp = new StockRecord[brKompanii + 1];
        for(int i = 0; i < brKompanii; i++)
        {
            temp[i] = kompanii[i];
        }
        delete [] kompanii;
        kompanii = temp;
        kompanii[brKompanii] = sr;
        brKompanii++;
        return *this;
    }

    friend ostream &operator<<(ostream &o, Client &c)
    {
        o << c.idSmetka << " " << c.totalValue() << endl;
        for(int i = 0; i < c.brKompanii; i++)
        {
            o << c.kompanii[i] ;
        }
        return o;
    }
};

int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}