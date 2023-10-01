#include <stdio.h>
#define IN 0
#define OUT 1
#define LONGEST 20

int main() {
    int lenwords[LONGEST];
    int c, len, state, maxcount;

    state = OUT;
    len = maxcount = 0;

    for (int i; i < LONGEST; i++) {
        lenwords[i] = 0;
    }

    while((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;

            if (len > 0) {
                ++lenwords[len - 1];
            }

            len = 0;
        } else {
            if (state == OUT)
                state = IN;
            ++len;
        }
    }

    for (int i = 0; i < LONGEST; i++) {
        if (lenwords[i] > maxcount)
            maxcount = lenwords[i];
    }

    for (int i = maxcount; i > 0; --i) {
        printf("%2d |", i);
        for (int j = 0; j < LONGEST; j++) {
            if (lenwords[j] >= i)
                printf("  #");
            else
                printf("   ");
        }
        printf("\n");
    }

    printf("   |");
    for (int i = 0; i < LONGEST; i++) {
        printf("---");
    }

    printf("\n    ");

    for (int i = 1; i <= LONGEST; i++) {
        printf("%3d", i);
    }
    printf("\n");

    return 0;
}
