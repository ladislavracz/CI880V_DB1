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

void copy_file(const char *source, const char *destination) {
    FILE *fp1 = fopen(source, "r");
    FILE *fp2 = fopen(destination, "w");
    char line[MAX_LINE];
    
    if (fp1 == NULL || fp2 == NULL) {
        perror("Error opening files");
        return;
    }
    
    while (fgets(line, MAX_LINE, fp1) != NULL) {
        fputs(line, fp2);
    }
    
    fclose(fp1);
    fclose(fp2);
}

int main() {
    char filename1[MAX_LINE], filename2[MAX_LINE];
    char line[MAX_LINE];
    FILE *file;

    // Fájlnév beolvasása
    printf("Enter source file name: ");
    fgets(filename1, MAX_LINE, stdin);
    filename1[strcspn(filename1, "\n")] = 0;
    
    printf("Enter destination file name: ");
    fgets(filename2, MAX_LINE, stdin);
    filename2[strcspn(filename2, "\n")] = 0;
    
    // Fájl megnyitása írásra
    file = fopen(filename1, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    // Sorok beolvasása és fájlba írása
    while (1) {
        printf("Enter name and Neptun code (# to end): ");
        fgets(line, MAX_LINE, stdin);
        line[strcspn(line, "\n")] = 0;
        
        if (strcmp(line, "#") == 0) {
            break;
        }
        fprintf(file, "%s\n", line);
    }
    fclose(file);
    
    // Fájl másolása
    copy_file(filename1, filename2);
    
    // Másolt fájl tartalmának kiírása nagybetűsen
    file = fopen(filename2, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    printf("\nContent of copied file in uppercase:\n");
    while (fgets(line, MAX_LINE, file) != NULL) {
        to_uppercase(line);
        printf("%s", line);
    }
    fclose(file);
    
    return 0;
}
