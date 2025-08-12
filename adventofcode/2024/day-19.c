#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// number of ways the last n chars of design can be formed
long CACHE[1024] = {0};

long get_possible_arrangments(char *design, char **patterns, int num_patterns) {
    /* printf("%s\n", design); */

    char *pattern;
    int plen;
    int dlen = strlen(design);

    if (CACHE[dlen] != -1) {
        /* printf("cache hit %s => %ld \n", design, CACHE[dlen]); */
        return CACHE[dlen];
    }

    long possible = 0;
    for (int i = 0; i < num_patterns; i++) {
        pattern = patterns[i];
        plen = strlen(patterns[i]);

        if (strcmp(design, pattern) == 0) {
            // perfect match
            possible++;
            continue;
        }

        // design is longer
        if (dlen > plen) {
            // pattern is at the beginning of design
            if (strncmp(design, pattern, plen) == 0) {
                /* printf("%s prefix matched\n", pattern); */
                possible += get_possible_arrangments(design + plen, patterns,
                                                     num_patterns);
            }
        }
    }

    CACHE[dlen] = possible;
    /* printf("%s => %ld \n", design, CACHE[dlen]); */
    return possible;
}

int main(int argc, char *argv[]) {
    if (argc < 1) {
        exit(1);
    }

    char *file_path = argv[1];
    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        exit(1);
    }

    char *patterns[1024] = {0};
    int num_patterns = 0;

    char line[4096], design[1024];
    fgets(line, sizeof(line), file);

    char *pattern;
    char *rest = line;
    while ((pattern = strtok_r(rest, " ,\n", &rest))) {
        patterns[num_patterns++] = pattern;
    }

    /* for (int i = 0; i < num_patterns; i++) { */
    /*     printf("%d: %s\n", i, patterns[i]); */
    /* } */
    // skip empty line

    fgets(design, sizeof(design), file);

    long designs_possible = 0;
    while (fgets(design, sizeof(design), file) != 0) {
        // removing trailing \r and or \n
        design[strcspn(design, "\r\n")] = 0;

        for (int i = 0; i < 1024; i++) {
            CACHE[i] = -1;
        }

        long p = get_possible_arrangments(design, patterns, num_patterns);
        /* printf("%s can be formed in %ld ways\n", design, p); */
        designs_possible += p;
    }

    printf("%ld designs possible\n", designs_possible);
    fclose(file);
    return 0;
}
