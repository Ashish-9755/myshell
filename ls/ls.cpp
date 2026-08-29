#include "ls.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include<pwd.h>
#include <grp.h>
#include<unistd.h>
#include<ctime>

struct input_info
{
    bool show_hidden;
    bool show_long;
    char *folders[100];
};

void print_long(struct stat info,char* filename)
{
    if (S_ISDIR(info.st_mode))
    printf("d");
    else
    printf("-");

    if(info.st_mode & S_IRUSR)
    printf("r");
    else printf("-");

    if(info.st_mode & S_IWUSR)
    printf("w");
    else printf("-");

    if(info.st_mode & S_IXUSR)
    printf("x");
    else printf("-");

    if(info.st_mode & S_IRGRP)
    printf("r");
    else printf("-");

    if(info.st_mode & S_IWGRP)
    printf("w");
    else printf("-");

    if(info.st_mode & S_IXGRP)
    printf("x");
    else printf("-");

     if(info.st_mode & S_IROTH)
    printf("r");
    else printf("-");

    if(info.st_mode & S_IWOTH)
    printf("w");
    else printf("-");

    if(info.st_mode & S_IXOTH)
    printf("x");
    else printf("-");

    printf(" %lld",(long long)info.st_nlink);

    uid_t uid = info.st_uid;
    struct passwd* user = getpwuid(uid);
    printf(" %s",user->pw_name);

    gid_t gid = info.st_gid;
    struct group *grp = getgrgid(info.st_gid);
    printf(" %s",grp->gr_name);

    printf(" %lld",info.st_size);

    struct tm* time = localtime(&info.st_mtime);
    char time_buffer[100];
    strftime(time_buffer,sizeof(time_buffer),"%b %d %H:%M",time);
    printf(" %s", time_buffer);

    printf(" %s\n",filename);

}

void long_entry(DIR *dir,char* path,bool a)
{
    struct dirent *read = readdir(dir);

    while (true)
    {
        if (read == NULL)
            break;

        if (!(a) && read->d_name[0] == '.')
        {
            read = readdir(dir);
            continue;
        }
        char full_path[2000];
        snprintf(full_path,sizeof(full_path),"%s/%s",path,read->d_name);

        struct stat info;
        if(stat(full_path,&info)==-1)
        {
            perror("stat");
            read = readdir(dir);
            continue;
        }
        print_long(info,read->d_name);
        read = readdir(dir);
    }
    return;
}

void print_entry(DIR *dir, bool a)
{
    struct dirent *read = readdir(dir);
    while (true)
    {
        if (read == NULL)
            break;

        if (!(a) && read->d_name[0] == '.')
        {
            read = readdir(dir);
            continue;
        }

        printf("%s\n", read->d_name);

        read = readdir(dir);
    }
    return;
}

void list_directories(struct input_info in, int total_folders)
{
    if (total_folders == 0)
    {
        DIR *open = opendir(".");
        if (open == NULL)
        {
            perror("opendir");
            return;
        }
        if(!in.show_long)
        print_entry(open, in.show_hidden);

        else
        {
            char path[2000];
            if(getcwd(path,sizeof(path))==NULL)
            {
                perror("cwd");
                return;
            }
            long_entry(open,path,in.show_hidden);
        }

        closedir(open);
        return;
    }

    int i{0};
    while (i < total_folders)
    {
        DIR *open = opendir(in.folders[i]);
        if (open == NULL)
        {
            perror("opendir");
            i++;
            continue;
        }
        if(!in.show_long)
        print_entry(open,in.show_hidden);

        else
        long_entry(open,in.folders[i],in.show_hidden);

        closedir(open);
        i++;
    }
}

void parse_input(char *input)
{
    struct input_info in = {false, false, {}};

    int no_of_folders = 0;

    while (input != NULL)
    {
        if (input[0] == '-')
        {
            int i = 1;
            while (input[i] != '\0')
            {
                if (input[i] == 'a')
                    in.show_hidden = true;

                else if (input[i] == 'l')
                    in.show_long = true;
                i++;
            }
        }

        else
        {
            in.folders[no_of_folders] = input;
            no_of_folders++;
        }

        input = strtok(NULL, " \t\n");
    }

    list_directories(in, no_of_folders);
    return;
}

void main_ls(char *input)
{
    parse_input(input);
}
