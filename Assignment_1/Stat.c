#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main()
{
    char filename[100];
    struct stat info;

    printf("Enter file name: ");
    scanf("%s",filename);

    if (stat(filename,&info) == -1)
    {
        perror("stat failed");
        return 1;
    }

    printf("File Information");

    if (S_ISREG(info.st_mode))
    {
        printf("File Type : Regular File\n");
    }
    else if (S_ISDIR(info.st_mode))
    {
        printf("File Type : Directory\n");
    }
    else if (S_ISLNK(info.st_mode))
    {
        printf("File Type : Symbolic Link\n");
    }
    else
    {
        printf("File Type : Other\n");
    }

    printf("Inode Number : %lu\n", info.st_ino);
    printf("File Size : %ld bytes\n", info.st_size);
    printf("Hard Links : %lu\n", info.st_nlink);
    printf("Owner UID : %u\n", info.st_uid);
    printf("Group GID : %u\n", info.st_gid);

    printf("Permissions : ");
    printf( (info.st_mode & S_IRUSR) ? "r" : "-");
    printf( (info.st_mode & S_IWUSR) ? "w" : "-");
    printf( (info.st_mode & S_IXUSR) ? "x" : "-");
    printf( (info.st_mode & S_IRGRP) ? "r" : "-");
    printf( (info.st_mode & S_IWGRP) ? "w" : "-");
    printf( (info.st_mode & S_IXGRP) ? "x" : "-");
    printf( (info.st_mode & S_IROTH) ? "r" : "-");
    printf( (info.st_mode & S_IWOTH) ? "w" : "-");
    printf( (info.st_mode & S_IXOTH) ? "x\n" : "-\n");

    printf("Last Access : %s",ctime(&info.st_atime));

    printf("Last Modified : %s",ctime(&info.st_mtime));

    return 0;
}
