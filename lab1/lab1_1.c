//
// Created by David Arsov on 23.2.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct proizvod
{
    char ime[20];
    float cena, kolicina;
} proizvod;

int main()
{
    int n;
    scanf("%d", &n);
    proizvod proizvodi[n];
    float vkupno = 0;
    for(int i = 0; i < n; i++)
    {
        scanf("%s %f %f", proizvodi[i].ime, &proizvodi[i].cena, &proizvodi[i].kolicina);
        vkupno += proizvodi[i].cena * proizvodi[i].kolicina;
        printf("%d. %s\\t%.2f x %.1f = %.2f\n", i + 1, proizvodi[i].ime, proizvodi[i].cena, proizvodi[i].kolicina, proizvodi[i].cena * proizvodi[i].kolicina);
    }
    printf("Total: %.2f", vkupno);
    return 0;
}
