#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

void copy_file(const char *source, const char *destination) {
    FILE *fp1 = fopen(source, "r");
    FILE *fp2 = fopen(destination, "w");
    char buffer[MAX_LEN];

    if (!fp1 || !fp2) {
        fprintf(stderr, "Hiba a fájlok megnyitásakor!\n");
        if (fp1) fclose(fp1);
        if (fp2) fclose(fp2);
        return;
    }

    while (fgets(buffer, MAX_LEN, fp1)) {
        fputs(buffer, fp2);
    }

    fclose(fp1);
    fclose(fp2);
}

int main() {
    char source_filename[MAX_LEN], dest_filename[MAX_LEN];
    char line[MAX_LEN];
    FILE *file;

    // Első sor beolvasása, ami a forrás fájl neve lesz
    printf("Adja meg a forrás fájl nevét: ");
    if (!fgets(source_filename, MAX_LEN, stdin)) {
        fprintf(stderr, "Hiba a fájlnév beolvasásakor!\n");
        return 1;
    }
    source_filename[strcspn(source_filename, "\n")] = '\0';

    // Forrás fájl megnyitása írásra
    file = fopen(source_filename, "w");
    if (!file) {
        fprintf(stderr, "Hiba a fájl megnyitásakor!\n");
        return 1;
    }

    // Sorok beolvasása és fájlba írása
    printf("Adja meg a neveket és Neptun kódokat (a végjel: #):\n");
    while (1) {
        if (!fgets(line, MAX_LEN, stdin)) break;
        if (line[0] == '#' && line[1] == '\n') break;
        fputs(line, file);
    }
    fclose(file);

    // Második fájlnév bekérése
    printf("Adja meg a cél fájl nevét: ");
    if (!fgets(dest_filename, MAX_LEN, stdin)) {
        fprintf(stderr, "Hiba a cél fájlnév beolvasásakor!\n");
        return 1;
    }
    dest_filename[strcspn(dest_filename, "\n")] = '\0';

    // Fájl másolása
    copy_file(source_filename, dest_filename);

    printf("A fájl sikeresen másolva lett: %s -> %s\n", source_filename, dest_filename);

    return 0;
}
