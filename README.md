# Operating-System-112_2
## Program Assignment 1
In this assignment you are to implement a Minix **shell** program.

## Program Assignment 2
The goal of this assignment is to get everyone up to speed on Minix OS and to gain some familiarity with scheduling. In this assignment you are to implement a **priority scheduler**. 
A priority scheduler assigns each process some number of lottery tickets, then randomly draws a ticket among those allocated to ready processes to decide which process to run. That process is allowed to run for a set time quantum, after which it is interrupted by a timer interrupt and the process is repeated.

## Program Assignment 3
In this assignment you will implement a producer – consumer paradigm, readers-writers, using
shared memory. First a parent process should be launched. Then it should spawn 2 children
processes. Each child process can communicate with the parent and visa-versa.

## Program Assignment 4
Write a program that implements the following disk-scheduling algorithms:
a. FCFS
b. SSTF
c. SCAN
d. C-SCAN
e. LOOK
f. CLOOK
g. Optimal (minimizes the total latency / distance the head needs to travel).
Your program will service a disk with 5,000 cylinders numbered 0 to 4,999. The
program will generate a random series of 1,000 cylinder requests and service them
according to each of the algorithms listed above. The program will be passed the initial
position of the disk head (as a parameter on the command line). You can assume the
disk head starts at 0.
Note: Disk head movement
