//
// Created by David Arsov on 1.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Matrica
{
private:
    float a[10][10];
    int m;

public:
    Matrica operator+(int x)
    {
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < m; j++)
            {
                a[i][j] += x;
            }
        }
        return *this;
    }

    Matrica operator-(const Matrica &mm)
    {
        Matrica b;
        b.m = m;
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < m; j++)
            {
                b.a[i][j] = a[i][j] - mm.a[i][j];
            }
        }
        return b;
    }

    Matrica operator*(const Matrica &mm)
    {
        Matrica b;
        b.m = m;

        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < m; j++)
            {
                b.a[i][j] = 0;
                for (int k = 0; k < m; k++)
                {
                    b.a[i][j] += a[i][k] * mm.a[k][j];
                }
            }
        }
        return b;
    }

    friend ostream &operator<<(ostream &o, const Matrica &mm)
    {
        for(int i = 0; i < mm.m; i++)
        {
            for(int j = 0; j < mm.m; j++)
            {
                o << mm.a[i][j] << " ";
            }
            o << endl;
        }
        return o;
    }

    friend istream &operator>>(istream &ii, Matrica &mm)
    {
        ii >> mm.m >> mm.m;
        for(int i = 0; i < mm.m; i++)
        {
            for(int j = 0; j < mm.m; j++)
            {
                ii >> mm.a[i][j];
            }
        }
        return ii;
    }
};

int main()
{
    Matrica A,B,C;
    cin>>A>>B>>C;
    Matrica D=B*C;
    Matrica R=A-D+2;
    cout<<R;
}