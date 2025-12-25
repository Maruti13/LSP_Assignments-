#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char filename[100];
    char mode[5];
    int fd, iflags;

    printf("Enter file name: ");
    scanf("%s", filename);

    printf("Enter mode (R/W/RW/A): ");
    scanf("%s", mode);

    if (strcmp(mode, "R") == 0)
        iflags = O_RDONLY;
    else if (strcmp(mode, "W") == 0)
        iflags = O_WRONLY | O_CREAT;
    else if (strcmp(mode, "RW") == 0)
        iflags = O_RDWR | O_CREAT;
    else if (strcmp(mode, "A") == 0)
        iflags = O_APPEND | O_CREAT;
    else
    {
        printf("Invalid mode\n");
        return 1;
    }

    fd = open(filename, iflags, 0644);

    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    printf("File opened successfully\n");
    printf("File descriptor: %d\n", fd);

    close(fd);
    return 0;
}
