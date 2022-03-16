//
// Created by David Arsov on 16.3.2022.
//
#include <bits/stdc++.h>

using namespace std;

class Category
{
    private:
    char name[20];
    public:
    Category()
    {
        strncpy(name, "unnamed", 20);
    }

    Category(char * i)
    {
        strncpy(name, i, 20);
    }

    void print() {
        cout << "Category: " << name << endl;
    }
};

class NewsArticle
{
    private:
    Category kategorija;
    char title[30];

    public:
    NewsArticle()
    {
        strncpy(title, "untitled", 30);
    }

    NewsArticle(Category kat, char *nas = "untitled")
    {
        strncpy(title, nas, 20);
        kategorija = kat;
    }

    void print()
    {
        cout << "Article title: " << title << endl;
        kategorija.print();
    }
};

class FrontPage
{
    private:
    NewsArticle statija;
    float cena;
    int editionNumber;
    public:
    FrontPage()
    {
        cena = 0;
        editionNumber = 0;
    }

    FrontPage(NewsArticle stat, float c = 0, int ed = 0)
    {
        statija = stat;
        cena = c;
        editionNumber = ed;
    }

    void print()
    {
        cout << "Price: " << cena << ", " << "Edition number: " << editionNumber << endl;
        statija.print();
    }
};

int main() {
    char categoryName[20];
    char articleTitle[30];
    float price;
    int editionNumber;

    int testCase;
    cin >> testCase;


    if (testCase == 1) {
        int iter;
        cin >> iter;
        while (iter > 0) {
            cin >> categoryName;
            cin >> articleTitle;
            cin >> price;
            cin >> editionNumber;
            Category category(categoryName);
            NewsArticle article(category, articleTitle);
            FrontPage frontPage(article, price, editionNumber);
            frontPage.print();
            iter--;
        }
    }
    else if (testCase == 2) {
        cin >> categoryName;
        cin >> price;
        cin >> editionNumber;
        Category category(categoryName);
        NewsArticle article(category);
        FrontPage frontPage(article, price, editionNumber);
        frontPage.print();
    }// test case 3
    else if (testCase == 3) {
        cin >> categoryName;
        cin >> articleTitle;
        cin >> price;
        Category category(categoryName);
        NewsArticle article(category, articleTitle);
        FrontPage frontPage(article, price);
        frontPage.print();
    }
    else {
        FrontPage frontPage = FrontPage();
        frontPage.print();
    }
    return 0;
}