//
// Created by David Arsov on 2.3.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Krug
{
private:
    float radius;
    const float pi = 3.14;

public:
    Krug()
    {

    }

    Krug(float radius)
    {
        this->radius = radius;
    }

    float plostina()
    {
        return radius * radius * pi;
    }

    float perimetar()
    {
        return 2 * radius * pi;
    }

    int ednakvi()
    {
       return plostina() == perimetar();
    }
};

int main() {
    float r;
    cin >> r;
    Krug k(r);
    cout << k.perimetar() << endl;
    cout << k.plostina() << endl;
    cout << k.ednakvi() <<endl;
    Krug k1;
    return 0;
}