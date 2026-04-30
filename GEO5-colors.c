#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MENU_SIZE 4

const char *menu[MENU_SIZE] = {
    "Nacist body",
    "Smernik a delka",
    "Zmena barev",
    "Konec"
};

int selected = 0;
int color_mode = 0;


// ====== BARVY ======
void set_color(int selected_item) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    switch (color_mode) {
        case 0: // klasika
            if (selected_item)
                SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
            else
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;

        case 1: // zelená
            if (selected_item)
                SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
            else
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            break;

        case 2: // modrá
            if (selected_item)
                SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
            else
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
            break;
    }
}


// ====== RESET ======
void reset_color() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}


// ====== CLEAR ======
void clear_screen() {
    system("cls");
}


// ====== MENU ======
void draw_menu() {
    clear_screen();

    printf("=== GEO5 RETRO WINDOWS ===\n\n");
    printf("Sipky ↑ ↓, ENTER = vyber, C = barvy, ESC = konec\n\n");

    for (int i = 0; i < MENU_SIZE; i++) {
        set_color(i == selected);
        printf("  %s\n", menu[i]);
        reset_color();
    }
}


// ====== AKCE ======
void action(int choice) {
    clear_screen();

    switch (choice) {
        case 0:
            printf(">>> Nacitani bodu (zatim demo)\n");
            break;
        case 1:
            printf(">>> Vypocet smerniku (zatim demo)\n");
            break;
        case 2:
            color_mode = (color_mode + 1) % 3;
            printf(">>> Zmena barev\n");
            break;
        case 3:
            printf("Konec...\n");
            return;
    }

    printf("\nStiskni libovolnou klavesu...");
    getch();
}


// ====== MAIN ======
int main() {
    int ch;

    while (1) {
        draw_menu();

        ch = getch();

        if (ch == 224) { // speciální klávesy
            ch = getch();

            if (ch == 72) { // nahoru
                selected = (selected - 1 + MENU_SIZE) % MENU_SIZE;
            }
            else if (ch == 80) { // dolu
                selected = (selected + 1) % MENU_SIZE;
            }
        }
        else if (ch == 13) { // ENTER
            if (selected == 3) break;
            action(selected);
        }
        else if (ch == 27) { // ESC
            break;
        }
        else if (ch == 'c' || ch == 'C') {
            color_mode = (color_mode + 1) % 3;
        }
    }

    reset_color();
    clear_screen();
    return 0;
}