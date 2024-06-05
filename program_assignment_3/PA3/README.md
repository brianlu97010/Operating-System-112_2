## Intro
First, you need to follow the instuction to rebuild the system 
to add the new system call for semaphore.

Then, Test the program with `make`

## Rebuild the MINIX system
1. `mv minix /usr/src/`
2. Compiling the Server
	Steps for compiling the servers:
Go to directory /usr/src/servers/
Issue `make`
Issue `make install`

3. Compiling the Library
Steps to compile the new library
Go to the directory /usr/src/lib/
`make` 
`make install`

4. Creating a New Boot-Image Using the Updated Servers and Library
Rebuilding the Kernel Only
`cd /usr/src/releasetools`  
`make hdboot`
`cp /usr/sbin/kernel /boot/minix_latest/kernel`
`reboot`

## Test the program
`cd PA3`
Issue `make run`
