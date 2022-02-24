//
// Created by David Arsov on 24.2.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SkiLift
{
    char ime[20];
    int brKorisnici, funkcija;
} SkiLift;

typedef struct SkiCentar
{
    char ime[20], drzava[20];
    SkiLift skiLift[20];
    int brSkiLiftovi;
};

void najgolemKapacitet (struct SkiCentar sc[], int n)
{
    int maxCentar = -1, maxKapacitet = -1;
    for(int i = 0; i < n; i++)
    {
        int vkupnoKapacitet = 0;
        for(int j = 0; j < sc[i].brSkiLiftovi; j++)
        {
            if(sc[i].skiLift[j].funkcija)
            {
                vkupnoKapacitet += sc[i].skiLift[j].brKorisnici;
            }
        }
        if(vkupnoKapacitet > maxKapacitet)
        {
            maxCentar = i;
            maxKapacitet = vkupnoKapacitet;
        }
        else if(vkupnoKapacitet == maxKapacitet)
        {
            if(sc[i].brSkiLiftovi > sc[maxCentar].brSkiLiftovi)
            {
                maxCentar = i;
                maxKapacitet = vkupnoKapacitet;
            }
        }
    }
    printf("%s\n%s\n%d", sc[maxCentar].ime, sc[maxCentar].drzava, maxKapacitet);
}

int main()
{
    int n;
    scanf("%d", &n);
    struct SkiCentar skiCentar[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%s %s %d", skiCentar[i].ime, skiCentar[i].drzava, &skiCentar[i].brSkiLiftovi);

        for(int j = 0; j < skiCentar[i].brSkiLiftovi; j++)
        {
            scanf("%s %d %d", skiCentar[i].skiLift[j].ime, &skiCentar[i].skiLift[j].brKorisnici, &skiCentar[i].skiLift[j].funkcija);
        }
    }

    najgolemKapacitet(skiCentar, n);

    return 0;
}