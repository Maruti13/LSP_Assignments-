/*
 Assignment 5
 Question 2 : Recursive Directory Traversal
*/

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

void tree(const char *dirname, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat info;
    char path[512];

    dp = opendir(dirname);
    if (!dp)
    {
        perror("opendir failed");
        return;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

        if (lstat(path,&info) == -1)
        {
            perror("lstat failed");
            continue;
        }

        for (int i = 0; i < depth; i++)
            printf("    ");

        if (S_ISDIR(info.st_mode))
        {
            printf("[D] %s\n",entry->d_name);
            tree(path, depth + 1);   // recurse
        }
        else if (S_ISLNK(info.st_mode))
        {
            printf("[L] %s\n",entry->d_name);
        }
        else if (S_ISREG(info.st_mode))
        {
            printf("[F] %s\n",entry->d_name);
        }
        else
        {
            printf("[?] %s\n",entry->d_name);
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <directory>\n",argv[0]);
        return 1;
    }

    printf("%s\n",argv[1]);
    tree(argv[1], 1);

    return 0;
}
