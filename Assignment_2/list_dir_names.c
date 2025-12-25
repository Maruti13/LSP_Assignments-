#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main()
{
    char dirname[200];
    DIR *dp;
    struct dirent *entry;

    printf("Enter directory name : ");
    scanf("%s",dirname);

    dp = opendir(dirname);

    if (dp == NULL)
    {
        perror("Unable to open directory");
        return 1;
    }

    printf("Directory Entries : \n");

    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        printf("%s\n",entry->d_name);
    }
    closedir(dp);
    return 0;
}
