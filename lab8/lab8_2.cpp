//
// Created by David Arsov on 7.5.2022.
//
#include <bits/stdc++.h>

using namespace std;

class Igrachka
{
private:

public:
    Igrachka()
    {

    }
    virtual float getVolumen() = 0;
    virtual float getMasa() = 0;
    virtual float getPlostina() = 0;
};

class Forma {
protected:
    char boja[100];
    int gustina;
public:
    Forma(char *b = "", int g = 0)
    {
        strncpy(boja, b, 100);
        gustina = g;

    }
    // да се имплементираат потребните методи

};

class Topka : public Igrachka, public Forma
{
private:
    int radius;

public:
    Topka(char *b = "", int g = 0, int r = 0) : Forma(b, g)
    {
        radius = r;
    }

    float getVolumen()
    {
        return 4/3. * 3.14 * radius * radius * radius;
    }

    float getMasa()
    {
        return getVolumen() * gustina;
    }

    float getPlostina()
    {
        return 4 * 3.14 * radius * radius;
    }
};

class Kocka : public Igrachka, public Forma
{
private:
    int vis, sir, dlab;

public:
    Kocka (char *b = "", int g = 0, int v = 0, int s = 0, int d = 0) : Forma(b, g)
    {
        vis = v;
        sir = s;
        dlab = d;
    }

    float getVolumen()
    {
        return vis * sir * dlab;
    }

    float getMasa()
    {
        return getVolumen() * gustina;
    }

    float getPlostina()
    {
        return 2 * sir * vis + 2 * sir * dlab + 2 * dlab * vis;
    }
};

int main()
{
    int n;
    cin >> n;
    Igrachka **kupche = new Igrachka*[n];
    float vkMasa = 0;
    int maxVol = 0, minPlo = 0;
    for(int i = 0; i < n; i ++)
    {
        int m, g;
        char b[100];
        cin >> m >> b >> g;
        if(m == 1)
        {
            int r;
            cin >> r;
            kupche[i] = new Topka(b, g, r);
        }
        else if(m == 2)
        {
            int v, s, d;
            cin >> v >> s >> d;
            kupche[i] = new Kocka(b, g, v, s, d);
        }

        vkMasa += kupche[i]->getMasa();

        if(kupche[i]->getVolumen() > kupche[maxVol]->getVolumen())
        {
            maxVol = i;
        }

        if(kupche[i]->getPlostina() < kupche[minPlo]->getPlostina())
        {
            minPlo = i;
        }
    }
    int g, v, s, d;
    char b[100];
    cin >> b >> g >> v >> s >> d;
    Kocka kockaPetra(b, g, v, s, d);
    if(vkMasa > kockaPetra.getMasa())
    {
        cout << "DA" << endl;
    }
    else
    {
        cout << "NE" << endl;
    }

    cout << "Razlikata e: " << fabs(kockaPetra.getVolumen() - kupche[maxVol]->getVolumen()) << endl;
    cout << "Razlikata e: " << fabs(kockaPetra.getPlostina() - kupche[minPlo]->getPlostina()) << endl;

    return 0;
}