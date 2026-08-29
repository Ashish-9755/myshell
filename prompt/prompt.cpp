#include "prompt.h"
#include<stdio.h>
#include<unistd.h>
#include<pwd.h>
#include<string.h>


void print_prompt (char* home)
{
    //get username
    uid_t uid = getuid();

    struct passwd* user = getpwuid(uid);
    if(user==nullptr)
    {
        perror("username");
        return;
    }

    //get hostname
    char host_name[1024];
    if(gethostname(host_name,sizeof(host_name))==-1)
    {
        perror("hostname");
        return;
    }

    //get current working directory
    char cwd[2000];
    if(getcwd(cwd,sizeof(cwd))==nullptr)
    {
         perror("cwd");
        return;
    }

    //print the prompt

    printf("%s @ %s : ",user->pw_name,host_name);

    if(strcmp(cwd,home)==0)
    {
        printf("~ >");
    }

    else if(strlen(cwd)>strlen(home) && strncmp(cwd,home,strlen(home))==0 && cwd[strlen(home)]=='/')
    {
        printf("~%s >",cwd + strlen(home));
    }
    
    else
    {
        printf("%s >",cwd);
    }

    return;
    
}