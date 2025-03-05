#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

void to_uppercase(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

int main() {
    char filename[MAX_LEN];
    char line[MAX_LEN];
    FILE *file;

    // Első sor beolvasása, ami a fájlnév lesz
    printf("Adja meg a fájl nevét: ");
    if (!fgets(filename, MAX_LEN, stdin)) {
        fprintf(stderr, "Hiba a fájlnév beolvasásakor!\n");
        return 1;
    }
    filename[strcspn(filename, "\n")] = '\0'; // Új sor karakter eltávolítása

    // Fájl megnyitása írásra
    file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Hiba a fájl megnyitásakor!\n");
        return 1;
    }

    // Sorok beolvasása és fájlba írása
    printf("Adja meg a neveket és Neptun kódokat (a végjel: #):\n");
    while (1) {
        if (!fgets(line, MAX_LEN, stdin)) break;
        if (line[0] == '#' && line[1] == '\n') break; // Végjel ellenőrzése
        fputs(line, file);
    }
    fclose(file);

    // Fájl újra megnyitása olvasásra
    file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Hiba a fájl megnyitásakor olvasásra!\n");
        return 1;
    }

    // Tartalom kiírása nagybetűvel
    printf("\nA fájl tartalma nagybetűvel:\n");
    while (fgets(line, MAX_LEN, file)) {
        to_uppercase(line);
        printf("%s", line);
    }
    fclose(file);

    return 0;
}
