//
// Created by David Arsov on 2.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Number
{
public:
    virtual double doubleValue() = 0;
    virtual int intValue() = 0;
    virtual void print() = 0;
};

bool operator==(Number &n, Number &m)
{
    return (n.doubleValue() == m.doubleValue() && n.intValue() == m.intValue());
}

class Integer : public Number
{
private:
    int n;

public:
    Integer(int x)
    {
        n = x;
    }

    double doubleValue()
    {
        return 0;
    }

    int intValue()
    {
        return n;
    }

    void print()
    {
        cout << "Integer: " << n << endl;
    }
};

class Double : public Number
{
private:
    double n;

public:
    Double(double x)
    {
        n = x;
    }

    double doubleValue()
    {
        return n - (int)n;
    }

    int intValue()
    {
        return (int)n;
    }

    void print()
    {
        cout << "Double: " << n << endl;
    }
};

class Numbers
{
private:
    Number **br;
    int brBroevi;

public:
    Numbers()
    {
        br = new Number*[0];
        brBroevi = 0;
    }

    Numbers &operator+=(Number *n)
    {
        Number **temp = new Number*[brBroevi + 1];
        for(int i = 0; i < brBroevi; i++)
        {
            if(*br[i] == *n)
            {
                delete [] temp;
                return *this;
            }
            temp[i] = br[i];
        }
        delete [] br;
        br = temp;
        br[brBroevi] = n;
        brBroevi++;
        return *this;
    }

    double sumOfAll()
    {
        double sum = 0;
        for(int i = 0; i < brBroevi; i++)
        {
            sum += br[i]->doubleValue() + br[i]->intValue();
        }
        return sum;
    }

    int countInt()
    {
        int sum = 0;
        for(int i = 0; i < brBroevi; i++)
        {
            if(br[i]->doubleValue() == 0)
            {
                sum++;
            }
        }
        return sum;
    }

    int sumInt()
    {
        int sum = 0;
        for(int i = 0; i < brBroevi; i++)
        {
            if(br[i]->doubleValue() == 0)
            {
                sum += br[i]->intValue();
            }
        }
        return sum;
    }

    int countDouble()
    {
        int sum = 0;
        for(int i = 0; i < brBroevi; i++)
        {
            if(br[i]->doubleValue() != 0)
            {
                sum++;
            }
        }
        return sum;
    }

    double sumDouble()
    {
        double sum = 0;
        for(int i = 0; i < brBroevi; i++)
        {
            if(br[i]->doubleValue() != 0)
            {
                sum += br[i]->intValue() + br[i]->doubleValue();
            }
        }
        return sum;
    }

    void statistics()
    {
        cout << "Count of numbers: " << brBroevi << endl;
        cout << "Sum of all numbers: " << sumOfAll() << endl;
        cout << "Count of integer numbers: " << countInt() << endl;
        cout << "Sum of integer numbers: " << sumInt() << endl;
        cout << "Count of double numbers: " << countDouble() << endl;
        cout << "Sum of double numbers: " << sumDouble() << endl;
    }

    void integersLessThan(Integer n)
    {
        int c = 0;
        for(int i = 0; i < brBroevi; i++)
        {
            if(br[i]->intValue() < n.intValue() && br[i]->doubleValue() == 0)
            {
                br[i]->print();
                c++;
            }
        }
        if(c == 0)
        {
            cout << "None" << endl;
        }
    }

    void doublesBiggerThan(Double n)
    {
        int c = 0;
        for(int i = 0; i < brBroevi; i++)
        {
            if(br[i]->intValue() + br[i]->doubleValue() > n.intValue() + n.doubleValue() && br[i]->doubleValue() != 0)
            {
                br[i]->print();
                c++;
            }
        }
        if(c == 0)
        {
            cout << "None" << endl;
        }
    }
};

int main() {

    int n;
    cin>>n;
    Numbers numbers;
    for (int i=0;i<n;i++){
        int type;
        double number;
        cin>>type>>number;
        if (type==0){//Integer object
            Integer * integer = new Integer((int) number);
            numbers+=integer;
        }
        else {
            Double * doublee = new Double(number);
            numbers+=doublee;
        }
    }

    int lessThan;
    double biggerThan;

    cin>>lessThan;
    cin>>biggerThan;

    cout<<"STATISTICS FOR THE NUMBERS\n";
    numbers.statistics();
    cout<<"INTEGER NUMBERS LESS THAN "<<lessThan<<endl;
    numbers.integersLessThan(Integer(lessThan));
    cout<<"DOUBLE NUMBERS BIGGER THAN "<<biggerThan<<endl;
    numbers.doublesBiggerThan(Double(biggerThan));

    return 0;
}