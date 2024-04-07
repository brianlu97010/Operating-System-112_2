# OS Program Assignment 1 Design Guideline    
## Overview

### Goal
The main structure of the Shell is a `while loop`, which continuously accepts user keyboard input lines and gives feedback. The shell decomposes the input line into a word sequence and processes it separately according to the command name, namely **shell built-in commands** (such as `cd`, `history`, `exit`) and **program commands** (such as `ls`, `grep`, etc. in the /bin/ directory). 

After identifying it as a shell built-in command, perform the corresponding operation. After accepting the program command, create a new process to execute the command (by using `execvp`) and wait for the process to end. If the `&` parameter is included at the end, the shell can return directly without waiting for the process to end.
### Topic
Use the `fork` sys call to create a child process, use the `execvp` sys call to load the minix program into the process, and assign running parameters. Finally, the Shell uses `wait/waitpid` call to wait for the child process to end.
* **Implement a command with no arguments**
* **Implement a command with arguments**
* **Implement command, with or without arguments, executed in the background using &**
* **Implement a command, with or without arguments, whose output is redirected to a file**
* **Implement a command, with or without arguments, whose input is redirected from a file**

## In-depth analysis and implementation
### main function
**Goal** : Implement a while loop, when type `exit` break the loop
**Parameters** : 
`wordcount` : the number of words in the command

`wordmatrix` : A word array, each row stores a word, and the header character of each column is \0

`buf` : the buffer array that stores user's commands

### getCommand function
Read the command we entered from the command line window and store the command in the buf array. 

### anaCommand function
Use the "space" to separate the commands in buf word by word, and then store them in the wordmatrix.

### exeCommand function
Execute the command we parsed. All built-in commands and Program commands are implemented in this function.
* **built-in commands** : `cd`,`history`,`exit`
* **program commands** : `ls`,`grep`


## Risks
May have buffer overflow problems
May have memory leaking problem.

## Assignment questions
Haven't figured out how to complete  `&`,``>``,``>>``,``|`` yet. 

