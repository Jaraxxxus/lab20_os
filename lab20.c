#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <glob.h>


#define SIZE 256
#define FIASCO -1
#define SUCCESS 0



int printFileNames(char* pattern) {
    glob_t result;
    int globResult = glob(pattern, GLOB_NOCHECK, NULL, &result);
    if (isGlobError(globResult)) {
        perror("glob_error");
        globfree(&result);
        return FIASCO;
    }
    for (int i = 0; i < result.gl_pathc; i++) {
        printf("%s\n", result.gl_pathv[i]);
    }
    globfree(&result);
    return SUCCESS;
}

int main(int argc, char* argv[]) {
    char pattern[SIZE]; //шаблон
    int patternLength;


    printf("Enter pattern: ");
    fgets(pattern, SIZE, stdin);
    patternLength = strlen(pattern) - 1;
    pattern[patternLength] = 0;
    if (patternLength == 0) {
        fprintf(stderr, "The pattern can't be empty\n");
        return FIASCO;
    }


    if (printFileNames(pattern) == FIASCO) return FIASCO;
    return SUCCESS;
}
