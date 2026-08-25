#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include "builtins.h"

void pwd()
{
    char cwd[4000];
    if(getcwd(cwd,sizeof(cwd))==nullptr)
    {
        perror("cwd");
        return;
    }

    printf("%s\n", cwd);
}


void change_dir(char* path,char* home)
{
   if(path==nullptr)
   {
        if(chdir(home)==-1)
        {
            perror("chdir");
        }
        return;
   }

    if(chdir(path)==-1)
    {
        perror("chdir");
    }

}

