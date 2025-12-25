#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFSIZE 1024

int main()
{
    char src[200], dest[200];
    int fd_src, fd_dest;
    char buffer[BUFSIZE];
    int bytes_read, bytes_written;
    long total = 0;

    struct stat s;   

    printf("Enter source file name : ");
    scanf("%s",src);

    printf("Enter destination file name : ");
    scanf("%s",dest);

    fd_src = open(src,O_RDONLY);

    if (fd_src == -1)
    {
        perror("Error opening source file");
        return 1;
    }

    if (stat(src, &s) == -1)
    {
        perror("stat failed");
    }

    fd_dest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd_dest == -1)
    {
        perror("Error opening/creating destination file");
        close(fd_src);
        return 1;
    }

    while ((bytes_read = read(fd_src, buffer, BUFSIZE)) > 0)
    {
        bytes_written = write(fd_dest, buffer, bytes_read);

        if (bytes_written == -1)
        {
            perror("Error writing to destination");
            close(fd_src);
            close(fd_dest);
            return 1;
        }

        total += bytes_written;
    }

    if (bytes_read == -1)
    {
        perror("Error reading source file");
    }

    chmod(dest, s.st_mode);

    printf("Copy successful\n");
    printf("Total bytes copied: %ld\n",total);

    close(fd_src);
    close(fd_dest);

    return 0;
}
