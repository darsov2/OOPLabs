//
// Created by David Arsov on 1.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class PlDrustvo
{
private:
    char *ime;
    int brTuri, brClenovi;

public:
    PlDrustvo(char *i = "", int bt = 0, int bc = 0)
    {
        ime = new char[strlen(i) + 1];
        brTuri = bt;
        brClenovi = bc;
        strcpy(ime, i);
    }

    PlDrustvo(const PlDrustvo &pd)
    {
        ime = new char[strlen(pd.ime) + 1];
        brTuri = pd.brTuri;
        brClenovi = pd.brClenovi;
        strcpy(ime, pd.ime);
    }

    PlDrustvo &operator=(const PlDrustvo &pd)
    {
        if(this != &pd)
        {
            delete [] ime;
            ime = new char[strlen(pd.ime) + 1];
            brTuri = pd.brTuri;
            brClenovi = pd.brClenovi;
            strcpy(ime, pd.ime);
        }
        return *this;
    }

    PlDrustvo operator+(const PlDrustvo &pd)
    {
        return PlDrustvo(brClenovi > pd.brClenovi ? ime : pd.ime, brClenovi > pd.brClenovi ? brTuri : pd.brTuri, brClenovi + pd.brClenovi);
    }

    bool operator>(const PlDrustvo &pd)
    {
        if(brClenovi > pd.brClenovi)
        {
            return  true;
        }
        else return false;
    }

    bool operator<(const PlDrustvo &pd)
    {
        return !(*this > pd);
    }

    friend ostream &operator<<(ostream &o, const PlDrustvo &pd)
    {
        return o << "Ime: " << pd.ime << " Turi: " << pd.brTuri << " Clenovi: " << pd.brClenovi << endl;
    }

    int getClenovi()
    {
        return brClenovi;
    }
};

void najmnoguClenovi(PlDrustvo *pd, int n)
{
    int maks = 0;
    for(int i = 0; i < n; i++)
    {
        if(pd[i].getClenovi() > pd[maks].getClenovi())
        {
            maks = i;
        }
    }
    cout << "Najmnogu clenovi ima planinarskoto drustvo: " << pd[maks];
}

int main()
{
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i=0;i<3;i++)
    {
        char ime[100];
        int brTuri;
        int brClenovi;
        cin>>ime;
        cin>>brTuri;
        cin>>brClenovi;
        PlDrustvo p(ime,brTuri,brClenovi);
        drustva[i] = p;

    }

    pl = drustva[0] + drustva[1];
    cout<<pl;

    najmnoguClenovi(drustva, 3);

    return 0;
}