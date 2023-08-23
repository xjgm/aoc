#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void save_sum(int max[3], int sum);

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

    int max[3] = {0, 0, 0};
    int sum = 0;

    while ((nread = getline(&line, &len, fp)) != -1) {
        sum += atoi(line);

        if (line[0] == '\n') {
            save_sum(max, sum);
            sum = 0;
        }
    }

    // XXX: this should/could be handled diffrently
    if (sum > 0) {
        save_sum(max, sum);
        sum = 0;
    }

    free(line);
    fclose(fp);

    int total = 0;
    for (int i = 0; i < 3; i++) {
        printf("max: %d\n", max[i]);
        total += max[i];
    }
    printf("total: %d\n", total);
    exit(0);
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

/*

0 = 10
1 = 8
2 = 4

-> 9

1

2 = 1
1 = sum

for n = 2; n >= 0; n--;
    if n > 0
    2 = [n-1]

*/