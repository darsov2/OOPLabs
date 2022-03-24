//
// Created by David Arsov on 23.3.2022.
//

#include <bits/stdc++.h>

using namespace std;

enum Extension
{
    pdf,
    txt,
    exe
};

class File
{
    private:
    char *ime, *sopstvenik;
    int gol;
    Extension ekst;

    public:
    File(char *i = "", char *sopst = "", int g = 0, Extension ex = (Extension)-1)
    {
        ime = new char[strlen(i) + 1];
        sopstvenik = new char[strlen(sopst) + 1];
        strcpy(ime, i);
        strcpy(sopstvenik, sopst);
        ekst = ex;
        gol = g;
    }

    File(const File &f1)
    {
        ime = new char[strlen(f1.ime) + 1];
        sopstvenik = new char[strlen(f1.sopstvenik) + 1];
        strcpy(ime, f1.ime);
        strcpy(sopstvenik, f1.sopstvenik);
        ekst = f1.ekst;
        gol = f1.gol;
    }

    ~File()
    {
        delete [] ime;
        delete [] sopstvenik;
    }

    File &operator=(const File &f1)
    {
        if(this != &f1)
        {
            delete [] ime;
            delete [] sopstvenik;
            ime = new char[strlen(f1.ime) + 1];
            sopstvenik = new char[strlen(f1.sopstvenik) + 1];
            strcpy(ime, f1.ime);
            strcpy(sopstvenik, f1.sopstvenik);
            ekst = f1.ekst;
            gol = f1.gol;
            return *this;
        }
    }

    void print()
    {
        char *ek[]={"pdf", "txt", "exe"};
        cout << "File name: " << ime << "." << ek[ekst] << endl;
        cout << "File owner: " << sopstvenik << endl;
        cout << "File size: " << gol << endl;
    }

    bool equals(const File &that)
    {
        if(!strcmp(ime, that.ime))
        {
            if(!strcmp(sopstvenik, that.sopstvenik))
            {
                if(ekst == that.ekst)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool equalsType(const File &that)
    {
        if(!strcmp(ime, that.ime))
        {
            if(ekst == that.ekst)
            {
                return true;
            }
        }
        return false;
    }
};

class Folder
{
    private:
    char *ime;
    int brDat;
    File *dat;

    public:
    Folder(const char *name)
    {
        ime = new char[strlen(name) + 1];
        strcpy(ime, name);
        brDat = 0;
        dat = new File[0];
    }

    ~Folder()
    {
        delete [] dat;
        delete [] ime;
    }

    void print()
    {
        cout << "Folder name: " << ime << endl;
        for(int i = 0; i < brDat; i++)
        {
            dat[i].print();
        }
    }

    void remove(const File &file)
    {
        for(int i = 0; i < brDat; i++)
        {
            if(dat[i].equals(file))
            {
                for(int j = i; j < brDat - 1; i++)
                {
                    dat[i] = dat[i + 1];
                }
                brDat--;
                i--;
            }
        }
    }

    void add(const File &file) {
        File *temp = new File[brDat + 1];
        for (int i = 0; i < brDat; i++)
        {
            temp[i] = dat[i];
        }
        delete [] dat;
        dat = temp;
        dat[brDat] = file;
        brDat++;
    }
};

#include<iostream>
#include<cstring>

using namespace std;

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS AND EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}