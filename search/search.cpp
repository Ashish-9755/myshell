#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <cstring>
#include <sys/stat.h>

bool search(const char *path,const char *cwd)
{
    DIR *dir = opendir(cwd);
    if (dir == NULL)
    {
        perror("opendir");
        return false;
    }
    struct dirent *redir;
    while ((redir = readdir(dir)) != NULL)
    {
        if (strcmp(redir->d_name, ".") == 0 ||strcmp(redir->d_name, "..") == 0)
        {
            redir = readdir(dir);
            continue;
        }

        char full_path[2000];
        snprintf(full_path, sizeof(full_path), "%s/%s", cwd, redir->d_name);
        struct stat info;
        if (stat(full_path, &info) == -1)
        {
            perror("stat");
            continue;
        }

        if (strcmp(redir->d_name, path) == 0)
        {
            closedir(dir);
            return true;
        }

        if (S_ISDIR(info.st_mode))
        {
            if(search(path, full_path))
            {
                closedir(dir);
                return true;
            }
        }
    }

    closedir(dir);
    return false;
}