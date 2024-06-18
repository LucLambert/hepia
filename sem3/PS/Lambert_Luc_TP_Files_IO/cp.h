#ifndef CP_H_
#define CP_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void cp_file(char* filename, char* dest);
void cp_dir(char * dir, char * dest);
void cp(char** argv, int argc, short param);
void create_dir(char * name, mode_t mode);
bool Exist(char* name);

#endif