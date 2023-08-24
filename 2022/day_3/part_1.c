#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

ssize_t getline(char **restrict line, size_t *restrict len, FILE *restrict fp);

int main(void) {
    FILE *fp = fopen("input.txt", "r");

    if (fp == NULL) {
        perror("fopen");
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    size_t sum = 0;

    while (getline(&line, &len, fp) != EOF) {
        if (line[0] == '\0')
            continue;

        size_t nline = strlen(line);
        line[nline - 1] = '\0';

        for (int i = 0; i < nline / 2; i++) {
            int found = 0;

            for (int j = nline / 2; j < nline - 1; j++) {
                if (line[i] == line[j]) {
                    size_t s = 0;

                    if (line[i] - '0' <= 42)
                        s = line[i] - '0' + 10;
                    else
                        s = line[i] - '0' - 48;

                    sum += s;
                    found = 1;
                    break;
                }
            }

            if (found == 1)
                break;
        }
    }

    free(line);
    fclose(fp);

    printf("sum: %zu\n", sum);
    return 0;
}