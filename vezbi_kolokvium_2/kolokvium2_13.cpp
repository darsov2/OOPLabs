//
// Created by David Arsov on 11.5.2022.
//

#include<bits/stdc++.h>

using namespace std;

class Image
{
protected:
    char *imeDatoteka, *imeKorisnik;
    int visina, sirina;

public:
    Image(const char *id = "untitled", const char *ik = "unknown", int v = 800, int s = 800)
    {
        imeDatoteka = new char[strlen(id) + 1];
        strcpy(imeDatoteka, id);
        imeKorisnik = new char[strlen(ik) + 1];
        strcpy(imeKorisnik, ik);
        visina = v;
        sirina = s;
    }

    Image(const Image &img)
    {
        imeDatoteka = new char[strlen(img.imeDatoteka) + 1];
        imeKorisnik = new char[strlen(img.imeKorisnik) + 1];
        strcpy(imeDatoteka, img.imeDatoteka);
        strcpy(imeKorisnik, img.imeKorisnik);
        visina = img.visina;
        sirina = img.sirina;
    }

    virtual int fileSize() const
    {
        return visina * sirina * 3;
    }

    friend ostream &operator<<(ostream &o, Image &img)
    {
        return o << img.imeDatoteka << " " << img.imeKorisnik << " " << img.fileSize() << endl;
    }

    bool operator>(const Image &img)
    {
        return fileSize() > img.fileSize();
    }
};

class TransparentImage : public Image
{
private:
    bool transaprent;

public:
    TransparentImage(const char *id = "untitled", const char *ik = "unknown", int v = 800, int s = 800, bool t = true) : Image(id, ik, v, s)
    {
        transaprent = t;
    }

    TransparentImage(const TransparentImage &img) : Image(img)
    {
        transaprent = img.transaprent;
    }

    int fileSize() const
    {
        if(transaprent)
        {
            return visina * sirina * 4;
        }
        return sirina * visina + sirina * visina / 8;
    }
};

class Folder
{
private:
    char ime[256], imeKorisnik[51];
    Image *sliki[100];

public:
    Folder(const char *i = "", const char *k = "unknown", Image **s = 0)
    {
        strncpy(ime, i, 255);
        strncpy(imeKorisnik, k, 50);
        sliki[0] = NULL;
    }

    int folderSize()
    {
        double vkp = 0;
        for(int i = 0; sliki[i] != NULL && i < 100; i++)
        {
            vkp += sliki[i]->fileSize();
        }
        return vkp;
    }

    Image* getMaxFile()
    {
        int max = 0;
        for(int i = 0; sliki[i] != NULL && i < 100; i++)
        {
            if(sliki[i]->fileSize() > sliki[max]->fileSize())
            {
                max = i;
            }
        }
        return sliki[max];
    }

    Folder &operator+=(Image &img)
    {
        int i;
        for(i = 0; sliki[i] != NULL && i < 100; i++);
        sliki[i] = &img;
        sliki[i + 1] = NULL;
    }

    friend ostream &operator<<(ostream &o, Folder f)
    {
        o << f.ime << " " << f.imeKorisnik << endl << "--" << endl;
        for(int i = 0; f.sliki[i] != NULL && i < 100; i++)
        {
            o << *f.sliki[i];
        }
        o << "--" << endl << "Folder size: " << f.folderSize() << endl;
        return o;
    }

    Image** getSliki()
    {
        return sliki;
    }

    Image* operator[](int n)
    {
        if(sliki[n])
        {
            return sliki[n];
        }
        return NULL;
    }
};

Folder max_folder_size(Folder *f, int n)
{
    int max = 0;
    for(int i = 0; i < n; i++)
    {
        if(f[i].folderSize() > f[max].folderSize())
        {
            max = i;
        }
    }
    return f[max];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
