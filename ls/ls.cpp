#include "ls.h"
#include <stdio.h>
#include <dirent.h>

void ls()
{
    DIR *curr_dir = opendir(".");

    if (curr_dir == nullptr)
    {
        perror("ls");
        return;
    }

    struct dirent *read_entry;
    while (true)
    {
        read_entry = readdir(curr_dir);

        // break if eof or any error
        if (read_entry == NULL)
            break;

        // skip the hidden files
        if (read_entry->d_name[0] == '.')
            continue;

        printf("%s\n", read_entry->d_name);
    }

    if (closedir(curr_dir) == -1)
    {
        perror("closedir");
        return;
    }
}

