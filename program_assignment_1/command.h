#ifndef COMMANDS_H  // Prevent repeated introduction of header files
#define COMMANDS_H

#include <stdio.h>

#define MAX_SIZE  256  // ÂMacro definition

// declare global variable
extern char *cpath;  
extern int hcnt;
extern char msg[40][256];

// declare function
void getCommand(char*, int);
void anaCommand(char*, int* , char (*wordmatrix)[256]);
void exeCommand(int, char (*wordmatrix)[256], int);

#endif
