#include <stdio.h>
#define IN 0
#define OUT 1

int main() {
    int lenwords[20];
    int c, len, state;
    state = OUT;
    for (int i; i < 20; i++) {
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


    for (int i = 20 - 1; i >= 0; --i) {
        printf("%2d |", i);
        for (int j = 0; j < lenwords[i]; j++) {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
