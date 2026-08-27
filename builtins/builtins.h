#ifndef BUILTINS_H
#define BUILTINS_H

void pwd();
void change_dir(const char* path,const char* home,char* prev);
void echo(char* input);

#endif