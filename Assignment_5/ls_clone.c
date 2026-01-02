/*
 Assignment 5
 Question 1 : Directory Traversal Basics
*/

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void print_permissions(mode_t m)
{
    printf((S_ISDIR(m)) ? "d" : (S_ISLNK(m)) ? "l" : "-");

    printf((m & S_IRUSR) ? "r" : "-");
    printf((m & S_IWUSR) ? "w" : "-");
    printf((m & S_IXUSR) ? "x" : "-");

    printf((m & S_IRGRP) ? "r" : "-");
    printf((m & S_IWGRP) ? "w" : "-");
    printf((m & S_IXGRP) ? "x" : "-");

    printf((m & S_IROTH) ? "r" : "-");
    printf((m & S_IWOTH) ? "w" : "-");
    printf((m & S_IXOTH) ? "x" : "-");
}

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *entry;
    struct stat info;
    char path[512];

    if (argc != 2)
    {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    dp = opendir(argv[1]);
    if (!dp)
    {
        perror("opendir failed");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        snprintf(path,sizeof(path), "%s/%s", argv[1], entry->d_name);

        if (lstat(path, &info) == -1)
        {
            perror("lstat failed");
            continue;
        }

        printf("%-20s ",entry->d_name);

        if (S_ISREG(info.st_mode)) printf("file  ");
        else if (S_ISDIR(info.st_mode)) printf("dir   ");
        else if (S_ISLNK(info.st_mode)) printf("link  ");
        else printf("other ");

        printf("%10ld",(long)info.st_size);

        print_permissions(info.st_mode);
        printf("  ");

        printf("%s", ctime(&info.st_mtime));
    }

    closedir(dp);
    return 0;
}
