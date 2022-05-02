//
// Created by David Arsov on 2.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Shape
{
protected:
    int strana;

public:
    virtual double plostina() = 0;

    virtual void pecati() = 0;

    virtual int getType() = 0;

    Shape(int a = 0)
    {
        strana = a;
    }
};

class Square : public Shape
{
public:
    Square(int a) : Shape(a)
    {

    }

    double plostina()
    {
        return strana * strana;
    }

    void pecati()
    {
        cout << "Kvadrat so plostina = " << plostina() << endl;
    }

    int getType()
    {
        return 1;
    }
};

class Circle : public Shape
{
public:
    Circle(int a) : Shape(a)
    {

    }

    double plostina()
    {
        return strana * strana * 3.14;
    }

    void pecati()
    {
        cout << "Krug so plostina = " << plostina() << endl;
    }

    int getType()
    {
        return 2;
    }
};

class Triangle : public Shape
{
public:
    Triangle(int a) : Shape(a)
    {

    }

    double plostina()
    {
        return (sqrt(3)/4) * strana * strana;
    }

    void pecati()
    {
        cout << "Triagolnik so plostina = " << plostina() << endl;
    }

    int getType()
    {
        return 3;
    }
};

void checkNumTypes(Shape **niza, int n)
{
    int kvad = 0, kr = 0, tri = 0;

    for(int i = 0; i < n; i++)
    {
        switch (niza[i]->getType())
        {
            case 1:
                kvad++;
                break;
            case 2:
                kr++;
                break;
            case 3:
                tri++;
                break;
            default:
                break;
        }
    }
    cout << "Broj na kvadrati vo nizata = " << kvad << endl;
    cout << "Broj na krugovi vo nizata = " << kr << endl;
    cout << "Broj na triagolnici vo nizata = " << tri << endl;
}

int main(){


    int n;
    cin >> n;

    Shape **niza;
    niza = new Shape*[n];

    int classType;
    int side;

    for(int i = 0; i < n; ++i)
    {
        cin >> classType;
        cin >> side;
        if(classType == 1)
        {
            niza[i] = new Square(side);
        }
        else if(classType == 2)
        {
            niza[i] = new Circle(side);
        }
        else if(classType == 3)
        {
            niza[i] = new Triangle(side);
        }
    }

    for(int i = 0; i < n; ++i)
    {
        niza[i]->pecati();
    }

    checkNumTypes(niza, n);
    return 0;
}