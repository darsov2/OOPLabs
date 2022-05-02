//
// Created by David Arsov on 2.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Employee
{
protected:
    char ime[50];
    int godiniIskustvo, godini;
    Employee(char *i = " ", int g = 0, int god = 0)
    {
        strncpy(ime, i, 50);
        godiniIskustvo = god;
        godini = g;
    }

public:
    virtual double plata() = 0;

    virtual double bonus() const = 0;

    bool operator==(const Employee &emp)
    {
        if(bonus() == emp.bonus() && godini == emp.godini)
        {
            return true;
        }
        return false;
    }
    virtual int tip() = 0;
};

class SalaryEmployee : public Employee
{
private:
    int osnovnaPlata;

public:
    SalaryEmployee(char *i = " ", int g = 0, int god = 0, int op = 0) : Employee(i, g, god)
    {
        osnovnaPlata = op;
    }

    double plata()
    {
        return osnovnaPlata + bonus();
    }

    double bonus() const
    {
        return osnovnaPlata * godiniIskustvo / 100.;
    }

    int tip()
    {
        return 1;
    }
};

class HourlyEmployee : public Employee
{
private:
    int brCasovi, plataCas;

public:
    HourlyEmployee(char *i = " ", int g = 0, int god = 0, int bc = 0, int pc = 0) : Employee(i, g, god)
    {
        brCasovi = bc;
        plataCas = pc;
    }

    double plata()
    {
        return brCasovi * plataCas + bonus();
    }

    double bonus() const
    {
        if(brCasovi > 320)
        {
            return (brCasovi - 320) * plataCas / 2.;
        }
        else return 0;
    }

    int tip()
    {
        return 2;
    }
};

class Freelancer : public Employee
{
private:
    int brProekti;
    double *suma;

public:
    Freelancer(char *i = " ", int god = 0, int isk = 0, int pr = 0, double *s = 0) : Employee(i, god, isk)
    {
        brProekti = pr;
        suma = new double[brProekti];
        for(int j = 0; j < brProekti; j++)
        {
            suma[j] = s[j];
        }
    }

    double plata()
    {
        double p = 0;
        for(int i = 0; i < brProekti; i++)
        {
            p += suma[i];
        }
        return p + bonus();
    }

    double bonus() const
    {
        if(brProekti > 5)
        {
            return (brProekti - 5) * 1000;
        }
        else return 0;
    }

    int tip()
    {
        return 3;
    }
};

class Company
{
private:
    char ime[100];
    Employee **vrab;
    int brVrab;

public:
    Company(char *i=" ")
    {
        strncpy(ime, i, 100);
        brVrab = 0;
        vrab = new Employee*[0];
    }

    Company &operator+=(Employee *emp)
    {
        Employee **temp = new Employee*[brVrab + 1];
        for(int i = 0; i < brVrab; i++)
        {
            temp[i] = vrab[i];
        }
        delete [] vrab;
        vrab = temp;
        vrab[brVrab] = emp;
        brVrab++;
    }

    double vkupnaPlata()
    {
        double pl = 0;
        for(int i = 0; i < brVrab; i++)
        {
            pl += vrab[i]->plata();
        }
        return pl;
    }

    double filtriranaPlata(Employee *emp)
    {
        double pl = 0;
        for(int i = 0; i < brVrab; i++)
        {
            if(*emp == *vrab[i])
            {
                pl += vrab[i]->plata();
            }
        }
        return pl;
    }

    void pecatiRabotnici()
    {
        int sal = 0, hou = 0, fre = 0;
        for(int i = 0; i < brVrab; i++)
        {
            switch (vrab[i] -> tip())
            {
                case 1:
                    sal++;
                    break;
                case 2:
                    hou++;
                    break;
                case 3:
                    fre++;
                    break;
                default:
                    break;
            }
        }
        cout << "Vo kompanijata " << ime << " rabotat: " << endl << "Salary employees: " << sal << endl << "Hourly employees: " << hou << endl << "Freelancers: " << fre << endl;
    }
};

int main() {

    char name[50];
    cin >> name;
    Company c(name);

    int n;
    cin >> n;

    char employeeName[50];
    int age;
    int experience;
    int type;

    for (int i=0; i <n; ++i) {
        cin >> type;
        cin >> employeeName >> age >> experience;

        if (type == 1) {
            int basicSalary;
            cin >> basicSalary;
            c += new SalaryEmployee(employeeName, age, experience, basicSalary);
        }

        else if (type == 2) {
            int hoursWorked;
            int hourlyPay;
            cin >> hoursWorked >> hourlyPay;
            c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
        }

        else {
            int numProjects;
            cin >> numProjects;
            double projects[10];
            for (int i=0; i < numProjects; ++i) {
                cin >> projects[i];
            }
            c += new Freelancer(employeeName, age, experience, numProjects, projects);
        }
    }

    c.pecatiRabotnici();
    cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
    Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
    cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

    delete emp;
}