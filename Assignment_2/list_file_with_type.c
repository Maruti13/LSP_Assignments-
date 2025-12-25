#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    char dirname[200];
    DIR *dp;
    struct dirent *entry;
    struct stat info;
    char path[400];

    printf("Enter directory name : ");
    scanf("%s",dirname);

    dp = opendir(dirname);

    if (dp == NULL)
    {
        perror("Unable to open directory");
        return 1;
    }

    printf("Files with Type : \n");

    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path,sizeof(path),"%s/%s",dirname,entry->d_name);

        if (lstat(path,&info) == -1)
        {
            perror("lstat failed");
            continue;
        }

        printf("%-25s : ",entry->d_name);

        if (S_ISREG(info.st_mode))
        {
            printf("Regular File\n");
        }
        else if (S_ISDIR(info.st_mode))
        {
            printf("Directory\n");
        }
        else if (S_ISLNK(info.st_mode))
        {
            printf("Symbolic Link\n");
        }
        else if (S_ISCHR(info.st_mode))
        {
            printf("Character Device\n");
        }
        else if (S_ISBLK(info.st_mode))
        {
            printf("Block Device\n");
        }
        else if (S_ISFIFO(info.st_mode))
        {
            printf("FIFO (Named Pipe)\n");
        }
        else if (S_ISSOCK(info.st_mode))
        {
            printf("Socket\n");
        }
        else
        {
            printf("Other\n");
        }
    }

    closedir(dp);
    return 0;
}
