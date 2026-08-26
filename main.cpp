#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include "prompt/prompt.h"
#include "builtins/builtins.h"

int main()
{
    char home[2000];
    char prev[2000];
    prev[0] = '\0';
    if(getcwd(home,sizeof(home))==nullptr)
    {
        perror("home");
        return 1;
    }

    while(true)
    {
        print_prompt(home);

        char input[2000];
        if(fgets(input,sizeof(input),stdin)==nullptr)
        {
            perror("input error");
            return 1;
        }

        char* cmnd = strtok(input," \t\n");

        if(cmnd==nullptr)
        {
            continue;
        }

        else if(strcmp(cmnd,"pwd")==0)
        {
            pwd();
        }

       else if(strcmp(cmnd,"cd")==0)
        {
            char* path = strtok(nullptr," \t\n");

            char* extra_argu = strtok(nullptr," \t\n");

            if(extra_argu!=nullptr)
            {
                printf("INVALID ARGUMENTS\n");
                continue;
            }

            change_dir(path,home,prev);
        }


        else if(strcmp(cmnd,"exit")==0)
        {
            break;
        }
        
    }

    printf("exit from shell");

    return 0;
}