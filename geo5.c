#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <string.h>

#define MAX 2000

typedef struct {
    int id;
    double y, x, z;
    char typ[50];
} Point;

Point points[MAX];
int count = 0;


// ====== NAČTENÍ BODŮ ======
void load_points() {
    char filename[100];
    printf("Soubor: ");
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Chyba otevreni souboru!\n");
        return;
    }

    count = 0;

    while (!feof(f)) {
        int id;
        char y[50], x[50], z[50], typ[50];

        if (fscanf(f, "%d %s %s %s %s", &id, y, x, z, typ) >= 4) {
            points[count].id = id;

            // převod čárky na tečku
            for (int i = 0; y[i]; i++) if (y[i] == ',') y[i] = '.';
            for (int i = 0; x[i]; i++) if (x[i] == ',') x[i] = '.';
            for (int i = 0; z[i]; i++) if (z[i] == ',') z[i] = '.';

            points[count].y = atof(y);
            points[count].x = atof(x);
            points[count].z = atof(z);

            if (strlen(typ) > 0)
                strcpy(points[count].typ, typ);
            else
                strcpy(points[count].typ, "");

            count++;
        }
    }

    fclose(f);
    printf("Nacteno bodu: %d\n", count);
}


// ====== VÝPIS ======
void list_points() {
    for (int i = 0; i < count; i++) {
        printf("%d  %.3f  %.3f  %.3f  %s\n",
               points[i].id,
               points[i].y,
               points[i].x,
               points[i].z,
               points[i].typ);
    }
}


// ====== NALEZENÍ BODU ======
Point* find_point(int id) {
    for (int i = 0; i < count; i++) {
        if (points[i].id == id)
            return &points[i];
    }
    return NULL;
}


// ====== SMĚRNÍK A DÉLKA ======
void smernik_delka(double dy, double dx, double *s, double *d) {
    if (dy == 0 && dx == 0) *s = 0;
    else if (dx == 0) *s = (dy > 0) ? 100 : 300;
    else if (dy == 0) *s = (dx > 0) ? 0 : 200;
    else {
        *s = atan(dy / dx) * 200.0 / M_PI;
        if (dx > 0 && dy < 0) *s += 400;
        else if (dx < 0) *s += 200;
    }

    *d = sqrt(dx * dx + dy * dy);
}


// ====== VÝPOČET ======
void compute() {
    int id1, id2;
    printf("Bod 1: ");
    scanf("%d", &id1);
    printf("Bod 2: ");
    scanf("%d", &id2);

    Point *p1 = find_point(id1);
    Point *p2 = find_point(id2);

    if (!p1 || !p2) {
        printf("Bod nenalezen!\n");
        return;
    }

    double dy = p2->y - p1->y;
    double dx = p2->x - p1->x;

    double s, d;
    smernik_delka(dy, dx, &s, &d);

    printf("Smernik: %.4f\n", s);
    printf("Delka: %.4f\n", d);
}


// ====== MENU ======
void menu() {
    int choice;

    do {
        printf("\n=== GEO5 C RETRO ===\n");
        printf("1 - Nacist body\n");
        printf("2 - Vypsat body\n");
        printf("3 - Smernik a delka\n");
        printf("4 - Konec\n");
        printf("Volba: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: load_points(); break;
            case 2: list_points(); break;
            case 3: compute(); break;
        }

    } while (choice != 4);
}


// ====== MAIN ======
int main() {
    menu();
    return 0;
}