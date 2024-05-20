#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <unistd.h>
#include <errno.h>
#include <sys/times.h>

//Buffer Line
#define BUFFER_LINE 1024

//Global Variables
static char command[BUFFER_LINE]; 
static char duplicate[BUFFER_LINE];
static char * get;

//Functions for the commands, redirecting output and runningShell.
void redirectOutput(char flag);
void runningShell();
void commandCd();
void commandClr();
void commandDir();
void commandEcho();
void commandEnviron();
void commandHelp();
void commandPause();