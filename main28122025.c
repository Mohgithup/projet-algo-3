#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void Triparselection(int *t, int n) {
    int i, pmin, j, c;
    for (i = 0; i < n - 1; i++) {
        pmin = i;
        for (j = i + 1; j < n; j++) {
            if (t[pmin] > t[j]) {
                pmin = j;
            }
        }
        c = t[i];
        t[i] = t[pmin];
        t[pmin] = c;
    }
}

void Triparbulle(int *t, int n) {
    int i, j, c;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (t[j] > t[j + 1]) {
                c = t[j];
                t[j] = t[j + 1];
                t[j + 1] = c;
            }
        }
    }
}

int partition(int *t, int pmax, int pmin) {
    int pivot = t[pmax];
    int i = pmin - 1;
    for (int j = pmin; j < pmax; j++) {
        if (t[j] <= pivot) {
            i++;
            int temp = t[i];
            t[i] = t[j];
            t[j] = temp;
        }
    }
    int temp = t[i + 1];
    t[i + 1] = t[pmax];
    t[pmax] = temp;
    return i + 1;
}

void trirapide(int *t, int pmax, int pmin) {
    if (pmin < pmax) {
        int pivot = partition(t, pmax, pmin);
        trirapide(t, pivot - 1, pmin);
        trirapide(t, pmax, pivot + 1);
    }
}

void fusion(int *t, int gauche, int droit, int m) {
    int n1 = m - gauche + 1;
    int n2 = droit - m;
    int tgauche[n1], tdroit[n2];

    for (int i = 0; i < n1; i++) {
        tgauche[i] = t[gauche + i];
    }
    for (int j = 0; j < n2; j++) {
        tdroit[j] = t[m + 1 + j];
    }

    int i = 0, j = 0, k = gauche;
    while (i < n1 && j < n2) {
        if (tgauche[i] <= tdroit[j]) {
            t[k] = tgauche[i];
            i++;
        } else {
            t[k] = tdroit[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        t[k] = tgauche[i];
        i++;
        k++;
    }

    while (j < n2) {
        t[k] = tdroit[j];
        j++;
        k++;
    }
}

void triparfusion(int *t, int g, int d) {
    if (g < d) {
        int m = (g + d) / 2;
        triparfusion(t, g, m);
        triparfusion(t, m + 1, d);
        fusion(t, g, d, m);
    }
}

void Tripeigne(int *t, int n) {
    int intervalle = n;
    bool echange = true;

    while (intervalle > 1 || echange) {
        intervalle = (int)(intervalle / 1.3);
        if (intervalle < 1) intervalle = 1;
        echange = false;

        for (int i = 0; i + intervalle < n; i++) {
            if (t[i] > t[i + intervalle]) {
                int temp = t[i];
                t[i] = t[i + intervalle];
                t[i + intervalle] = temp;
                echange = true;
            }
        }
    }
}


int main() {
    int i, n;
    int choix;
    int choix2;
    
    do {
        printf("Donner la taille du vecteur: ");
        scanf("%d", &n);
    } while (n <= 0);

    int t[n], t2[n];

    printf("Remplir le premier tableau :\n");
    for (i = 0; i < n; i++) {
        printf("Donner le %d element: ", i + 1);
        scanf("%d", &t[i]);
    }

    printf("Entrez votre choix: 1. Vector Sort / 2. Matrix Sort / 3. Linked List Sort: ");
    scanf("%d", &choix);

    if (choix == 1) {
        printf("Choisissez le type de tri pour le vecteur:\n");
        printf("1. Tri par sélection\n");
        printf("2. Tri à bulle\n");
        printf("3. Tri rapide\n");
        printf("4. Tri fusion\n");
        printf("5. Tri peigne\n");
        scanf("%d", &choix2);

        switch (choix2) {
            case 1:
                Triparselection(t, n);
                break;
            case 2:
                Triparbulle(t, n);
                break;
            case 3:
                trirapide(t, n - 1, 0);
                break;
            case 4:
                triparfusion(t, 0, n - 1);
                break;
            case 5:
                Tripeigne(t, n);
                break;
            default:
                printf("Choix invalide\n");
                break;
        }
        printf("Vecteur trie: ");
        for (i = 0; i < n; i++) {
            printf("%d ", t[i]);
        }
        
        printf("\n");
    }
    
}
