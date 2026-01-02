/*
 Assignment 5
 Question 3 : Create dir_report.c that recursively calculates :
              a] Total number of files
              b] Total number of directories
              c] Total size of file(bytes)
              d] Largest file name + size
              e] Count of file when you enter it 
              f] For size : consider only S_ISREG
              g] Ignore symlink target size(treat symlink as link object, don't follow)
*/

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

long total_files = 0;
long total_dirs = 0;
long long total_size = 0;

char largest_file[512] = "";
off_t largest_size = 0;

void dir_report(const char *path)
{
    DIR *dp;
    struct dirent *entry;
    struct stat info;
    char newpath[512];

    dp = opendir(path);
    if (!dp)
    {
        perror("opendir failed");
        return;
    }

    total_dirs++;   // count directory when entered

    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(newpath, sizeof(newpath), "%s/%s", path, entry->d_name);

        if (lstat(newpath, &info) == -1)
        {
            perror("lstat failed");
            continue;
        }

        // regular file
        if (S_ISREG(info.st_mode))
        {
            total_files++;
            total_size += info.st_size;

            if (info.st_size > largest_size)
            {
                largest_size = info.st_size;
                strcpy(largest_file, newpath);
            }
        }
        // directory 
        else if (S_ISDIR(info.st_mode))
        {
            dir_report(newpath);
        }
        // symbolic link 
        else if (S_ISLNK(info.st_mode))
        {
            // ignore size of target
            continue;
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    dir_report(argv[1]);

    printf("\nFiles : %ld\n", total_files);
    printf("Dirs  : %ld\n", total_dirs);
    printf("Total Size: %lld bytes\n", total_size);

    if (largest_size > 0)
        printf("Largest: %s (%ld bytes)\n", largest_file, (long)largest_size);
    else
        printf("Largest: (no regular files found)\n");

    return 0;
}
