/*
 Assignment 4
 Question 1 : File Copy Utility using read() and write()
 Command line usage : ./a.out source_file destination_file
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
    int fd_src, fd_dest;
    char buffer[BUFSIZE];
    ssize_t rbytes, wbytes;

    if (argc != 3)
    {
        printf("Usage: %s <source_file> <destination_file>\n",argv[0]);
        return 1;
    }

    fd_src = open(argv[1], O_RDONLY);
    if (fd_src == -1)
    {
        perror("Error opening source file");
        return 1;
    }

    fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest == -1)
    {
        perror("Error opening/creating destination file");
        close(fd_src);
        return 1;
    }

    while ((rbytes = read(fd_src, buffer, BUFSIZE)) > 0)
    {
        wbytes = write(fd_dest, buffer, rbytes);
        if (wbytes == -1)
        {
            perror("Error writing to destination file");
            close(fd_src);
            close(fd_dest);
            return 1;
        }
    }

    if (rbytes == -1)
        perror("Error reading source file");

    printf("File copied successfully.\n");

    close(fd_src);
    close(fd_dest);

    return 0;
}
