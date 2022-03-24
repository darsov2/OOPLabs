//
// Created by David Arsov on 23.3.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Pica
{
    private:
    char ime[15], *sostojki;
    int namaluvanje, cena;

    public:
    Pica(char i[] = "", int c = 0, char *s = "", int n = 0)
    {
        strncpy(ime, i, 15);
        sostojki = new char[strlen(s) + 1];
        strcpy(sostojki, s);
        cena = c;
        namaluvanje = n;
    }

    Pica(const Pica &p)
    {
        strncpy(ime, p.ime, 15);
        sostojki = new char[strlen(p.sostojki) + 1];
        strcpy(sostojki, p.sostojki);
        namaluvanje = p.namaluvanje;
        cena = p.cena;
    }

    ~Pica()
    {
        delete [] sostojki;
    }

    Pica& operator=(const Pica &p)
    {
        if(this != &p)
        {
            delete [] sostojki;
            strncpy(ime, p.ime, 15);
            sostojki = new char[strlen(p.sostojki) + 1];
            strcpy(sostojki, p.sostojki);
            namaluvanje = p.namaluvanje;
            cena = p.cena;
        }
        return *this;
    }

    void pecati()
    {
        cout << ime << " - " << sostojki << " " << cena << endl;
    }

    bool istiSe(Pica p)
    {
        if(!strcmp(p.sostojki, sostojki))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    char* getSostojki()
    {
        return sostojki;
    }

    int getNam()
    {
        return namaluvanje;
    }

    char* getIme()
    {
        return ime;
    }

    int getCena()
    {
        return cena;
    }
};

class Picerija
{
    private:
    char ime[15];
    Pica *pici;
    int brPici;

    public:
    Picerija(char i[] = "", Pica p[] = 0, int b = 0)
    {
        strncpy(ime, i, 15);
        pici = new Pica[b];
        brPici = b;
        for(int i = 0; i < brPici; i++)
        {
            pici[i] = p[i];
        }
    }

    Picerija(const Picerija &pic)
    {
        strncpy(ime, pic.ime, 15);
        pici = new Pica[pic.brPici];
        brPici = pic.brPici;
        for(int i = 0; i < brPici; i++)
        {
            pici[i] = pic.pici[i];
        }
    }

    Picerija& operator=(const Picerija &pic)
    {
        strncpy(ime, pic.ime, 15);
        pici = new Pica[pic.brPici];
        brPici = pic.brPici;
        for(int i = 0; i < brPici; i++)
        {
            pici[i] = pic.pici[i];
        }
    }

    void setIme(char *i)
    {
        strncpy(ime, i, 15);
    }

    char* getIme()
    {
        return ime;
    }

    ~Picerija()
    {
        delete [] pici;
    }

    void dodadi(Pica p)
    {
        bool ima = false;
        for(int i = 0; i < brPici; i++)
        {
            if(!strcmp(pici[i].getSostojki(), p.getSostojki()))
            {
                return;
            }
        }
        Pica *temp = new Pica[brPici + 1];
        for(int i = 0; i < brPici; i++)
        {
            temp[i] = pici[i];
        }
        delete [] pici;
        pici = temp;
        pici[brPici] = p;
        brPici++;
    }

    void piciNaPromocija()
    {
        for(int i = 0; i < brPici; i++)
        {
            if(pici[i].getNam() > 0)
            {
                cout << pici[i].getIme() << " - " << pici[i].getSostojki() << ", " << pici[i].getCena() << " " << pici[i].getCena() - (pici[i].getNam() / 100. * pici[i].getCena()) << endl;
            }
        }
    }
};

int main () {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for(int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp,100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki,100);
        int popust;
        cin >> popust;
        Pica p(imp,cena,sostojki,popust);
        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp,100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki,100);
    int popust;
    cin >> popust;
    Pica p(imp,cena,sostojki,popust);
    p2.dodadi(p);

    cout<<p1.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p1.piciNaPromocija();

    cout<<p2.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p2.piciNaPromocija();

    return 0;
}