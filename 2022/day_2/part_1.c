#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct {
        char *key;
        int   score;
} round;

ssize_t getline(char **restrict, size_t *restrict, FILE *restrict);
int     score_round(round *, size_t, const char *);

int
main(void)
{
        FILE *fp = fopen("input.txt", "r");

        if (fp == NULL) {
                perror("fopen");
                return -1;
        }

        char  *line     = NULL;
        size_t len      = 0;
        round  rounds[] = {
            {"A X", 1 + 3}, {"A Y", 2 + 6}, {"A Z", 3 + 0},
            {"B X", 1 + 0}, {"B Y", 2 + 3}, {"B Z", 3 + 6},
            {"C X", 1 + 6}, {"C Y", 2 + 0}, {"C Z", 3 + 3},
        };
        size_t nrounds = sizeof(rounds) / sizeof(round);
        int    score   = 0;
        int    s       = 0;

        while (getline(&line, &len, fp) != EOF) {
                if (line[0] == '\0')
                        continue;

                line[strlen(line) - 1] = '\0';
                s                      = score_round(rounds, nrounds, line);

                if (s > 0 && score > INT_MAX - s) {
                        return 1;
                }

                score += s;
        }

        free(line);
        fclose(fp);

        printf("score: %d\n", score);

        return 0;
}

int
score_round(round *rounds, size_t size, const char *key)
{
        int score = 0;

        for (int i = 0; i < size; i++)
                if (strcmp(rounds[i].key, key) == 0) {
                        score = rounds[i].score;
                        break;
                }

        return score;
}