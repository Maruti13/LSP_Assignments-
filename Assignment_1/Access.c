#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char filename[100];
    char mode[10];
    int permission_flag;

    printf("Enter file name: ");
    scanf("%s", filename);

    printf("Enter mode (read / write / execute): ");
    scanf("%s", mode);

    if (strcmp(mode, "read") == 0)
    {
        permission_flag = R_OK;
    }
    else if (strcmp(mode, "write") == 0)

    {
        permission_flag = W_OK;
    }
    else if (strcmp(mode, "execute") == 0)
    {
        permission_flag = X_OK;
    }
    else
    {
        printf("Invalid mode entered\n");
        return 1;
    }

    if (access(filename, permission_flag) == 0)
    {
        printf("Accessible: Permission GRANTED for %s\n", mode);
    }
    else
    {
        perror("Not accessible");
    }

    return 0;
}
