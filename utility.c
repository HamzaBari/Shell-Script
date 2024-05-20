#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <unistd.h>
#include <errno.h>
#include <sys/times.h>
#include "myshell.h"

void commandCd() {

	char * mainMenu;
	
	mainMenu = getenv("Main Menu");

	//Getting the name of the directory. 
	get = strtok(NULL, " \t\n()<>|&;");

	//Allowing the empty "cd" command to be used for moving to the home directory.
	if (get == NULL) {

		if (mainMenu == NULL){
			printf("ERROR: the command line isn't going to work as there is no set variables.\n");
			return;
		}

		//On this error -1 it returns an error message.
		if (chdir (mainMenu) == -1) {
			perror("ERROR: this cannot work.");
		}
		return;
	}

	//Allowing'-' to cd relative for the home directory.
	if (get[0] == '-') {	

		if (mainMenu == NULL) {
			printf("ERROR: the command line isn't going to work as there is no set variables.\n");
			return;
		}

		char rel[500];
		strcpy(rel, mainMenu);
		get = strcat(rel, &get[1]);
	}

	//On this error -1 it returns an error message.
	if (chdir (get) == -1) {
		perror("ERROR: this cannot work.");
	}
	
}

//This clears the terminal screen.
void commandClr() {
	system("clear");
}

//This lists all the directory's which exist in the system.
void commandDir() {
	system("ls -l");
}

//This gets an input from the user and outputs it onto the terminal. 
void commandEcho() {
	//The variable is set to 100 characters/
	char text[100];
	
	//This gets the input from the user.
	fgets(text, 100, stdin);
	
	//This prints the text entered by the user onto the system.
	printf(text);
}

//This lists all the environmental strings in the system.
void commandEnviron() {
	system("env");
}

//This is used for displaying the help for the users on the system.
void commandHelp() {

	FILE * helpFile;
	
	//The limit of characters in the help manual.
	char characters[6050];	
	
	//Identifies the path where the help maunal is located.
	helpFile = fopen("/home/satstudent/OperatingSystemsCW1/readme", "r");


	if (helpFile != NULL) {

		//This loop would run util the file reches the end.
		while (!feof (helpFile)) {

			// gets all the characters from the help maunal
			fgets(characters, 6050, helpFile);
			
			//Prints the content of the file onto the terminal.
			printf("%s", characters);

		}

		fclose(helpFile);

		} else {

			//returns error message of the file is not recognized. 
			printf("Cannot open the file.\n");
		}

}

//This is used to pause the system.
void commandPause() {
	puts("Press enter to continue...");
	system("read");
}


void redirectOutput(char flag) {
	
	pid_t pid;
	char * args[BUFFER_LINE];
	int argumentNo;
	FILE * filePath;
	int currentState;

	currentState = 0;
	argumentNo = 0;
	pid = fork();

	//Error with forking.
	if (pid == -1) {
		perror("ERROR: unable to fork.");
		exit(EXIT_FAILURE);
	} 

	//The child processes
	else if (pid == 0) {

		args[argumentNo] = get;

		do 
		{
			//These are the symbols for the redirection.
			get = strtok(NULL, " \t\n()<>|&;");
			++argumentNo;
			args[argumentNo] = get;

		} while (get != NULL);

		//&flag should be the name of the file, redirect output
		filePath = freopen(args[argumentNo - 1], &flag, stdout);
	
		if (filePath == NULL) { //if there is an error with the file path.
			perror("ERROR: could not find.");
			return;
		}

		args[argumentNo - 1] = NULL;

		//Running the program which has been specified. 
		if (execvp (args[0], args) == -1) {
			perror("ERROR: unable to run the program.");
		}

		fclose(filePath); //closes the file.
		exit(EXIT_FAILURE); //exit on failure
		
	}

	//The Parent processes
	else {
		if (main (&currentState) == -1) {
			perror("ERROR: unable to process.");
			return;
		}

		//Checking the status for exiting.
		if (WIFEXITED (currentState) == 0) {
			printf("ERROR: This process is not exiting.");
		}
	}
}


void runningShell() {

	pid_t pid;
	char * args[BUFFER_LINE];
	int argumentNo;
	FILE * filePath;
	int currentState;

	currentState = 0;
	argumentNo = 0;
	pid = fork();

	//Error with forking.
	if (pid == -1) {
		perror("ERROR: unable to fork.");
		exit(EXIT_FAILURE);
	} 

	//The child process.
	else if (pid == 0) {

		args[argumentNo] = get;

		do 
		{
			
			get = strtok(NULL, " \t\n()<>|&;");
			++argumentNo;
			args[argumentNo] = get;

		} while (get != NULL);


		//Running the program which has been specified. 
		if (execvp (args[0], args) == -1) {
			perror("ERROR: unable to run the program.");
		}

		exit(EXIT_SUCCESS);
		
	}

	//The parent process
	else {
		
		if (main (&currentState) == -1) {
			perror("ERROR: unable to process.");
			return;
		}

		//Checking the status for exiting.
		if (WIFEXITED (currentState) == 0) {
			printf("ERROR: This process is not exiting.");
		}
	}
}