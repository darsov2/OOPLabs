//
// Created by David Arsov on 11.5.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class ExistingGame
{
public:
    ExistingGame()
    {

    }

    void poraka()
    {
        cout << "The game is already in the collection" << endl;
    }
};

class Game
{
protected:
    char ime[101];
    double cena;
    bool rasprodazba;

public:
    Game(const char *i = "", double c = 0, bool r = false)
    {
        strncpy(ime, i, 100);
        cena = c;
        rasprodazba = r;
    }

    friend ostream &operator<<(ostream &o, Game &sg)
    {
        return o << "Game: " << sg.ime << ", regular price: $" << sg.cena << (sg.rasprodazba ? ", bought on sale" : "") << endl;
    }

    friend istream &operator>>(istream &i, Game &sg)
    {
        i.get();
        i.getline(sg.ime, 50);
        return i >> sg.cena >> sg.rasprodazba;
    }

    bool operator==(Game &g)
    {
        return !strcmp(ime, g.ime);
    }

    virtual double getCena()
    {
        if(rasprodazba)
        {
            return cena * 0.3;
        }
        return cena;
    }

    bool getRasprodazba()
    {
        return rasprodazba;
    }
};

class SubscriptionGame : public Game
{
private:
    double pretplata;
    int mesec, godina;

public:
    SubscriptionGame(const char *i = "", double c = 0, bool r = false, double p = 0, int m = 0, int g = 0) : Game(i, c, r)
    {
        pretplata = p;
        mesec = m;
        godina = g;
    }

    friend ostream &operator<<(ostream &o, SubscriptionGame &sg)
    {
        return o << "Game: " << sg.ime << ", regular price: $" << sg.cena << (sg.rasprodazba ? ", bought on sale" : "") << ", monthly fee: $" << sg.pretplata << ", purchased: " << sg.mesec << "-" << sg.godina << endl;
    }

    friend istream &operator>>(istream &i, SubscriptionGame &sg)
    {
        i.get();
        i.getline(sg.ime, 100);
        return i >> sg.cena >> sg.rasprodazba >> sg.pretplata >> sg.mesec >> sg.godina;
    }

    int getMesec()
    {
        return mesec;
    }

    int getGodina()
    {
        return godina;
    }

    double getPretplata()
    {
        return pretplata;
    }

    double getCena()
    {
        return Game::getCena() + pretplata * (2018 * 360 + 5 * 30 - godina * 360 - mesec * 30) / 30;
    }
};

class User
{
private:
    Game **igri;
    char username[101];
    int brIgri;

public:
    User(const char *u = "", Game **ig = 0, int b = 0)
    {
        strncpy(username, u, 100);
        brIgri = b;
        igri = new Game*[brIgri];
        for(int i = 0; i < brIgri; i++)
        {
            igri[i] = ig[i];
        }
    }

    User &operator+=(Game &g)
    {
        for(int i = 0; i < brIgri; i++)
        {
            if(*igri[i] == g)
            {
                throw ExistingGame();
            }
        }

        Game **temp = new Game*[brIgri + 1];
        for(int i = 0; i < brIgri; i++)
        {
            temp[i] = igri[i];
        }
        delete [] igri;
        igri = temp;
        igri[brIgri] = &g;
        brIgri++;
        return *this;
    }

    double total_spent()
    {
        double vkp = 0;
        for(int i = 0; i < brIgri; i++)
        {
            vkp += igri[i]->getCena();
        }
        return vkp;
    }

    friend ostream &operator<<(ostream &o, User &u)
    {
        o << endl << "User: " << u.username << endl;
        for(int i = 0; i < u.brIgri; i++)
        {
            cout << "- ";
            SubscriptionGame *temp = dynamic_cast<SubscriptionGame*>(u.igri[i]);
            if(temp)
            {
                cout << *temp;
            }
            else
            {
                cout << *u.igri[i];
            }
        }
        o << endl;
        return  o;
    }

    char* get_name()
    {
        return username;
    }

    int get_games_number()
    {
        return brIgri;
    }

    Game* get_game(int n)
    {
        return igri[n];
    }
};

int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i){

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.poraka();
        }

        cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.poraka();
            }
        }

        cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            u+=(*g);
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}