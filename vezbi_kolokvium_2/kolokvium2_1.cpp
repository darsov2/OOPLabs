//
// Created by David Arsov on 9.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Book
{
protected:
    char isbn[21], naslov[51], avtor[31];
    double cena;

public:
    Book(const char *i = "", const char *n = "", const char *a="", double c = 0)
    {
        strcpy(isbn, i);
        strcpy(naslov, n);
        strcpy(avtor, a);
        cena = c;
    }

    virtual double bookPrice() = 0;

    friend ostream &operator<<(ostream &o, Book &b)
    {
        return o << b.isbn << ": " << b.naslov << ", " << b.avtor << " " << b.bookPrice() << endl;
    }

    void setISBN(char *i)
    {
        strcpy(isbn, i);
    }

    bool operator>(Book &b2)
    {
        return bookPrice() > b2.bookPrice();
    }

};

class OnlineBook : public Book
{
private:
    char *url;
    int goleminaMB;

public:
    OnlineBook(const char *i = "", const char *n = "", const char *a = "", double c = 0, const char *u = "", int g = 0) : Book(i, n, a, c)
    {
        url = new char[strlen(u) + 1];
        strcpy(url, u);
        goleminaMB = g;
    }

    OnlineBook(const OnlineBook &ob)
    {
        strcpy(isbn, ob.isbn);
        strcpy(naslov, ob.naslov);
        strcpy(avtor, ob.avtor);
        url = new char[strlen(ob.url) + 1];
        strcpy(url, ob.url);
        goleminaMB = ob.goleminaMB;
        cena = ob.cena;
    }

    OnlineBook &operator=(const OnlineBook &ob)
    {
        if(this != &ob)
        {
            strcpy(isbn, ob.isbn);
            strcpy(naslov, ob.naslov);
            strcpy(avtor, ob.avtor);
            delete [] url;
            url = new char[strlen(ob.url) + 1];
            strcpy(url, ob.url);
            goleminaMB = ob.goleminaMB;
            cena = ob.cena;
        }
        return *this;
    }


    double bookPrice()
    {
        if(goleminaMB > 20)
        {
            return cena * 1.2;
        }
        return cena;
    }

};

class PrintBook : public Book
{
private:
    double masa;
    bool zaliha;

public:
    PrintBook(const char *i = "", const char *n = "", const char *a = "", double c = 0, double m = 0, bool z = 0) : Book(i, n, a, c)
    {
        masa = m;
        zaliha = z;
    }

    double bookPrice()
    {
        if(masa > 0.7)
        {
            return cena * 1.15;
        }
        return cena;
    }
};

void mostExpensiveBook(Book **books, int n)
{
    cout << "FINKI-Education" << endl;
    int brOnline = 0, brPrint = 0, maxCena = 0;
    for(int i = 0; i < n; i++)
    {
        OnlineBook *temp = dynamic_cast<OnlineBook*> (books[i]);
        if(temp != 0)
        {
            brOnline++;
        }
        else
        {
            brPrint++;
        }
        if(*books[i] > *books[maxCena])
        {
            maxCena = i;
        }
    }
    cout << "Total number of online books: " << brOnline << endl;
    cout << "Total number of print books: " << brPrint << endl;
    cout << "The most expensive book is:" << endl;
    cout << *books[maxCena] << endl;
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }
        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
