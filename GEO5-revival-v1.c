#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <math.h>

#define MAX 5000
#define MENU_SIZE 5

typedef struct {
    int id;
    double y, x, z;
    char typ[50];
} Point;

Point points[MAX];
int count = 0;

const char *menu[MENU_SIZE] = {
    "Nacist body",
    "Vypsat body",
    "Smernik a delka",
    "Zmena barev",
    "Konec"
};

int selected = 0;
int color_mode = 0;


// ====== BARVY ======
void set_color(int selected_item) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    switch (color_mode) {
        case 0:
            SetConsoleTextAttribute(h, selected_item ?
                BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED :
                FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;

        case 1:
            SetConsoleTextAttribute(h, selected_item ?
                BACKGROUND_GREEN :
                FOREGROUND_GREEN);
            break;

        case 2:
            SetConsoleTextAttribute(h, selected_item ?
                BACKGROUND_BLUE :
                FOREGROUND_BLUE | FOREGROUND_GREEN);
            break;
    }
}

void reset_color() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void clear_screen() {
    system("cls");
}


// ====== MENU ======
void draw_menu() {
    clear_screen();

    printf("=== GEO5 REVIVAL (C / Windows) ===\n\n");
    printf("Sipky Nahoru/Dolu | ENTER | C = barvy | ESC\n\n");  // Zobrazeni sipek nefunguje spravne! ↑ ↓

    for (int i = 0; i < MENU_SIZE; i++) {
        set_color(i == selected);
        printf("  %s\n", menu[i]);
        reset_color();
    }
}


// ====== NAČTENÍ ======
void load_points() {
    char filename[100];
    clear_screen();

    printf("Soubor: ");
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Soubor nenalezen!\n");
        getch();
        return;
    }

    count = 0;

    while (!feof(f)) {
        int id;
        char y[50], x[50], z[50], typ[50] = "";

        if (fscanf(f, "%d %s %s %s %s", &id, y, x, z, typ) >= 4) {

            for (int i = 0; y[i]; i++) if (y[i] == ',') y[i] = '.';
            for (int i = 0; x[i]; i++) if (x[i] == ',') x[i] = '.';
            for (int i = 0; z[i]; i++) if (z[i] == ',') z[i] = '.';

            points[count].id = id;
            points[count].y = atof(y);
            points[count].x = atof(x);
            points[count].z = atof(z);

            strcpy(points[count].typ, typ);

            count++;
        }
    }

    fclose(f);

    printf("\nNacteno bodu: %d\n", count);
    printf("Stiskni klavesu...");
    getch();
}


// ====== VÝPIS ======
void list_points() {
    clear_screen();

    for (int i = 0; i < count; i++) {
        printf("%d  %.3f  %.3f  %.3f  %s\n",
            points[i].id,
            points[i].y,
            points[i].x,
            points[i].z,
            points[i].typ);
    }

    printf("\nStiskni klavesu...");
    getch();
}


// ====== NAJDI BOD ======
Point* find_point(int id) {
    for (int i = 0; i < count; i++)
        if (points[i].id == id)
            return &points[i];

    return NULL;
}


// ====== SMĚRNÍK ======
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
    clear_screen();

    int id1, id2;
    printf("Bod 1: "); scanf("%d", &id1);
    printf("Bod 2: "); scanf("%d", &id2);

    Point *p1 = find_point(id1);
    Point *p2 = find_point(id2);

    if (!p1 || !p2) {
        printf("Bod nenalezen!\n");
        getch();
        return;
    }

    double dy = p2->y - p1->y;
    double dx = p2->x - p1->x;

    double s, d;
    smernik_delka(dy, dx, &s, &d);

    printf("\nSmernik: %.4f\n", s);
    printf("Delka: %.4f\n", d);

    printf("\nStiskni klavesu...");
    getch();
}


// ====== AKCE ======
void action(int choice) {
    switch (choice) {
        case 0: load_points(); break;
        case 1: list_points(); break;
        case 2: compute(); break;
        case 3: color_mode = (color_mode + 1) % 3; break;
        case 4: exit(0);
    }
}


// ====== MAIN ======
int main() {
    int ch;

    while (1) {
        draw_menu();

        ch = getch();

        if (ch == 224) {
            ch = getch();
            if (ch == 72) selected = (selected - 1 + MENU_SIZE) % MENU_SIZE;
            if (ch == 80) selected = (selected + 1) % MENU_SIZE;
        }
        else if (ch == 13) {
            action(selected);
        }
        else if (ch == 27) {
            break;
        }
        else if (ch == 'c' || ch == 'C') {
            color_mode = (color_mode + 1) % 3;
        }
    }

    return 0;
}