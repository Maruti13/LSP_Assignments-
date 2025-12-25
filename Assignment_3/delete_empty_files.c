#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    char dirname[300];
    DIR *dp;
    struct dirent *entry;
    struct stat info;
    char path[500];
    int deleted = 0;

    printf("Enter directory name : ");
    scanf("%s", dirname);

    dp = opendir(dirname);
    if (dp == NULL)
    {
        perror("Unable to open directory");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name,"..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

        if (lstat(path, &info) == -1)
        {
            perror("lstat failed");
            continue;
        }

        if (!S_ISREG(info.st_mode))
            continue;

        if (info.st_size == 0)
        {
            if (unlink(path) == 0)
            {
                printf("Deleted: %s\n",entry->d_name);
                deleted++;
            }
            else
            {
                perror("Unable to delete file");
            }
        }
    }

    closedir(dp);

    printf("Total deleted files: %d\n",deleted);

    return 0;
}
