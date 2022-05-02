//
// Created by David Arsov on 2.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Secret
{
public:
    virtual double simpleEntropy() = 0;

    virtual int total() = 0;
};

class DigitSecret : public Secret
{
private:
    int niza[100];
    int br;

public:
    DigitSecret(int *n = 0, int num = 0)
    {
        for(int i = 0; i < num; i++)
        {
            niza[i] = n[i];
        }
        br = num;
    }

    double simpleEntropy()
    {
        int pojavuvanje[10] = {0}, unik = 0;
        for(int i = 0; i < br; i++)
        {
            pojavuvanje[niza[i]]++;
        }
        for(int i = 0; i < 10; i++)
        {
            if(pojavuvanje[i] == 1)
            {
                unik++;
            }
        }
        return (double)unik / br;
    }

    int total()
    {
        return br;
    }

    friend ostream &operator<<(ostream &o, DigitSecret &ds)
    {
        for(int i = 0; i < ds.br; i++)
        {
            o << ds.niza[i];
        }
        return o << " Simple entropy: " << ds.simpleEntropy() << " Total: " << ds.total() << endl;
    }
};

class CharSecret : public Secret
{
private:
    char niza[100];

public:
    CharSecret(char *n = "")
    {
        strncpy(niza, n, 100);
    }

    double simpleEntropy()
    {
        int pojavuvanje[26] = {0}, unik = 0, vk = 0;
        for(int i = 0; niza[i] != '\0'; i++)
        {
            pojavuvanje[niza[i] - 'a']++;
            vk++;
        }
        for(int i = 0; i < 26; i++)
        {
            if(pojavuvanje[i] == 1)
            {
                unik++;
            }
        }
        return (double)unik / vk;
    }

    int total()
    {
        int vk = 0;
        for(int i = 0; niza[i] != '\0'; i++)
        {
            vk++;
        }
        return vk;
    }

    friend ostream &operator<<(ostream &o, CharSecret &ds)
    {
        return o << ds.niza << " Simple entropy: " << ds.simpleEntropy() << " Total: " << ds.total() << endl;
    }
};

bool operator==(Secret &s1, Secret &s2)
{
    return s1.simpleEntropy() == s2.simpleEntropy() && s1.total() == s2.total();
}

bool operator!=(Secret &s1, Secret &s2)
{
    return !(s1 == s2);
}

void process(Secret **secrets, int n)
{
    int maxEnt = 0;

    for(int i = 1; i < n; i++)
    {
        if(secrets[i]->simpleEntropy() > secrets[maxEnt]->simpleEntropy())
        {
            maxEnt = i;
        }
    }

    DigitSecret *d = dynamic_cast<DigitSecret*>(secrets[maxEnt]);
    if(d != 0)
    {
        cout << *d;
    }
    else
    {
        CharSecret *c = dynamic_cast<CharSecret*>(secrets[maxEnt]);
        cout << *c;
    }
}

void printAll(Secret **secrets, int n)
{
    for(int i = 0; i < n; i++)
    {
        DigitSecret *d = dynamic_cast<DigitSecret*>(secrets[i]);
        if(d != 0)
        {
            cout << *d;
        }
        else
        {
            CharSecret *c = dynamic_cast<CharSecret*>(secrets[i]);
            cout << *c;
        }
    }
}

int main() {
    int n;
    cin >> n;
    if(n == 0) {
        cout << "Constructors" << endl;
        int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << "OK" << endl;
    } else if(n == 1) {
        cout << "operator <<" << endl;
        int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << ds;
        cout << cs << endl;
    }  else if(n == 2) {
        cout << "== and !=" << endl;
        int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        CharSecret css("abcabc");
        cout << (ds == cs) << endl;
        cout << (cs != ds) << endl;
        cout << (cs == css) << endl;
        cout << (cs != css) << endl;
    } else if(n == 3) {
        cout << "Secret processor" << endl;
        int numbers1 [] = {1,2,3,4,5,6,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
        int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
        int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        process(s,6);
        delete [] s;
    }
    else if (n==4){
        cout << "Print all secrets" << endl;
        int numbers1 [] = {1,2,3,4,5,5,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
        int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
        int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        printAll(s,6);
        delete [] s;
    }

    return 0;
}