#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char filename[100];
    int n, fd;
    char *buffer;
    int bytes_read;

    printf("Enter file name: ");
    scanf("%s", filename);

    printf("Enter number of bytes to read: ");
    scanf("%d", &n);

    buffer = (char *)malloc(n + 1);

    fd = open(filename, O_RDONLY);

    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    bytes_read = read(fd, buffer, n);

    if (bytes_read == -1)
    {
        perror("Error reading file");
        close(fd);
        return 1;
    }

    buffer[bytes_read] = '\0';   

    printf("\nData read from file:\n");
    printf("%s\n", buffer);

    printf("\nTotal bytes read: %d\n", bytes_read);

    free(buffer);
    close(fd);

    return 0;
}
