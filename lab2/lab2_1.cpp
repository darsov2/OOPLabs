//
// Created by David Arsov on 2.3.2022.
//

#include <iostream>
using namespace std;

class Agol
{
    private:

    int stepeni, minuti, sekundi;

    public:

    Agol()
    {

    }

    Agol (int stepeni, int minuti, int sekundi)
    {
        this->stepeni = stepeni;
        this->minuti = minuti;
        this->sekundi = sekundi;
    }

    void setStepeni (int stepeni)
    {
        this->stepeni = stepeni;
    }

    void setMinuti (int minuti)
    {
        this->minuti = minuti;
    }

    void setSekundi(int sekundi)
    {
        this->sekundi = sekundi;
    }

    int toSekundi ()
    {
        return sekundi + minuti * 60 + stepeni * 3600;
    }

    int getSekundi ()
    {
        return sekundi;
    }
};

bool proveri(int stepeni, int minuti, int sekundi)
{
    if(stepeni >= 0 && stepeni <= 360)
    {
        if(minuti >= 0 && minuti < 60)
        {
            if(sekundi >= 0 && sekundi < 60)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}


bool changeOfSeconds(Agol a, int sec)
{
    return a.getSekundi()!=sec;
}

int main()
{

    Agol a1;
    int deg, min, sec;
    cin >> deg >> min >> sec;

    if (proveri(deg, min, sec)) {

        a1.setStepeni(deg);
        a1.setMinuti(min);
        a1.setSekundi(sec);
        cout << a1.toSekundi();
        if (changeOfSeconds(a1,sec))
            cout << "Ne smeete da gi menuvate sekundite vo ramkite na klasata!" << endl;
    }
    else
    {
        cout << "Nevalidni vrednosti za agol";
    }

    return 0;
}
