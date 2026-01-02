/*
 Assignment 4
 Question 2 : File copy with offset
 Usage : ./a.out source_file destination_file offset
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
    int fd_src, fd_dest;
    off_t offset;
    char buffer[BUFSIZE];
    ssize_t rbytes, wbytes;

    if (argc != 4)
    {
        printf("Usage:%s<source_file> <destination_file> <offset>\n",argv[0]);
        return 1;
    }

    offset = atoll(argv[3]);   // convert string to number

    fd_src = open(argv[1], O_RDONLY);
    if (fd_src == -1)
    {
        perror("Error opening source file");
        return 1;
    }

    if (lseek(fd_src, offset, SEEK_SET) == -1)
    {
        perror("Error seeking to offset");
        close(fd_src);
        return 1;
    }

    // open/create destination file
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
            perror("Error writing to destination");
            close(fd_src);
            close(fd_dest);
            return 1;
        }
    }

    if (rbytes == -1)
        perror("Error reading source file");

    printf("File copied from offset %ld successfully\n", (long)offset);

    close(fd_src);
    close(fd_dest);

    return 0;
}
