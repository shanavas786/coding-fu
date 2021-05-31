#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    int fd = open("hello-world.txt", O_CREAT | O_WRONLY | O_TRUNC);
    write(fd, "Hello world\n", 12);
    close(fd);
    return 0;
}
