#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "command.h"  

// define variable
char *cpath;  
int hcnt;
char msg[40][256];

int main(int argc, char **argv){
 //...
      char *username = getenv("logname");
      char wordmatrix[100][256];      // each row stores a word, and the header character of each     column is \0
      char *buf = NULL;           // create a buffer to store user's input
      buf = (char *)malloc(256);
      if (buf == NULL){           // if buffer doesnt have enough space
          perror("malloc failed");
          exit(-1);
      }
 
      while(1){
          int wordcnt = 0;        // the number of words in the command
          cpath = (char *)malloc(100);    // allocate memory space to cpath
          getcwd(cpath, 100);     // call getcwd() to get current working directory
          printf("%s@:%s $",username, cpath);
          free(cpath);
 
          memset(buf,0,256);      // set the elements in buffer to \0
         getCommand(buf, 256);
         // history
         strcpy(msg[hcnt], buf);     // copy the command into msg array
         hcnt++;

         if(strcmp(buf,"exit") == 0){    // if the command is 'exit', then break the loop
             break;
         }

         for (int i=0;i<100;i++){
             wordmatrix[i][0] = '\0';    // set the header character of each column in \0
         }

         anaCommand(buf,&wordcnt, wordmatrix);
         exeCommand(wordcnt, wordmatrix, hcnt);
     }

     // release the memory space of buffer array
     if(buf != NULL){
         free(buf);
         buf = NULL;
     }
    return 0;
}
