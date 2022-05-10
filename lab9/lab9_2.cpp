//
// Created by David Arsov on 9.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class ArithmeticException
{
public:
    void message()
    {
        cout << "Division by zero is not allowed" << endl;
    }
};

class NumbersNotDivisableException
{
private:
    int n;

public:
    NumbersNotDivisableException(int b)
    {
        n = b;
    }

    void message()
    {
        cout << "Division by " << n << " is not supported" << endl;
    }
};

class ArrayFullException
{
public:
    void message()
    {
        cout << "The array is full. Increase the capacity" << endl;
    }
};

class IndexOutOfBoundsException
{
private:
    int n;

public:
    IndexOutOfBoundsException(int b)
    {
        n = b;
    }

    void message()
    {
        cout << "Index " << n << " is out of bounds" << endl;
    }
};

class NumberIsNotPositiveException
{
private:
    int n;

public:
    NumberIsNotPositiveException(int b)
    {
        n = b;
    }

    void message()
    {
        cout << "Number " << n << " is not positive integer" << endl;
    }
};

class PositiveIntegers
{
private:
    int *pozitivni;
    int brElementi;
    int kapacitet;

public:
    PositiveIntegers(int c = 0)
    {
        pozitivni = new int[0];
        brElementi = 0;
        kapacitet = c;
    }

    ~PositiveIntegers()
    {
        delete [] pozitivni;
    }

    void increaseCapacity (int c)
    {
        kapacitet += c;
    }

    PositiveIntegers (const PositiveIntegers &pi)
    {
        pozitivni = new int[pi.brElementi];
        brElementi = pi.brElementi;
        kapacitet = pi.kapacitet;
        for(int i = 0; i < brElementi; i++)
        {
            pozitivni[i] = pi.pozitivni[i];
        }
    }

    PositiveIntegers &operator=(const PositiveIntegers &pi)
    {
        if(this != &pi)
        {
            delete [] pozitivni;
            pozitivni = new int[pi.brElementi];
            brElementi = pi.brElementi;
            kapacitet = pi.kapacitet;
            for(int i = 0; i < brElementi; i++)
            {
                pozitivni[i] = pi.pozitivni[i];
            }
        }
        return *this;
    }

    PositiveIntegers &operator+=(int n)
    {
        if(brElementi + 1 <= kapacitet)
        {
            if(n > 0)
            {
                int *temp = new int[brElementi + 1];
                for(int i = 0; i < brElementi; i++)
                {
                    temp[i] = pozitivni[i];
                }
                delete [] pozitivni;
                pozitivni = temp;
                pozitivni[brElementi] = n;
                brElementi++;
            }
            else
            {
                throw NumberIsNotPositiveException(n);
            }
        }
        else
        {
            throw ArrayFullException();
        }
        return *this;
    }

    PositiveIntegers operator*(int n)
    {
        PositiveIntegers temp = *this;
        for(int i = 0; i < brElementi; i++)
        {
            temp.pozitivni[i] *= n;
        }
        return temp;
    }

    PositiveIntegers operator/(int n)
    {
        if(n != 0)
        {
            PositiveIntegers temp = *this;
            for(int i = 0; i < brElementi; i++)
            {
                if(pozitivni[i] % n != 0)
                {
                    throw NumbersNotDivisableException(n);
                }
                else
                {
                    temp.pozitivni[i] /= n;
                }
            }
            return temp;
        }
        else
        {
            throw ArithmeticException();
        }
    }

    int &operator[](int n)
    {
        if(n < 0 || n >= brElementi)
        {
            throw IndexOutOfBoundsException(n);
        }
        else
        {
            return pozitivni[n];
        }
    }

    void print()
    {
        cout << "Size: " << brElementi << " Capacity: " << kapacitet << " Numbers: ";
        for(int i = 0; i < brElementi; i++)
        {
            cout << pozitivni[i] << " ";
        }
        cout << endl;
    }
};

int main() {

    int n,capacity;
    cin >> n >> capacity;
    PositiveIntegers pi (capacity);
    for (int i=0;i<n;i++){
        int number;
        cin>>number;
        try
        {
            pi+=number;
        }
        catch (ArrayFullException &polno)
        {
            polno.message();
        }
        catch (NumberIsNotPositiveException &nepoz)
        {
            nepoz.message();
        }

    }
    cout<<"===FIRST ATTEMPT TO ADD NUMBERS==="<<endl;
    pi.print();
    int incCapacity;
    cin>>incCapacity;
    pi.increaseCapacity(incCapacity);
    cout<<"===INCREASING CAPACITY==="<<endl;
    pi.print();

    int n1;
    cin>>n1;
    for (int i=0;i<n1;i++){
        int number;
        cin>>number;
        try
        {
            pi+=number;
        }
        catch(ArrayFullException &polno)
        {
            polno.message();
        }
        catch(NumberIsNotPositiveException &nepoz)
        {
            nepoz.message();
        }
    }
    cout<<"===SECOND ATTEMPT TO ADD NUMBERS==="<<endl;

    pi.print();
    PositiveIntegers pi1;

    cout<<"===TESTING DIVISION==="<<endl;

    try
    {
        pi1 = pi / 0;
        pi1.print();
    }
    catch(NumbersNotDivisableException &nedeli)
    {
        nedeli.message();
    }
    catch(ArithmeticException &arit)
    {
        arit.message();
    }

    try
    {
        pi1 = pi / 1;
        pi1.print();
    }
    catch(NumbersNotDivisableException &nedeli)
    {
        nedeli.message();
    }
    catch(ArithmeticException &arit)
    {
        arit.message();
    }

    try
    {
        pi1 = pi / 2;
        pi1.print();
    }
    catch(NumbersNotDivisableException &nedeli)
    {
        nedeli.message();
    }
    catch(ArithmeticException &arit)
    {
        arit.message();
    }

    cout<<"===TESTING MULTIPLICATION==="<<endl;
    pi1 = pi*3;
    pi1.print();


    cout<<"===TESTING [] ==="<<endl;
    try
    {
        cout<<"PositiveIntegers[-1] = "<<pi[-1]<<endl;
    }
    catch(IndexOutOfBoundsException &indeks)
    {
        indeks.message();
    }

    try
    {
        cout<<"PositiveIntegers[2] = "<<pi[2]<<endl;
    }
    catch(IndexOutOfBoundsException &indeks)
    {
        indeks.message();
    }

    try
    {
        cout<<"PositiveIntegers[3] = "<<pi[3]<<endl;
    }
    catch(IndexOutOfBoundsException &indeks)
    {
        indeks.message();
    }

    try
    {
        cout<<"PositiveIntegers[12] = "<<pi[12]<<endl;
    }
    catch(IndexOutOfBoundsException &indeks)
    {
        indeks.message();
    }

    return 0;
}