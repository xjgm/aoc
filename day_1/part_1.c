#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    int max, sum = 0;

    while ((nread = getline(&line, &len, fp)) != -1) {
        sum += atoi(line);

        if (line[0] == '\n') {
            if (sum > max)
                max = sum;
            sum = 0;
        }
    }

    free(line);
    fclose(fp);

    printf("max: %d\n", max);
    exit(0);
}