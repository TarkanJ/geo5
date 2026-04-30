/* LINUX VERZE! */

#include <stdio.h>
#include <stdlib.h>
// #include <conio.h>
#include <termios.h> // <= Toto pro Linux library
#include <unistd.h>
#define MENU_SIZE 4

const char *menu[MENU_SIZE] = {
    "Nacist body",
    "Smernik a delka",
    "Zmena barev",
    "Konec"
};

int selected = 0;
int color_mode = 0;


// ====== READKEY (termios) ======
int readkey() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO); // raw mode
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    if (ch == 27) { // ESC sekvence
        if (getchar() == '[') {
            switch (getchar()) {
                case 'A': ch = 'U'; break; // UP
                case 'B': ch = 'D'; break; // DOWN
            }
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}


// ====== BARVY ======
void set_color(int selected_item) {
    switch (color_mode) {
        case 0: // klasika
            if (selected_item)
                printf("\033[30;47m"); // černá na bílé
            else
                printf("\033[37;40m"); // bílá na černé
            break;

        case 1: // zelená
            if (selected_item)
                printf("\033[30;42m");
            else
                printf("\033[32;40m");
            break;

        case 2: // modrá
            if (selected_item)
                printf("\033[37;44m");
            else
                printf("\033[34;40m");
            break;
    }
}


// ====== RESET BARVY ======
void reset_color() {
    printf("\033[0m");
}


// ====== CLEAR ======
void clear_screen() {
    printf("\033[2J\033[H");
}


// ====== MENU ======
void draw_menu() {
    clear_screen();

    printf("=== GEO5 RETRO LINUX ===\n\n");
    printf("Pouzij sipky ↑ ↓, ENTER = vyber, C = barvy, ESC = konec\n\n");

    for (int i = 0; i < MENU_SIZE; i++) {
        set_color(i == selected);
        printf("  %s\n", menu[i]);
        reset_color();
    }
}


// ====== FAKE FUNKCE ======
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
            exit(0);
    }

    printf("\nStiskni libovolnou klavesu...");
    getchar();
}


// ====== MAIN ======
int main() {
    int key;

    while (1) {
        draw_menu();

        key = readkey();

        if (key == 'U') { // nahoru
            selected = (selected - 1 + MENU_SIZE) % MENU_SIZE;
        }
        else if (key == 'D') { // dolu
            selected = (selected + 1) % MENU_SIZE;
        }
        else if (key == '\n') { // ENTER
            action(selected);
        }
        else if (key == 'c' || key == 'C') {
            color_mode = (color_mode + 1) % 3;
        }
        else if (key == 27) { // ESC
            break;
        }
    }

    reset_color();
    clear_screen();
    return 0;
}