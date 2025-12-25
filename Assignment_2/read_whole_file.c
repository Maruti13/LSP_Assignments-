#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

int main()
{
    char filename[100];
    int fd;
    char buffer[BUFSIZE];
    int bytes_read;
    int total = 0;

    printf("Enter file name: ");
    scanf("%s",filename);

    fd = open(filename,O_RDONLY);

    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    printf("File Content\n");

    while ((bytes_read = read(fd,buffer,BUFSIZE)) > 0)
    {
        write(1,buffer,bytes_read); 
        total += bytes_read;
    }

    if (bytes_read == -1)
    {
        perror("Error reading file");
        close(fd);
        return 1;
    }

    printf("\n\nTotal bytes read: %d\n",total);

    close(fd);
    return 0;
}
