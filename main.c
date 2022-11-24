#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/input.h>

int main(int argc, char *argv[])
{
    int fd = open("/dev/input/event2", O_RDWR);
    int n, res;
    res = ioctl(fd, EVIOCGEFFECTS, &n);
    printf("ioctl result: %i\n", res);
    printf("The number of effects that can be stored: %i\n", n);
    return 0;
}
