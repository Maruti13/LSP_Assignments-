/*
 Assignment 4
 Question 3 : Copy using pread() and pwrite() without changing file offset
 Usage : ./a.out source_file destination_file
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
    int fd_src, fd_dest;
    char buffer[BUFSIZE];
    ssize_t rbytes, wbytes;
    off_t offset = 0;

    if (argc != 3)
    {
        printf("Usage:%s<source_file> <destination_file>\n",argv[0]);
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

    while ((rbytes = pread(fd_src, buffer, BUFSIZE, offset)) > 0)
    {
        wbytes = pwrite(fd_dest, buffer, rbytes, offset);

        if (wbytes == -1)
        {
            perror("Error writing using pwrite");
            close(fd_src);
            close(fd_dest);
            return 1;
        }

        offset += rbytes;   // manually update logical offset
    }

    if (rbytes == -1)
        perror("Error reading using pread");

    printf("File copied successfully using pread() and pwrite().\n");

    close(fd_src);
    close(fd_dest);

    return 0;
}
