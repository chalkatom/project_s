#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

void print_line(int l, int flag) {
    if (flag == 1) {
        for (int i = 0; i < l * 5; i++) {
            printf("_");
        }
        printf("\n");
    } else if (flag == 2) {
        for (int j = 0; j < l; j++) {
            printf("|");
            for (int k = 0; k < l * 5; k++) {
                printf(" ");
            }
            printf("|\n");
        }
    }
}

void print_border(int l) {
    printf(" ");
    print_line(l, 1);
    printf("\x1b[%d;%df", 2, 1);
    print_line(l, 2);
    printf("\x1b[%d;%df", l + 1, 2);
    print_line(l, 1);
}

void print_option(int x, int y, char *text, int selected) {
    printf("\x1b[%d;%df", y, x);
    if (selected) {
        printf("\x1b[1;32m> %s\x1b[0m\n", text); // highlighted green if selected
    } else {
        printf("  %s\n", text);
    }
}

void print_options(int x, int y, int selected){
        print_option(x, y, "start game", selected == 0);
        print_option(x, y+1, "options", selected == 1);
        print_option(x, y+2, "quit", selected == 2);
}

void print_screen(int selected) {
    printf("\033[H\033[J");
    print_border(40);
    printf("\x1b[%d;%df", 20, 100);
    printf("SCOUNDREL.");
    print_options(10, 30, selected);
    printf("\x1b[%d;%df", 42, 1);
}

void play_sound(char *mp3){
    char command[256];
    sprintf(command, "open \"%s\" type mpegvideo alias mp3", mp3);

    mciSendStringA(command, NULL, 0, NULL);
    mciSendStringA("play mp3", NULL, 0, NULL);
    Sleep(500);
    mciSendStringA("close mp3", NULL, 0, NULL);
}

void update_screen(int selected, int prev_s){
    if (selected == 0){
        print_options(10, 30, selected);
    } else if (selected == 1){
        print_options(10, 30, selected);
    } else if (selected == 2){
        print_options(10, 30, selected);
    }
    if (selected < prev_s){
        play_sound("up.mp3");
    }else if (selected > prev_s){
        play_sound("down.mp3");
    }
}

int main() {
    int selected = 0;
    int prev_s = 0;
    char key;

    printf("\e[?25l");
    print_screen(selected);
    
    while (1) {
        key = getch();

        if (key == 'w' && selected > 0) { // Up arrow
            prev_s = selected;
            selected--;
        } else if (key == 's' && selected < 2) { // Down arrow
            prev_s = selected;
            selected++;
        } else if (key == '\n' || key == 13) { // Enter key
            play_sound("select.mp3");
            if (selected == 0) {
                printf("\033[H\033[J");
                printf("Starting game...\n");
                Sleep(1000);
                printf("\033[H\033[J"); 
                break;
            } else if (selected == 1) {
                printf("\033[H\033[J");
                printf("Options Screen...\n");
                break;
            } else if (selected == 2) {
                printf("\033[H\033[J");
                printf("Quitting...\n");
                exit(0);
            }
        } else {
            continue;
        }

        update_screen(selected, prev_s);
    }

    printf("\e[?25h");
    return 0;
}

//AUDIO NO WORK.
//FIX LATER.
