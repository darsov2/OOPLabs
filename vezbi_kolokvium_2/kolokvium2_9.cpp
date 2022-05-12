//
// Created by David Arsov on 11.5.2022.
//

#include<iostream>
#include <string.h>

using namespace std;

class Exception
{
public:
    void poraka()
    {
        cout << "Ne moze da se vnese dadeniot trud" << endl;
    }
};

class IndeksException
{
private:
    int indeks;

public:
    IndeksException(int i)
    {
        indeks = i;
    }

    void poraka()
    {
        cout << "Ne postoi PhD student so indeks " << indeks << endl;
    }
};

class Trud
{
private:
    char vid;
    int godinaIzdavanje;

public:
    Trud(const char v = '0', int g = 1900)
    {
        vid = v;
        godinaIzdavanje = g;
    }

    char getVid() const
    {
        return vid;
    }

    int getGodina() const
    {
        return godinaIzdavanje;
    }

    friend istream &operator>>(istream &i, Trud &t)
    {
        return i >> t.vid >> t.godinaIzdavanje;
    }
};

class Student
{
private:
    char ime[31];
    int indeks, godinaUpis, ocenki[50], brPolozeni;

public:
    Student(const char *i = "", int in = 0, int godU = 1900, int *o = 0, int bp = 0)
    {
        strncpy(ime, i, 30);
        godinaUpis = godU;
        indeks = in;
        brPolozeni = bp;
        for(int i = 0; i < brPolozeni; i++)
        {
            ocenki[i] = o[i];
        }
    }

    virtual double rang() const
    {
        double prosek = 0;
        for(int i = 0; i < brPolozeni; i++)
        {
            prosek += ocenki[i];
        }
        return prosek / brPolozeni;
    }

    friend ostream &operator<<(ostream &o, const Student &s)
    {
        return o << s.indeks << " " << s.ime << " " << s.godinaUpis << " " << s.rang() << endl;
    }

    int getGodinaUpis()
    {
        return godinaUpis;
    }

    int getIndeks()
    {
        return indeks;
    }
};

class PhDStudent : public Student
{
private:
    Trud *trudovi;
    int brTrudovi;
    static int bodSpisanie, bodKonf;

public:
    PhDStudent(const char *i = "", int in = 0, int godU = 1900, int *o = 0, int bp = 0, Trud *t = 0, int brt = 0) : Student(i, in, godU, o, bp)
    {
        //brTrudovi = brt;
        trudovi = new Trud[0];
        brTrudovi = 0;
        if(brt > 0)
        {
            for(int i = 0; i < brt; i++)
            {
                //trudovi[i] = t[i];
                try
                {
                    *this += t[i];
                }
                catch(Exception &e)
                {
                    e.poraka();
                }
            }
        }

    }

    PhDStudent(const PhDStudent &phd) : Student(phd)
    {
        brTrudovi = phd.brTrudovi;
        trudovi = new Trud[brTrudovi];
        for(int i = 0; i < phd.brTrudovi; i++)
        {
            trudovi[i] = phd.trudovi[i];
        }
    }

    double rang() const
    {
        double dodatok = 0;
        for(int i = 0; i < brTrudovi; i++)
        {
            if(tolower(trudovi[i].getVid()) == 'c')
            {
                dodatok += bodKonf;
            }
            else
            {
                dodatok += bodSpisanie;
            }
        }

        return Student::rang() + dodatok;
    }

    PhDStudent &operator+=(const Trud &t)
    {
        //cout << "===================" << Student::getGodinaUpis() << "=================";
        if(t.getGodina() >= this->getGodinaUpis())
        {
            Trud *temp = new Trud[brTrudovi + 1];
            for(int i = 0; i < brTrudovi; i++)
            {
                temp[i] = trudovi[i];
            }
            delete [] trudovi;
            trudovi = temp;
            temp[brTrudovi] = t;
            brTrudovi++;
            return *this;
        }
        throw Exception();
    }

    static void setSpisanie(int s)
    {
        bodSpisanie = s;
    }

    static void setKonf(int k)
    {
        bodKonf = k;
    }
};

PhDStudent* getStudentPok(Student **studenti, int n, int ind)
{
    for(int i = 0; i < n; i++)
    {
        if(studenti[i]->getIndeks() == ind)
        {
            PhDStudent *temp = dynamic_cast<PhDStudent*> (studenti[i]);
            if(temp)
            {
                return temp;
            }
        }
    }
    throw IndeksException(ind);
}


int PhDStudent::bodKonf = 1;
int PhDStudent::bodSpisanie = 3;

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        try
        {
            *(getStudentPok(niza, n, indeks)) += t;
        }
        catch(Exception &e)
        {
            e.poraka();
        }
        catch(IndeksException &ie)
        {
            ie.poraka();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        try
        {
            *(getStudentPok(niza, n, indeks)) += t;
        }
        catch(Exception &e)
        {
            e.poraka();
        }
        catch(IndeksException &ie)
        {
            ie.poraka();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        try
        {
            *(getStudentPok(niza, n, indeks)) += t;
        }
        catch(Exception &e)
        {
            e.poraka();
        }
        catch(IndeksException &ie)
        {
            ie.poraka();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setKonf(conf);
        PhDStudent::setSpisanie(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}