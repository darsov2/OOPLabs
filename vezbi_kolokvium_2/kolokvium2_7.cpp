//
// Created by David Arsov on 11.5.2022.
//

#include<iostream>
#include<string.h>
using namespace std;

class OutOfBoundException
{
public:
    void poraka()
    {
        cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto" << endl;
    }
};

class Karticka
{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;

public:
    Karticka(char* smetka,int pin){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }

    ~Karticka()
    {

    }

    virtual int tezinaProbivanje() const
    {
        int brCifri = 0;
        int pPin = pin;
        for(int i = 0; pPin > 0; pPin /= 10)
        {
            brCifri++;
        }
        return brCifri;
    }

    friend ostream &operator<<(ostream &o, const Karticka &k)
    {
        return o << k.smetka << ": " << k.tezinaProbivanje() << endl;
    }

    bool getDopolnitelenPin() const
    {
        return povekjePin;
    }

    char* getSmetka()
    {
        return smetka;
    }
};

class SpecijalnaKarticka : public Karticka
{
private:
    int *pinovi, brPinovi;
    static const int p = 4;

public:
    SpecijalnaKarticka(char *smetka, int pin) : Karticka(smetka, pin)
    {
        povekjePin = true;
        pinovi = new int[0];
        brPinovi = 0;
    }

    SpecijalnaKarticka(const SpecijalnaKarticka &sk) : Karticka(sk)
    {
        povekjePin = true;
        brPinovi = sk.brPinovi;
        pinovi = new int[sk.brPinovi];
        for(int i = 0; i < brPinovi; i++)
        {
            pinovi[i] = sk.pinovi[i];
        }
    }

    SpecijalnaKarticka &operator=(const SpecijalnaKarticka &sk)
    {
        if(this == &sk) return *this;
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
        povekjePin = true;
        brPinovi = sk.brPinovi;
        pinovi = new int[sk.brPinovi];
        for(int i = 0; i < brPinovi; i++)
        {
            pinovi[i] = sk.pinovi[i];
        }
        return *this;
    }

    ~SpecijalnaKarticka()
    {
        delete [] pinovi;
    }

    int tezinaProbivanje() const
    {
        return Karticka::tezinaProbivanje() + brPinovi;
    }

    SpecijalnaKarticka &operator+=(int pi)
    {
        if(brPinovi + 1 <= p)
        {
            int *temp = new int[brPinovi + 1];
            for(int i = 0; i < brPinovi; i++)
            {
                temp[i] = pinovi[i];
            }
            delete [] pinovi;
            pinovi = temp;
            pinovi[brPinovi] = pi;
            brPinovi++;
        }
        else
        {
            throw OutOfBoundException();
        }
    }
};

class Banka
{
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;

public:
    Banka(char *naziv, Karticka** karticki,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }
    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }

    static void setLIMIT(int l)
    {
        LIMIT = l;
    }

    void pecatiKarticki()
    {
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite:" << endl;
        for(int i = 0; i < broj; i++)
        {
            if(karticki[i]->tezinaProbivanje() <= LIMIT)
            {
                SpecijalnaKarticka *temp = dynamic_cast<SpecijalnaKarticka*> (karticki[i]);
                if(temp)
                {
                    cout << *temp;
                }
                else
                {
                    cout << *karticki[i];
                }
            }
        }
    }

    void dodadiDopolnitelenPin(char *s, int np)
    {
        for(int i = 0; i < broj; i++)
        {
            if(!strcmp(karticki[i]->getSmetka(), s))
            {
                if(karticki[i]->getDopolnitelenPin())
                {
                    SpecijalnaKarticka *temp = dynamic_cast<SpecijalnaKarticka*> (karticki[i]);
                    if(temp)
                    {
                        *temp += np;
                    }
                }
            }
        }
    }
};

int Banka::LIMIT = 7;

int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;

        komercijalna.dodadiDopolnitelenPin(smetka,pin);

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
