#include<unistd.h>

int main(int argc, char *argv[]) {
    write(1, "Hello world\n", 12);
    return 0;
}
