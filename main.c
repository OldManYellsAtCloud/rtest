#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int fd;

    if (argc > 1)
        fd = open(argv[1], O_RDWR);
    else
        fd = open("/dev/input/event2", O_RDWR);

    struct ff_effect ffe;
    struct input_event play;
    struct input_event stop;

    struct timespec hundred_ms;
    hundred_ms.tv_sec = 0;
    hundred_ms.tv_nsec = 100000000;

    char c;

    ffe.type = FF_PERIODIC;
    ffe.id = -1;
    ffe.u.periodic.custom_len = 500;
    ffe.u.periodic.waveform = FF_SQUARE;

    ioctl(fd, EVIOCSFF, &ffe);

    play.code = ffe.id;
    play.type = EV_FF;
    play.value = 3;

    stop.code = ffe.id;
    stop.type = EV_FF;
    stop.value = 0;


    while (read(STDIN_FILENO, &c, 1) > 0) {
        write(fd, (const void*) &play, sizeof(play));
        nanosleep(&hundred_ms, &hundred_ms);
        write(fd, (const void*) &stop, sizeof(stop));
    }

    close(fd);

    return 0;
}
