#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

ssize_t getline(char **restrict, size_t *restrict, FILE *restrict);
void save_sum(int[], int);

int main(void) {
    FILE *fp = fopen("input.txt", "r");

    if (fp == NULL) {
        perror("fopen");
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    int max[3] = {0, 0, 0};
    int sum, s = 0;

    while (getline(&line, &len, fp) != EOF) {
        s = atoi(line);

        if (s > 0 && sum > INT_MAX - s) {
            return -1;
        }

        sum += s;

        if (line[0] == '\n') {
            save_sum(max, sum);
            sum = 0;
        }
    }

    if (sum > 0) {
        save_sum(max, sum);
    }

    free(line);
    fclose(fp);

    int total = 0;

    for (int i = 0; i < 3; i++) {
        if (max[i] > 0 && total > INT_MAX - max[i]) {
            return -1;
        }

        printf("max: %d\n", max[i]);
        total += max[i];
    }

    printf("total: %d\n", total);
    return 0;
}

void save_sum(int max[3], int sum) {
    for (int i = 0; i < 3; i++) {
        if (sum > max[i]) {
            for (int n = 2; n > i; n--)
                max[n] = max[n - 1];
            max[i] = sum;
            break;
        }
    }
}
