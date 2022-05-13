//
// Created by David Arsov on 11.5.2022.
//

#include<bits/stdc++.h>

using namespace std;

class SMS
{
protected:
    double cena;
    char brPrati[14];

public:
    SMS(const char *tel = "", double c = 0)
    {
        strncpy(brPrati, tel, 13);
        cena = c;
    }

    virtual double SMS_cena() = 0;

    friend ostream &operator<<(ostream &o, SMS &s)
    {
        return o << "Tel: " << s.brPrati << " - cena: " << s.SMS_cena() << "den." << endl;
    }
};

class RegularSMS : public SMS
{
private:
    char *tekst;
    bool roaming;
    static double roamProc;

public:
    RegularSMS(const char *tel = "", double c = 0, const char *m = "", bool r = false) : SMS(tel, c)
    {
        tekst = new char[strlen(m) + 1];
        strcpy(tekst, m);
        roaming = r;
    }

    double SMS_cena()
    {
        double c = cena;
        if(roaming)
        {
            c *= roamProc + 1;
        }
        else
        {
            c *= 1.18;
        }
        c +=  (strlen(tekst) % 160 > 0 || (strlen(tekst) / 160) > 1 ? (strlen(tekst) / 160) * c : 0);
        return c;
    }

    static void set_rProcent(double d)
    {
        roamProc = d / 100;
    }
};

class SpecialSMS : public SMS
{
private:
    bool humanitarna;
    static double specProc;

public:
    SpecialSMS(const char *tel = "", double c = 0, bool r = false) : SMS(tel, c)
    {
        humanitarna = r;
    }

    double SMS_cena()
    {
        double c = cena;
        if(!humanitarna)
        {
            c *= specProc + 1;
            //c *= 1.18;
        }
        return c;

    }

    static void set_sProcent(double d)
    {
        specProc = d / 100;
    }
};

void vkupno_SMS(SMS **poraka, int n)
{
    int brReg = 0, brSpec = 0;
    double cenaReg = 0, cenaSpec = 0;
    for(int i = 0; i < n; i++)
    {
        RegularSMS *temp = dynamic_cast<RegularSMS*>(poraka[i]);
        if(temp)
        {
            brReg++;
            cenaReg += poraka[i]->SMS_cena();
        }
        else
        {
            brSpec++;
            cenaSpec += poraka[i]->SMS_cena();
        }
    }
    cout << "Vkupno ima " << brReg << " regularni SMS poraki i nivnata cena e: " << cenaReg << endl;
    cout << "Vkupno ima " << brSpec << " specijalni SMS poraki i nivnata cena e: " << cenaSpec << endl;
}

double RegularSMS::roamProc = 3;
double SpecialSMS::specProc = 1.5;

int main()
{
    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
