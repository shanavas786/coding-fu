#include <unistd.h>


void write_triangle(int n) {
    for(int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            write(2, "*", 1);
        }
        write(2, "\n", 1);
    }
}


int main(int argc, char *argv[]) {
    write_triangle(10);
    return 0;
}
