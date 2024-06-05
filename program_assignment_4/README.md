# README for Disk Scheduling Algorithms

## Overview
This program implements and tests several disk scheduling algorithms for a disk with 5,000 cylinders numbered 0 to 4,999. The implemented algorithms are:
- First-Come, First-Served (FCFS)
- Shortest Seek Time First (SSTF)
- SCAN
- Circular SCAN (C-SCAN)
- LOOK
- Circular LOOK (C-LOOK)
- Optimal (minimizes total head movement)

The program generates a random series of 1,000 cylinder requests and services them according to each algorithm. The initial position of the disk head is passed as a parameter on the command line, with the default starting position being 0.

## Files
- `main.c`: The main program file that tests all the disk scheduling algorithms.
- `disk_scheduling.c`: Contains the implementation of all disk scheduling algorithms.
- `disk_scheduling.h`: Header file declaring all functions and constants.
- `Makefile`: Makefile to compile, run, and clean the project.
- `README.md`: This file, describing the testing procedure.
- `design_document.md`: Design document addressing the specified questions.

## How to Compile
To compile the program, navigate to the project directory and run:
```sh
make
```

This will compile the source files and produce an executable named `disk_scheduling_demo`.

## How to Run
To run the program, use the following command:
```sh
./disk_scheduling_demo <initial_position>
```
Replace `<initial_position>` with the starting position of the disk head. For example, to start the disk head at position 0, run:
```sh
./disk_scheduling_demo 0
```

## Output
The program will output the total head movement and average latency for each of the disk scheduling algorithms. The average latency is calculated based on the assumption that moving 100 cylinders takes 1ms.

## Example 
```
./disk_scheduling_demo 0

FCFS Total Head Movement: 1671196
FCFS Average Latency: 16711.96 ms

SSTF Total Head Movement: 4999
SSTF Average Latency: 49.99 ms

SCAN Total Head Movement: 4999
SCAN Average Latency: 49.99 ms

C-SCAN Total Head Movement: 4999
C-SCAN Average Latency: 49.99 ms

LOOK Total Head Movement: 4998
LOOK Average Latency: 49.98 ms

C-LOOK Total Head Movement: 9991
C-LOOK Average Latency: 99.91 ms

Optimal Total Head Movement: 9992
Optimal Average Latency: 99.92 ms
```

## Cleaning Up
To remove the compiled files and clean the directory, run:
```sh
make clean
```

## Notes
- Make sure the initial position passed on the command line is a valid cylinder number (0-4999).
- Ensure that the generated requests and output are consistent by running the program multiple times.
