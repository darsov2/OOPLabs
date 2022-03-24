//
// Created by David Arsov on 23.3.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Avtomobil
{
    private:
    char boja[20], brend[20], model[20];

    public:
    Avtomobil(char *b = "", char *br = "", char *m = "")
    {
        strncpy(boja, b, 20);
        strncpy(brend, br, 20);
        strncpy(model, m, 20);
    }

    Avtomobil &operator=(const Avtomobil &a1)
    {
        if(this != &a1)
        {
            strncpy(boja, a1.boja, 20);
            strncpy(brend, a1.brend, 20);
            strncpy(model, a1.model, 20);
        }
    }

    char *getBoja()
    {
        return boja;
    }

    char *getBrend()
    {
        return brend;
    }

    char *getModel()
    {
        return model;
    }
};

class ParkingPlac
{
    private:
    char adresa[20], *id;
    int cena, zarabotka, brParkirani;
    Avtomobil *koli;

    public:
    ParkingPlac(char *a, char *i, int c)
    {
        strncpy(adresa, a, 20);
        id = new char[strlen(i) + 1];
        strcpy(id, i);
        cena = c;
        brParkirani = 0;
    }

    ParkingPlac()
    {
        strncpy(adresa, "", 20);
        id = new char[0];
        cena = 0;
        brParkirani = 0;
    }

    ParkingPlac(const ParkingPlac &pp)
    {
        strncpy(adresa, pp.adresa, 20);
        id = new char[strlen(pp.id + 1)];
        strcpy(id, pp.id);
        cena = pp.cena;
        brParkirani = pp.brParkirani;
        for(int i = 0; i < brParkirani; i++)
        {
            koli[i] = pp.koli[i];
        }
    }

    ParkingPlac &operator=(const ParkingPlac &pp)
    {
        strncpy(adresa, pp.adresa, 20);
        id = new char[strlen(pp.id + 1)];
        strcpy(id, pp.id);
        cena = pp.cena;
        brParkirani = pp.brParkirani;
        for(int i = 0; i < brParkirani; i++)
        {
            koli[i] = pp.koli[i];
        }
    }

    ~ParkingPlac()
    {
        delete [] id;
    }

    char* getId()
    {
        return id;
    }

    void pecati()
    {

        if(zarabotka != 0)
        {
            cout << id << " " << adresa << " - " << zarabotka << " denari" << endl;
        }
        else
        {
            cout << id << " " << adresa << endl;
        }
    }

    void platiCasovi(int casovi)
    {
        zarabotka += cena * casovi;
    }

    bool daliIstaAdresa(ParkingPlac p)
    {
        if(!strcmp(p.adresa, adresa))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void parkirajVozilo(Avtomobil novoVozilo)
    {
        Avtomobil *temp = new Avtomobil[brParkirani + 1];
        for(int i = 0; i < brParkirani; i++)
        {
            temp[i] = koli[i];
        }
        delete [] koli;
        koli = temp;
        koli[brParkirani] = novoVozilo;
        brParkirani++;
    }

    void pecatiParkiraniVozila()
    {
        cout << "Vo parkingot se parkirani slednite vozila: " << endl;
        for(int i = 0; i < brParkirani; i++)
        {
            cout << i + 1 << "." << koli[i].getBoja() << " " << koli[i].getBrend() << " " << koli[i].getModel() << endl;
        }
    }
};

int main(){

    ParkingPlac p[100];
    int n,m;
    char adresa[50],id[50];
    int brojcasovi,cenacas;
    cin>>n;
    if(n > 0){


        for (int i=0;i<n;i++){
            cin.get();
            cin.getline(adresa,50);
            cin>>id>>cenacas;

            ParkingPlac edna(adresa,id,cenacas);

            p[i]=edna;
        }

        //plakjanje
        cin>>m;
        for (int i=0;i<m;i++){

            cin>>id>>brojcasovi;

            int findId=false;
            for (int j=0;j<m;j++){
                if (strcmp(p[j].getId(),id)==0){
                    p[j].platiCasovi(brojcasovi);
                    findId=true;
                }
            }
            if (!findId)
                cout<<"Ne e platen parking. Greshen ID."<<endl;
        }

        cout<<"========="<<endl;
        ParkingPlac pCentar("Cvetan Dimov","C10",80);
        for (int i=0;i<n;i++)
            if (p[i].daliIstaAdresa(pCentar))
                p[i].pecati();
    } else {

        ParkingPlac najdobarPlac("Mars", "1337", 1);
        int brVozila;
        cin >> brVozila;
        for(int i = 0; i < brVozila; ++i){

            char boja[20];
            char brend[20];
            char model[20];

            cin >> boja >> brend >> model;
            Avtomobil novAvtomobil(boja, brend, model);
            najdobarPlac.parkirajVozilo(novAvtomobil);
        }
        if(brVozila != 0)
            najdobarPlac.pecatiParkiraniVozila();

    }
}