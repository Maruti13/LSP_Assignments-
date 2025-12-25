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

    off_t max_size = -1;
    char largest_file[256] = "";

    printf("Enter directory name : ");
    scanf("%s",dirname);

    dp = opendir(dirname);

    if (dp == NULL)
    {
        perror("Unable to open directory");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        snprintf(path, sizeof(path), "%s/%s",dirname,entry->d_name);

        if (lstat(path, &info) == -1)
        {
            perror("lstat failed");
            continue;
        }

        if (S_ISREG(info.st_mode))
        {
            if (info.st_size > max_size)
            {
                max_size = info.st_size;
                strcpy(largest_file, entry->d_name);
            }
        }
    }

    closedir(dp);

    if (max_size == -1)
    {
        printf("No regular files found in directory\n");
    }
    else
    {
        printf("\nLargest File : %s\n",largest_file);
        printf("Size : %ld bytes\n",(long)max_size);
    }

    return 0;
}
