/*
 Assignment 4
 Question 4 : File Merge Utility
 Usage : ./a.out dest_file src1 src2 src3 ...
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
    int fd_dest, fd_src;
    char buffer[BUFSIZE];
    ssize_t rbytes, wbytes;
    int i;

    if (argc < 3)
    {
        printf("Usage:%s<destination_file> <source1> <source2> ...\n",argv[0]);
        return 1;
    }

    fd_dest = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd_dest == -1)
    {
        perror("Error opening/creating destination file");
        return 1;
    }

    for (i = 2; i < argc; i++)
    {
        fd_src = open(argv[i], O_RDONLY);
        if (fd_src == -1)
        {
            perror("Error opening source file");
            continue;             
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

        close(fd_src);
    }

    printf("All files merged successfully into %s\n", argv[1]);

    close(fd_dest);
    return 0;
}
