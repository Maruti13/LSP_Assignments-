#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char filename[100];
    char text[500];
    int fd;
    int bytes_written;

    printf("Enter file name : ");
    scanf("%s",filename);

    getchar();

    printf("Enter string to write in file : ");
    fgets(text, sizeof(text), stdin);

    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    bytes_written = write(fd,text,strlen(text));

    if (bytes_written == -1)
    {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    printf("String written successfully.\n");
    printf("Total bytes written : %d\n", bytes_written);

    close(fd);
    return 0;
}
