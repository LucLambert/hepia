#ifndef REC_H_
#define REC_H_
    #include <stdbool.h>
    void browse_rec(char* name, char* to, short param,void (*f)(char*,char*,short));
    bool isDir(char* name);
#endif