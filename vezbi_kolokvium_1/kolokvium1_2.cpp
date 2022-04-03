//
// Created by David Arsov on 23.3.2022.
//

#include <bits/stdc++.h>

using namespace std;

class List
{
private:
    int *brVoLista, brElementi;

public:
    List()
    {
        brVoLista = new int[0];
        brElementi = 0;
    }
    List(int *br, int n = 0)
    {
        brVoLista = new int[n];
        for(int i = 0; i < n; i++)
        {
            brVoLista[i] = br[i];
        }
        brElementi = n;
    }

    List(const List &l1)
    {
        brVoLista = new int[l1.brElementi];
        brElementi = l1.brElementi;
        for(int i = 0; i < brElementi; i++)
        {
            brVoLista[i] = l1.brVoLista[i];
        }
    }

    ~List()
    {
        delete [] brVoLista;
    }

    List &operator=(List &l1)
    {
        if(this != &l1)
        {
            delete [] brVoLista;
            brVoLista = new int[l1.brElementi];
            brElementi = l1.brElementi;
            for(int i = 0; i < brElementi; i++)
            {
                brVoLista[i] = l1.brVoLista[i];
            }
        }
        return *this;
    }

    void pecati()
    {
        cout << brElementi << ": ";
        for(int i = 0; i < brElementi; i++)
        {
            cout << brVoLista[i] << " ";
        }
        cout << "sum: " << sum() << " average: " << average() << endl;
    }

    int sum()
    {
        int sum = 0;
        for(int i = 0; i < brElementi; i++)
        {
            sum += brVoLista[i];
        }
        return sum;
    }

    double average()
    {
        return sum() / (double) brElementi;
    }

    int getBrElementi()
    {
        return brElementi;
    }
};

class ListContainer
{
private:
    List *lista;
    int brElementi, brObidi;

public:
    ListContainer()
    {
        lista = new List[0];
        brObidi = 0;
        brElementi = 0;
    }

    ListContainer(ListContainer &lc1)
    {
        lista = new List[lc1.brElementi];
        lista = lc1.lista;
        brObidi = lc1.brObidi;
    }

    ~ListContainer()
    {
        delete [] lista;
    }

    ListContainer &operator=(ListContainer &lc1)
    {
        if(this != &lc1)
        {
            delete [] lista;
            lista = new List[lc1.brElementi];
            for(int i = 0; i < lc1.brElementi; i++)
            {
                lista[i] = lc1.lista[i];
            }
            brElementi = lc1.brElementi;
            brObidi = lc1.brObidi;
        }
        return *this;
    }

    void print()
    {
        if(brElementi > 0)
        {
            for(int i = 0; i < brElementi; i++)
            {
                cout << "List number: " << i + 1;
                cout << " List info: ";
                lista[i].pecati();
            }
            cout << "Sum: " << sum() << " Average: " << average() << endl;
            cout << "Successful attempts: " << brElementi << " Failed attempts: " << brObidi - brElementi << endl;
        }
        else
        {
            cout << "The list is empty" << endl;
        }
    }

    int sum()
    {
        int globSum = 0;
        for(int i = 0; i < brElementi; i++)
        {
            globSum += lista[i].sum();
        }
        return globSum;
    }

    double average()
    {
        int globElementi = 0;
        for(int i = 0; i < brElementi; i++)
        {
            globElementi += lista[i].getBrElementi();
        }
        return sum() / (double) globElementi;
    }

    void addNewList(List l)
    {
        for(int i = 0; i < brElementi; i++)
        {
            if(l.sum() == lista[i].sum())
            {
                brObidi++;
                return;
            }
        }
        List *temp = new List[brElementi + 1];
        for(int i = 0; i < brElementi; i++)
        {
            temp[i] = lista[i];
        }
        delete [] lista;
        lista = temp;
        lista[brElementi] = l;
        brElementi++;
        brObidi++;
    }
};

int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}