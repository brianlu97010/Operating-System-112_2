#include <lib.h>
#include <unistd.h>
#include <sys/cdefs.h>
#include "namespace.h"

#include <string.h>
#include <sys/stat.h>

int printmsg(){
    message m;
    return(_syscall(PM_PROC_NR, PM_PRINTMSG, &m)); 
}