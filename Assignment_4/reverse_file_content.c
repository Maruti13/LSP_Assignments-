/*
 Assignment 4
 Question 5 : Reverse File Content
 Usage : ./a.out filename
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd;
    off_t pos;
    char ch;

    if (argc != 2)
    {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    //move to end to get file size
    pos = lseek(fd, 0, SEEK_END);
    if (pos == -1)
    {
        perror("lseek failed");
        close(fd);
        return 1;
    }

    //read backwards one byte at a time
    while (pos > 0)
    {
        pos--;  // step one byte back
        lseek(fd, pos, SEEK_SET);

        if (read(fd, &ch, 1) != 1)
        {
            perror("read failed");
            close(fd);
            return 1;
        }

        write(1, &ch, 1);   // print to stdout
    }

    write(1, "\n", 1);

    close(fd);
    return 0;
}
