//
// Created by David Arsov on 1.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class NBAPlayer
{
private:
    char *ime, tim[40];
    double prosekPoeni, prosekAsist, prosekSkok;

public:
    NBAPlayer(char *i = "", char *t = "", double pp = 0, double pa = 0, double ps = 0)
    {
        ime = new char[strlen(i) + 1];
        strncpy(tim, t, 40);
        strcpy(ime, i);
        prosekPoeni = pp;
        prosekAsist = pa;
        prosekSkok = ps;
    }

    NBAPlayer(const NBAPlayer &nbp)
    {
        ime = new char[strlen(nbp.ime) + 1];
        strncpy(tim, nbp.tim, 40);
        strcpy(ime, nbp.ime);
        prosekPoeni = nbp.prosekPoeni;
        prosekAsist = nbp.prosekAsist;
        prosekSkok = nbp.prosekSkok;
    }

    NBAPlayer &operator=(const NBAPlayer &nbp)
    {
        if(this != &nbp)
        {
            delete [] ime;
            ime = new char[strlen(nbp.ime) + 1];
            strncpy(tim, nbp.tim, 40);
            strcpy(ime, nbp.ime);
            prosekPoeni = nbp.prosekPoeni;
            prosekAsist = nbp.prosekAsist;
            prosekSkok = nbp.prosekSkok;
        }
        return *this;
    }

    ~NBAPlayer()
    {
        delete [] ime;
    }

    double rating()
    {
        return prosekPoeni * 0.45 + prosekAsist * 0.3 + prosekSkok * 0.25;
    }

    void print()
    {
        cout << ime << " - " << tim << endl << "Points: " << prosekPoeni
        << endl << "Assists: " << prosekAsist << endl << "Rebounds: " << prosekSkok
        << endl << "Rating: " << rating() << endl;
    }
};

class AllStarPlayer : public NBAPlayer
{
private:
    double prosekPoeniAll, prosekAsistAll, prosekSkokAll;

public:
    AllStarPlayer(char *i = "", char *t = "", double pp = 0, double pa = 0, double ps = 0, double ppa = 0, double paa = 0, double psa = 0) : NBAPlayer(i, t, pp, pa, ps)
    {
        prosekPoeniAll = ppa;
        prosekAsistAll = paa;
        prosekSkokAll = psa;
    }

    AllStarPlayer(NBAPlayer nbp, double ppa = 0, double paa = 0, double psa = 0) : NBAPlayer(nbp)
    {
        prosekPoeniAll = ppa;
        prosekAsistAll = paa;
        prosekSkokAll = psa;
    }

    AllStarPlayer(const AllStarPlayer &asp) : NBAPlayer(asp)
    {
        prosekPoeniAll = asp.prosekPoeniAll;
        prosekAsistAll = asp.prosekAsistAll;
        prosekSkokAll = asp.prosekSkokAll;
    }

    AllStarPlayer &operator=(const AllStarPlayer &asp)
    {
        NBAPlayer::operator=(asp);
        prosekPoeniAll = asp.prosekPoeniAll;
        prosekAsistAll = asp.prosekAsistAll;
        prosekSkokAll = asp.prosekSkokAll;
    }

    double allStarRating()
    {
        return 0.3 * prosekPoeniAll + 0.4 * prosekAsistAll + 0.3 * prosekSkokAll;
    }

    double rating()
    {
        NBAPlayer::rating();
        allStarRating();
    }

    void print()
    {
        NBAPlayer::print();
        cout << "All Star Rating: " << allStarRating() << endl << "New Rating: " << (NBAPlayer::rating() + allStarRating()) / 2 << endl;
    }
};

int main() {

    char name[50];
    char team[40];
    double points;
    double assists;
    double rebounds;
    double allStarPoints;
    double allStarAssists;
    double allStarRebounds;

    NBAPlayer * players = new NBAPlayer[5];
    AllStarPlayer * asPlayers = new AllStarPlayer[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            players[i] = NBAPlayer(name,team,points,assists,rebounds);
            players[i].print();
        }
    }
    else if (n == 2) {

        for (int i=0; i < 5; ++i){
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            players[i] = NBAPlayer(name,team,points,assists,rebounds);
            asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
        }

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            players[i].print();

        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            asPlayers[i].print();

    }
    else if (n == 3) {

        for (int i=0; i < 5; ++i){
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                         allStarPoints,allStarAssists,allStarRebounds);
        }
        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            asPlayers[i].print();

    }

    delete [] players;
    delete [] asPlayers;
}
