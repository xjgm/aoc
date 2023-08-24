#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

ssize_t getline(char **restrict, size_t *restrict, FILE *restrict);

int main(void) {
    FILE *fp = fopen("input.txt", "r");

    if (fp == NULL) {
        perror("fopen");
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    int max, sum, s = 0;

    while (getline(&line, &len, fp) != EOF) {
        s = atoi(line);

        if (s > 0 && sum > INT_MAX - s) {
            return -1;
        }

        sum += s;

        if (line[0] == '\n') {
            if (sum > max)
                max = sum;
            sum = 0;
        }
    }

    free(line);
    fclose(fp);

    printf("max: %d\n", max);
    return 0;
}