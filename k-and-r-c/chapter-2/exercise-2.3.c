#include <stdio.h>

/*
 * Write a function htoi(s) which converts a string of hexa demical digits
 * including optional 0x or 0X into its equivalend integer
 * */


int htoi(char s[]);


int htoi(char s[]) {
    int i, n;
    i = n = 0;

    // skip optional '0x' or '0X'
    if(s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        i = 2;
    }

    for (;s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            n = 16 * n + s[i] - '0';
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            n = 16 * n + 10 + s[i] - 'a';
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            n = 16 * n + 10 + s[i] - 'A';
        }
    }

    return n;
}

int main(int argc, char *argv[]) {

    printf("%s in dec is %d\n", "ff", htoi("ff"));
    printf("%s in dec is %d\n", "0x0a", htoi("0x0a"));
    printf("%s in dec is %d\n", "0x0B", htoi("0x0B"));
    return 0;
}
