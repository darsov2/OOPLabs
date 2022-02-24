//
// Created by David Arsov on 23.2.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pacient
{
    char ime[100];
    int osiguran, brPregledi;
} Pacient;

typedef struct MaticenDoktor
{
    char ime[100];
    int brPacienti;
    Pacient pacienti[200];
    float cena;
} MaticenDoktor;

void najuspesen_doktor (MaticenDoktor md[], int n)
{
    int maxDoktor = -1, maxPregledi = -1;
    float maxZarabotka = -1;
    for(int i = 0; i < n; i++)
    {
        float zarabotka = 0;
        int brPregledi = 0;
        for(int j = 0; j < md[i].brPacienti; j++)
        {
            if(md[i].pacienti[j].osiguran == 0)
            {
                zarabotka += md[i].pacienti[j].brPregledi * md[i].cena;
            }
            brPregledi += md[i].pacienti[j].brPregledi;
        }
        if(zarabotka > maxZarabotka)
        {
            maxDoktor = i;
            maxZarabotka = zarabotka;
            maxPregledi = brPregledi;
        }
        else if(zarabotka == maxZarabotka)
        {
            if(brPregledi > maxPregledi)
            {
                maxDoktor = i;
                maxPregledi = brPregledi;
            }
        }
    }
    printf("%s %.2f %d", md[maxDoktor].ime, maxZarabotka, maxPregledi);
}

int main()
{
    int i, j, n, broj;
    MaticenDoktor md[200];
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        //ime na doktor
        scanf("%s", md[i].ime);
        //broj na pacienti
        scanf("%d", &md[i].brPacienti);
        //cena na pregled
        scanf("%f", &md[i].cena);

        for (j = 0; j < md[i].brPacienti; j++){
            scanf("%s", md[i].pacienti[j].ime);
            scanf("%d", &md[i].pacienti[j].osiguran);
            scanf("%d", &md[i].pacienti[j].brPregledi);
        }
    }
    najuspesen_doktor(md, n);

    return 0;
}