//
// Created by David Arsov on 9.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class InvalidPassword
{
private:
    char tekstPoraka[100];

public:
    InvalidPassword(char *p)
    {
        strncpy(tekstPoraka, p, 100);
    }

    void message()
    {
        cout << tekstPoraka << endl;
    }
};

class InvalidEmail
{
private:
    char tekstPoraka[100];

public:
    InvalidEmail(char *p)
    {
        strncpy(tekstPoraka, p, 100);
    }

    void message()
    {
        cout << tekstPoraka << endl;
    }
};

class MaximumSizeLimit
{
private:
    int br;

public:
    MaximumSizeLimit(int n)
    {
        br = n;
    }

    void message()
    {
        cout << "You can't add more than " << br << " users." << endl;
    }
};

class User
{
protected:
    char username[50], password[50], email[50];

public:
    User(char *u = "", char *p = "", char *e = "")
    {
        strncpy(username, u, 50);
        bool mali = false, golemi = false, cifri = false;
        for(int i = 0; i < strlen(p); i++)
        {
            if(!mali && islower(p[i]))
            {
                mali = true;
            }
            else if(!golemi && isupper(p[i]))
            {
                golemi = true;
            }
            else if(!cifri && isdigit(p[i]))
            {
                cifri = true;
            }
            else if(mali && golemi && cifri)
            {
                strncpy(password, p, 50);
                break;
            }
        }
        if(!(mali && golemi && cifri))
        {
            throw InvalidPassword("Password is too weak.");
        }
        int brMajmun = 0;
        for(int i = 0; i < strlen(e); i++)
        {
            if(e[i] == '@')
            {
                brMajmun++;
            }
        }
        if(brMajmun == 1)
        {
            strncpy(email, e, 50);
        }
        else
        {
            throw InvalidEmail("Mail is not valid.");
        }
    }

    virtual double popularity() = 0;
};

class FacebookUser : public User
{
private:
    int brPrijateli, brLajkovi, brKomentari;

public:
    FacebookUser(char *u = "", char *p = "", char *e = "", int pr = 0, int la = 0, int kom = 0) : User(u, p ,e)
    {
        brPrijateli = pr;
        brLajkovi = la;
        brKomentari = kom;
    }

    double popularity()
    {
        return brPrijateli + brLajkovi * 0.1 + brKomentari * 0.5;
    }
};

class TwitterUser : public User
{
private:
    int brSledaci, brTvitovi;

public:
    TwitterUser(char *u = "", char *p = "", char *e = "", int s = 0, int t = 0) : User(u, p ,e)
    {
        brSledaci = s;
        brTvitovi = t;
    }

    double popularity()
    {
        return brSledaci + brTvitovi * 0.5;
    }
};

class SocialNetwork
{
private:
    User **korisnici;
    int brKorisnici, maxKorisnici;

public:
    SocialNetwork()
    {
        korisnici = new User*[0];
        brKorisnici = 0;
        maxKorisnici = 5;
    }

    ~SocialNetwork()
    {
        delete [] korisnici;
    }

    SocialNetwork &operator+=(User *u)
    {
        if(brKorisnici + 1 <= maxKorisnici)
        {
            User **temp = new User*[brKorisnici + 1];
            for(int i = 0; i < brKorisnici; i++)
            {
                temp[i] = korisnici[i];
            }
            delete [] korisnici;
            korisnici = temp;
            temp[brKorisnici] = u;
            brKorisnici++;
        }
        else
        {
            throw MaximumSizeLimit(maxKorisnici);
        }
        return *this;
    }

    double avgPopularity()
    {
        double vkPop = 0;
        for(int i = 0; i < brKorisnici; i++)
        {
            vkPop += korisnici[i]->popularity();
        }
        return vkPop / brKorisnici;
    }

    void changeMaximumSize(int n)
    {
        maxKorisnici = n;
    }
};

int main() {

    SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i=0; i < n; ++i) {
        cin >> username;
        cin >> password;
        cin >> email;
        cin >> userType;
        if (userType == 1) {
            int friends;
            int likes;
            int comments;
            cin >> friends >> likes >> comments;

            try
            {
                User * u = new FacebookUser(username,password,email,friends,likes,comments);
                network += u;
            }
            catch(InvalidPassword &pass)
            {
                pass.message();
            }
            catch(InvalidEmail &mail)
            {
                mail.message();
            }
            catch(MaximumSizeLimit &size)
            {
                size.message();
            }

        }
        else {
            int followers;
            int tweets;
            cin >> followers >> tweets;
            try
            {
                User * u= new TwitterUser(username,password,email,followers,tweets);
                network += u;
            }
            catch(InvalidPassword &pass)
            {
                pass.message();
            }
            catch(InvalidEmail &mail)
            {
                mail.message();
            }
            catch(MaximumSizeLimit &size)
            {
                size.message();
            }

        }

    }
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin >> followers >> tweets;

    try
    {
        User * u= new TwitterUser(username,password,email,followers,tweets);
        network += u;
    }
    catch(InvalidPassword &pass)
    {
        pass.message();
    }
    catch(InvalidEmail &mail)
    {
        mail.message();
    }
    catch(MaximumSizeLimit &size)
    {
        size.message();
    }

    cout << network.avgPopularity();
}
