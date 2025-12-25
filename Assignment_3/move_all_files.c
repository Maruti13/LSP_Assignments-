#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 4096

int copy_and_delete(const char *src, const char *dest)
{
    int fd_src, fd_dest;
    char buf[BUFSIZE];
    ssize_t rbytes, wbytes;

    fd_src = open(src, O_RDONLY);
    if (fd_src == -1)
    {
        perror("open src failed");
        return -1;
    }

    fd_dest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest == -1)
    {
        perror("open dest failed");
        close(fd_src);
        return -1;
    }

    while ((rbytes = read(fd_src, buf, BUFSIZE)) > 0)
    {
        wbytes = write(fd_dest, buf, rbytes);
        if (wbytes == -1)
        {
            perror("write failed");
            close(fd_src);
            close(fd_dest);
            return -1;
        }
    }

    close(fd_src);
    close(fd_dest);

    if (unlink(src) == -1)
    {
        perror("unlink failed");
        return -1;
    }

    return 0;
}

int main()
{
    char srcdir[300], dstdir[300];
    DIR *dp;
    struct dirent *entry;
    struct stat info;
    char srcpath[500], dstpath[500];
    int moved = 0;

    printf("Enter source directory : ");
    scanf("%s",srcdir);

    printf("Enter destination directory : ");
    scanf("%s",dstdir);

    dp = opendir(srcdir);
    if (dp == NULL)
    {
        perror("Unable to open source directory");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(srcpath, sizeof(srcpath), "%s/%s", srcdir, entry->d_name);
        snprintf(dstpath, sizeof(dstpath), "%s/%s", dstdir, entry->d_name);

        if (lstat(srcpath, &info) == -1)
        {
            perror("lstat failed");
            continue;
        }

        if (!S_ISREG(info.st_mode))
            continue;

        if (rename(srcpath, dstpath) == 0)
        {
            moved++;
            continue;
        }

        if (copy_and_delete(srcpath, dstpath) == 0)
        {
            moved++;
        }
    }

    closedir(dp);

    printf("Total files moved: %d\n", moved);

    return 0;
}
