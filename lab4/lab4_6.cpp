//
// Created by David Arsov on 23.3.2022.
//

#include <bits/stdc++.h>

using namespace std;

enum Tip
{
    LINUX,
    UNIX,
    WINDOWS
};
class OperativenSistem
{
    private:
    char *ime;
    float verzija, gol;
    Tip tipp;

    public:
    OperativenSistem(char *i = "", float v = 0, Tip t = (Tip)-1, float g = 0)
    {
        ime = new char[strlen(i) + 1];
        verzija = v;
        strcpy(ime, i);
        gol = g;
        tipp = t;
    }

    OperativenSistem(const OperativenSistem &os)
    {
        ime = new char[strlen(os.ime) + 1];
        verzija = os.verzija;
        strcpy(ime, os.ime);
        gol = os.gol;
        tipp = os.tipp;
    }

    ~OperativenSistem()
    {
        delete [] ime;
    }

    OperativenSistem& operator=(const OperativenSistem &os)
    {
        if(this != &os)
        {
            delete [] ime;
            ime = new char[strlen(os.ime) + 1];
            verzija = os.verzija;
            strcpy(ime, os.ime);
            gol = os.gol;
            tipp = os.tipp;
        }
        return *this;
    }

    void pecati()
    {
        cout << "Ime: " << ime << " Verzija: " << verzija << " Tip: " << tipp << " Golemina:" << gol << "GB" << endl;
    }

    bool ednakviSe(const OperativenSistem &os)
    {
        if(!strcmp(os.ime, ime) && os.gol == gol && os.verzija == verzija && os.tipp == tipp)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int sporediVerzija(const OperativenSistem &os)
    {
        if(os.verzija == verzija)
        {
            return 0;
        }
        else if(os.verzija > verzija)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }

    bool istaFamilija(const OperativenSistem &os)
    {
        if(!strcmp(os.ime, ime) && os.tipp == tipp)
        {
            return  true;
        }
        else
        {
            return false;
        }
    }
};


class Repozitorium
{
private:
    char ime[20];
    OperativenSistem *os;
    int brOs;

public:
    Repozitorium(const char *i)
    {
        strncpy(ime, i, 20);
        os = new OperativenSistem[0];
        brOs = 0;
    }

    ~Repozitorium()
    {
        delete [] os;
    }

    void pecatiOperativniSistemi()
    {
        cout << "Repozitorium: " << ime << endl;
        for(int i = 0; i < brOs; i++)
        {
            os[i].pecati();
        }
    }

    void izbrishi(const OperativenSistem &operativenSistem)
    {
        for(int i = 0; i < brOs; i++)
        {
            if(os[i].ednakviSe(operativenSistem))
            {
                for(int j = i; j < brOs - 1; j++)
                {
                    os[j] = os[j+1];
                }
                brOs--;
                i++;
            }
        }
    }

    void dodadi(const OperativenSistem &nov)
    {
        for(int i = 0; i < brOs; i++)
        {
            if(os[i].istaFamilija(nov) && os[i].sporediVerzija(nov) == -1)
            {
                os[i] = nov;
                return;
            }
        }

        OperativenSistem *temp = new OperativenSistem[brOs + 1];
        for(int i = 0; i < brOs; i++)
        {
            temp[i] = os[i];
        }
        delete [] os;
        os = temp;
        os[brOs] = nov;
        brOs++;
    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}