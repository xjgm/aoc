#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_badge(char **);

int
main(void)
{
        FILE *fp = fopen("input.txt", "r");

        if (fp == NULL) {
                perror("fopen");
                return 1;
        }

        char  *line = NULL;
        size_t len  = 0;
        size_t sum  = 0;

        int   idx = 0;
        char *lines[3];

        while (getline(&line, &len, fp) != EOF) {
                if (line[0] == '\0')
                        continue;

                line[strlen(line) - 1] = '\0';

                lines[idx] = malloc(strlen(line));
                strcpy(lines[idx], line);
                idx++;

                if (idx == 3) {
                        size_t s     = 0;
                        char   badge = find_badge(lines);

                        if (badge - '0' <= 42)
                                s = badge - '0' + 10;
                        else
                                s = badge - '0' - 48;

                        sum += s;

                        idx = 0;
                }
        }

        free(line);
        fclose(fp);

        printf("sum: %zu\n", sum);
        return 0;
}

char
find_badge(char *lines[3])
{
        for (int i = 0; i < strlen(lines[0]); i++) {
                int count = 0;

                for (int n = 0; n < strlen(lines[1]); n++) {
                        if (lines[0][i] == lines[1][n]) {
                                count++;
                                break;
                        }
                }

                for (int n = 0; n < strlen(lines[2]); n++) {
                        if (lines[0][i] == lines[2][n]) {
                                count++;
                                break;
                        }
                }

                if (count == 2)
                        return lines[0][i];
        }

        return ' ';
}
