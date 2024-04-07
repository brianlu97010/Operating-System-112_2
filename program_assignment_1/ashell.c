#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_SIZE  256

/*	global variable		*/
char *cpath; 					// to output current path
int hcnt = 0;					// Record the numbers of command which have been entered
char msg[40][256];				// Record the command which have been entered


/* 	define function		*/
void getCommand(char*, int);			// Read the command we entered from the command line window and store the command in the buf array.
// Use the "space" to separate the commands in buf word by word, and then store them in the wordmatrix.
void anaCommand(char*, int* , char (*wordmatrix)[256]); 	
void exeCommand(int, char (*wordmatrix)[256], int);// Execute the command we parsed. 


/*	main function		*/
int main(int argc, char **argv){
//...
	char *username = getenv("logname");
	char wordmatrix[100][256];		// each row stores a word, and the header character of each column is \0
	char *buf = NULL;			// create a buffer to store user's input
	buf = (char *)malloc(256);
	if (buf == NULL){			// if buffer doesnt have enough space
		perror("malloc failed");
		exit(-1);
	}

	while(1){
		int wordcnt = 0;		// the number of words in the command
		cpath = (char *)malloc(100); 	// allocate memory space to cpath
		getcwd(cpath, 100);		// call getcwd() to get current working directory		
		printf("%s@:%s $",username, cpath);
		free(cpath);
		
		memset(buf,0,256);		// set the elements in buffer to \0 
		getCommand(buf, 256);
		// history
		strcpy(msg[hcnt], buf);		// copy the command into msg array
		hcnt++;

		if(strcmp(buf,"exit") == 0){	// if the command is 'exit', then break the loop
			break;
		}

		for (int i=0;i<100;i++){
			wordmatrix[i][0] = '\0'; 	// set the header character of each column in \0
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

/*	implement funtion	*/
// Read the command we entered from the command line window and store the command in the buf array.
void getCommand(char* buf, int size){
	if (fgets(buf,size,stdin) == NULL ){
		fprintf(stderr, "There are some mistakes when reading input");
		return;
	}

	// replace \n to \0 so that strcmp can execute successfully
	int len = strlen(buf);	
	if (len > 0 && buf[len-1]=='\n'){
		buf[len-1] = '\0';
	}
}

 
// Use the "space" to separate the commands in buf word by word, and then store them in the wordmatrix.
void anaCommand(char* buf, int *wordcnt, char(*wordmatrix)[256] ){
	char *temp;
	temp = strtok(buf, " ");
	while(temp != NULL && *wordcnt < 100){
		strcpy(wordmatrix[*wordcnt], temp);
		(*wordcnt)++;
		temp = strtok(NULL, " ");
	}

	// test code
	/*
	    for (int i = 0; i < *wordcnt; i++) {
	            printf("%d: %s\n", i, wordmatrix[i]);
		}		       
	*/
}

// Execute the command we parsed.
void exeCommand(int wordcnt, char (*wordmatrix)[256], int hcnt){
	// cd /dir/
	if( strcmp(wordmatrix[0], "cd") == 0){
		if( wordcnt != 1){
			if(chdir(wordmatrix[1])==-1 ){
				perror("cd");
			}
		}
	}
	// history n
	else if( strcmp(wordmatrix[0], "history") == 0){
		if ( wordcnt != 1){
			int t = atoi(wordmatrix[1]);

			for(int i = hcnt - t; i<hcnt; i++){
				printf("%d : %s\n", i+1, msg[i] );
			}
		}
	}
	// program commands	
	else{
		char *args[wordcnt+1];
		for(int i=0; i < wordcnt ; i++){
			args[i]=wordmatrix[i];
		}
		args[wordcnt]=NULL;
		// test code
		/*
		for(int i = 0; args[i] != NULL; i++) {
			printf("args[%d]: %s\n", i, args[i]);
		}
		*/
		
		pid_t pid = fork();
			
		if (pid == 0){ // child process
			execvp(args[0], args);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		else if(pid > 0){ //partent process
			wait(NULL);
		} 
		else{		 // fork failure
			perror("fork");
			exit(EXIT_FAILURE);
		}
	}		
}


