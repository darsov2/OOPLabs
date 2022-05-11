//
// Created by David Arsov on 11.5.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

enum Size
{
    small,
    big,
    family
};

class Pizza
{
protected:
    char ime[21], sostojki[101];
    double cena;

public:
    Pizza(const char *i = "", const char *s = "", double c = 0)
    {
        strncpy(ime, i, 51);
        strncpy(sostojki, s, 49);
        cena = c;
    }

    virtual double price() = 0;

    bool operator<(Pizza &p)
    {
        return price() < p.price();
    }
};

class FlatPizza : public Pizza
{
private:
    Size golemina;

public:
    FlatPizza(const char *i = "", const char *s = "", double c = 0, Size g = (Size)0) : Pizza(i, s, c)
    {
        golemina = g;
    }

    double price()
    {
        if(golemina == 0)
        {
            return cena * 1.1;
        }
        else if(golemina == 1)
        {
            return cena * 1.3;
        }
        else
        {
            return cena * 1.3;
        }
    }

    friend ostream &operator<<(ostream &o, FlatPizza &fp)
    {
        return o << fp.ime << ": " << fp.sostojki << ", " << (fp.golemina == 0 ? "small" : fp.golemina == 1 ? "big" : "family") << " - " << fp.price() << endl;
    }
};

class FoldedPizza : public Pizza
{
private:
    bool beloBrasno;

public:
    FoldedPizza(const char *i = "", const char *s = "", double c = 0, bool b = true) : Pizza(i, s, c)
    {
        beloBrasno = b;
    }

    double price()
    {
        if(beloBrasno)
        {
            return cena * 1.1;
        }
        return cena * 1.3;
    }

    friend ostream &operator<<(ostream &o, FoldedPizza &fp)
    {
       return o << fp.ime << ": " << fp.sostojki << ", " << (fp.beloBrasno ?  "wf" : "nwf") << " - " << fp.price() << endl;
    }
    
    void setWhiteFlour(bool f)
    {
        beloBrasno = f;
    }
};

void expensivePizza(Pizza **pici, int n)
{
    int najskapa = 0;
    for(int i = 0; i < n; i++)
    {
        if(pici[i]->price() > pici[najskapa]->price())
        {
            najskapa = i;
        }
    }
    FlatPizza *temp = dynamic_cast<FlatPizza*>(pici[najskapa]);
    if(temp != 0)
    {
        cout << *temp;
    }
    else
    {
        FoldedPizza *temp1 = dynamic_cast<FoldedPizza*>(pici[najskapa]);
        cout << *temp1;
    }
}

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
