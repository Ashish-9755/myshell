#include "pinfo.h"
#include<limits.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

void pinfo(pid_t pid)
{	
	char path[300];
	snprintf(path,sizeof(path),"/proc/%d/status",pid);

	int fd = open(path,O_RDONLY);
	if(fd==-1)
	{
		perror("open");
		return;
	}

	char buffer[4096];
	ssize_t readbytes = read(fd,buffer,sizeof(buffer));
	if(readbytes==-1)
	{
		perror("read");
		close(fd);
		return;
	}
	
	buffer[readbytes]='\0';

	char* line = strtok(buffer,"\n");

	while(line!=NULL)
	{
		if(strncmp(line,"State:",6)==0)
		{
			printf("%s\n",line);
		}

		if(strncmp(line,"VmSize:",7)==0)
		{
			printf("%s\n",line);
		}

		line = strtok(NULL,"\n");
	}

	char exe_path[PATH_MAX];
	snprintf(exe_path,sizeof(exe_path),"/proc/%d/exe",pid);

	char actual_path[PATH_MAX];
	ssize_t len = readlink(exe_path,actual_path,sizeof(actual_path)-1);

	if(len==-1)
	{
		perror("readlink");
		return;
	}

	actual_path[len] = '\0';
	printf("Executable Path: %s\n",actual_path);
}
