#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "builtins.h"

void pwd()
{
    char cwd[4000];
    if (getcwd(cwd, sizeof(cwd)) == nullptr)
    {
        perror("cwd");
        return;
    }

    printf("%s\n", cwd);
}

void change_dir(char *path, char *home, char *prev)
{
    char curr[2000];
    if (getcwd(curr, sizeof(curr)) == nullptr)
    {
        perror("cwd");
        return;
    }

    if (path == nullptr)
    {
        if (chdir(home) == -1)
        {
            perror("chdir");
            return;
        }
    }

    else if (strcmp(path, "-") == 0)
    {
        if (prev[0] == '\0')
        {
            printf("no previous working directory is set\n");
            return;
        }

        else
        {
            if (chdir(prev) == -1)
            {
                perror("chdir");
                return;
            }
            printf("%s\n",prev);
        }
    }

    else if (strcmp(path, "~") == 0)
    {
        if (chdir(home) == -1)
        {
            perror("chdir");
            return;
        }
    }

    else if (chdir(path) == -1)
    {
        perror("chdir");
        return;
    }

    strcpy(prev, curr);
    return;
}
