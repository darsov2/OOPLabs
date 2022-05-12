//
// Created by David Arsov on 11.5.2022.
//

#include<bits/stdc++.h>

using namespace std;

class Koncert
{
private:
    char naziv[21], lokacija[21];
    double cenaBilet;
    static double popust;

public:
    Koncert(const char *n = "", const char *l = "", double c = 0)
    {
        strncpy(naziv, n, 20);
        strncpy(lokacija, l, 20);
        cenaBilet = c;
    }

    virtual double cena() const
    {
        return cenaBilet - cenaBilet * popust;
    }

    char* getNaziv()
    {
        return naziv;
    }

    static double getSezonskiPopust()
    {
        return popust;
    }

    static double setSezonskiPopust(double p)
    {
        popust = p;
    }

    void pecati()
    {
        cout << naziv << " " << cena() << endl;
    }
};

class ElektronskiKoncert : public Koncert
{
private:
    char *dj;
    double vremetraenje;
    bool dnevna;

public:
    ElektronskiKoncert(const char *n = "", const char *l = "", double c = 0, const char *d = "", double v = 0, bool dn = false) : Koncert(n, l, c)
    {
        dj = new char[strlen(d) + 1];
        strcpy(dj, d);
        vremetraenje = v;
        dnevna = dn;
    }

    ElektronskiKoncert(const ElektronskiKoncert &ek) : Koncert(ek)
    {
        dj = new char[strlen(ek.dj) + 1];
        strcpy(dj, ek.dj);
        vremetraenje = ek.vremetraenje;
        dnevna = ek.dnevna;
    }

    double cena() const
    {
        double dodatok = 0;
        if(vremetraenje > 7)
        {
            dodatok += 360;
        }
        else if(vremetraenje > 5)
        {
            dodatok += 150;
        }

        if(dnevna)
        {
            dodatok -= 50;
        }
        else
        {
            dodatok += 100;
        }

        return Koncert::cena() + dodatok;
    }
};

bool elektronski(Koncert *k)
{
    ElektronskiKoncert *temp = dynamic_cast<ElektronskiKoncert*>(k);
    return temp;
}

void najskapKoncert(Koncert **koncerti, int n)
{
    int najskap = 0;
    int brEl = 0;
    for(int i = 0; i < n; i++)
    {
        if(elektronski(koncerti[i]))
        {
            brEl++;
        }
        if(koncerti[i]->cena() > koncerti[najskap]->cena())
        {
            najskap = i;
        }
    }
    cout << "Najskap koncert: ";
    koncerti[najskap]->pecati();
    cout << "Elektronski koncerti: " << brEl << " od vkupno " << n << endl;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektron)
{
    int ima = false;
    for(int i = 0; i < n; i++)
    {
        if(elektron && !elektronski(koncerti[i]))
        {
            continue;
        }
        if(!strcmp(koncerti[i]->getNaziv(), naziv))
        {
            koncerti[i]->pecati();
            ima = true;
        }
    }
    return ima;
}

double Koncert::popust = 0.2;

int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
