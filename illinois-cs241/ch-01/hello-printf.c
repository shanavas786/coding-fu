#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    close(1);
    mode_t mode = S_IRUSR | S_IWUSR;
    int fd = open("hello-world-printf.txt", O_CREAT | O_WRONLY | O_TRUNC, mode);
    write(fd, "Hello world\n", 12);
    close(fd);
    return 0;
}
