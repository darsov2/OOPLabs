//
// Created by David Arsov on 24.2.2022.
//

#include <stdio.h>
#include <string.h>
#define NEDELI 4
#define DENOVI 5

typedef struct RabotnaNedela
{
    int rabotniCasovi[DENOVI], brNedela;
} rabotnaNedela;

typedef struct Rabotnik
{
    char ime[20];
    rabotnaNedela rabotnaNedela[NEDELI];
} rabotnik;

int maxNedela(rabotnik *r)
{
    int maxCasovi = -1, maxNedela = -1;
    for(int i = 0; i < 4; i++)
    {
        int casoviNedela = 0;
        for(int j = 0; j < 5; j++)
        {
            casoviNedela += r->rabotnaNedela[i].rabotniCasovi[j];
        }
        if(casoviNedela > maxCasovi)
        {
            maxCasovi = casoviNedela;
            maxNedela = i;
        }
    }
    return maxNedela + 1;
}

void table(rabotnik r[], int n)
{
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for(int i = 0; i < n; i++)
    {
        printf("%s\t", r[i].ime);
        int vkupnoCasovi = 0;
        for(int j = 0; j < 4; j++)
        {
            int casoviNedela = 0;
            for(int k = 0; k < 5; k++)
            {
                casoviNedela += r[i].rabotnaNedela[j].rabotniCasovi[k];
            }
            vkupnoCasovi += casoviNedela;
            printf("%d\t", casoviNedela);
        }
        printf("%d\n", vkupnoCasovi);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    rabotnik rabotnici[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", rabotnici[i].ime);
        int j;
        for (j = 0; j < NEDELI; ++j) {
            int k;
            for (k = 0; k < DENOVI; ++k) {
                scanf("%d", &rabotnici[i].rabotnaNedela[j].rabotniCasovi[k]);
            }

        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].ime);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}
