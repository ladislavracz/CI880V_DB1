#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 256

void to_uppercase(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

int main() {
    char filename[MAX_LINE];
    char line[MAX_LINE];
    FILE *file;

    // Fájlnév beolvasása
    printf("File name: ");
    fgets(filename, MAX_LINE, stdin);
    filename[strcspn(filename, "\n")] = 0; // Újsor eltávolítása
    
    // Fájl megnyitása írásra
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    // Sorok beolvasása és fájlba írása
    while (1) {
        printf("Enter name and Neptun code (# to end): ");
        fgets(line, MAX_LINE, stdin);
        if (line[0] == '#' && line[1] == '\n') {
            break;
        }
        fputs(line, file);
    }
    fclose(file);
    
    // Fájl újranyitása olvasásra
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    // Tartalom visszaírása nagybetűsen
    printf("\nContent in uppercase:\n");
    while (fgets(line, MAX_LINE, file) != NULL) {
        to_uppercase(line);
        printf("%s", line);
    }
    fclose(file);
    
    return 0;
}