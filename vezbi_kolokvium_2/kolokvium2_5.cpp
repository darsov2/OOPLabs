//
// Created by David Arsov on 11.5.2022.
//

#include<iostream>
#include<cstring>

#define MAX 100

using namespace std;

enum typeC
{
    standard,
    loyal,
    vip
};

class UserExistsException
{
public:
    void poraka()
    {
        cout << "The user already exists in the list!" << endl;
    }
};

class Customer
{
private:
    char ime[51], email[50];
    typeC vid;
    static int popust;
    static const int dopPopust = 20;
    int brProizvodi;

public:
    Customer(const char *i = "", const char *e = "", typeC v = (typeC)0, int n = 0)
    {
        strncpy(ime, i, 50);
        strncpy(email, e, 50);
        vid = v;
        brProizvodi = n;
    }

    ~Customer()
    {

    }

    friend ostream &operator<<(ostream &o, const Customer &c)
    {
        o << c.ime << endl << c.email << endl << c.brProizvodi << endl;
        if(c.vid == 0)
        {
            o << "standard" << " " << 0 << endl;
        }
        else if(c.vid == 1)
        {
            o << "loyal" << " " << c.popust << endl;
        }
        else
        {
            o << "vip" << " " << c.popust + c.dopPopust << endl;
        }
        return o;
    }

    char* getEmail()
    {
        return email;
    }

    void setDiscount1(int n)
    {
        popust = n;
    }

    void setTypeC(typeC t)
    {
        vid = t;
    }

    int getBrProizvodi()
    {
        return brProizvodi;
    }

    typeC getTypeC()
    {
        return vid;
    }
};

class FINKI_bookstore
{
private:
    Customer *kupuvaci;
    int brKupuvaci;

public:
    FINKI_bookstore(Customer *k = 0, int br = 0)
    {
        kupuvaci = new Customer[br];
        for(int i = 0; i < br; i++)
        {
            kupuvaci[i] = k[i];
        }
        brKupuvaci = br;
    }

    FINKI_bookstore(const FINKI_bookstore &bs)
    {
        kupuvaci = new Customer[bs.brKupuvaci];
        brKupuvaci = bs.brKupuvaci;
        for(int i = 0; i < brKupuvaci; i++)
        {
            kupuvaci[i] = bs.kupuvaci[i];
        }
    }

    ~FINKI_bookstore()
    {
        delete [] kupuvaci;
    }

    FINKI_bookstore &operator=(const FINKI_bookstore &bs)
    {
        if(this != &bs)
        {
            delete [] kupuvaci;
            kupuvaci = new Customer[bs.brKupuvaci];
            brKupuvaci = bs.brKupuvaci;
            for(int i = 0; i < brKupuvaci; i++)
            {
                kupuvaci[i] = bs.kupuvaci[i];
            }
        }
        return *this;
    }

    FINKI_bookstore &operator+=(Customer &c)
    {
        for(int i = 0; i < brKupuvaci; i++)
        {
            if(!strcmp(kupuvaci[i].getEmail(), c.getEmail()))
            {
                throw UserExistsException();
            }
        }

        Customer *temp = new Customer[brKupuvaci + 1];
        for(int i = 0; i < brKupuvaci; i++)
        {
            temp[i] = kupuvaci[i];
        }
        delete [] kupuvaci;
        kupuvaci = temp;
        kupuvaci[brKupuvaci] = c;
        brKupuvaci++;
        return *this;
    }

    void setCustomers(Customer *k, int br)
    {
        delete [] kupuvaci;
        kupuvaci = new Customer[br];
        for(int i = 0; i < br; i++)
        {
            kupuvaci[i] = k[i];
        }
        brKupuvaci = br;
    }

    void update()
    {
        for(int i = 0; i < brKupuvaci; i++)
        {
            if(kupuvaci[i].getBrProizvodi() >= 10 && kupuvaci[i].getTypeC() == loyal)
            {
                kupuvaci[i].setTypeC(vip);
            }
            else if(kupuvaci[i].getBrProizvodi() > 5 && kupuvaci[i].getTypeC() == standard)
            {
                kupuvaci[i].setTypeC(loyal);
            }
        }
    }

    friend ostream &operator<<(ostream &o, FINKI_bookstore &bs)
    {
        for(int i = 0; i < bs.brKupuvaci; i++)
        {
            o << bs.kupuvaci[i];
        }
        return o;
    }
};

int Customer::popust = 10;

int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer kl;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
            kl = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;

        try
        {
            fc += kl;
        }
        catch(UserExistsException &user)
        {
            user.poraka();
        }

        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
