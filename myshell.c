#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <unistd.h>
#include <errno.h>
#include <sys/times.h>
#include "myshell.h"
#include "utility.c"

int main(){
	
	//The declaration.
	char * redirectingPosition;

	//This loop runs to keep the shell running.
	while (1) {

		//Shell prompt.
		printf("[$HB689] - ", system("pwd"));

		//Getting an input from the user such as the commands.
		fgets(command, sizeof command, stdin);

		//Duplicating the user input.
		strcpy(duplicate, command);

		//Tokenize command
		get = strtok(command, " \t\n()<>|&;");

		//This will continue the loop even if the user skips a line and doesn't wish to enter a command.
		if (!get) {
			continue;
		}

		//If the user inputs quit then the shell will exit with 0. exit 0 exits from the running programs.
		else if (strcmp (get, "quit") == 0) {
			exit(0);
		}

		//The user can use the cd command to go back a directory or enter into a directory. 
		else if (strcmp (get, "cd") == 0) {
			commandCd(); //calling the method from utility.c
		}

		//If the user inputs the clr command then the terminal screen clears.
		else if (strcmp (get, "clr") == 0) {
			commandClr(); //calling the method from utility.c
		}

		//If the user inputs the dir command then all the directories with their information will be listed.
		else if (strcmp (get, "dir") == 0) {
			commandDir(); //calling the method from utility.c
		}

		//If the user enters echo and then the comment then it outputs the comment in the system.
		else if (strcmp (get, "echo") == 0) {
			commandEcho();	//calling the method from utility.c
		}

		//If the user enters the environ then the environmental strings will be outputted.
		else if (strcmp (get, "environ") == 0) {
			commandEnviron(); //calling the method from utility.c
		}

		//If the user enters help then the readme file content will be printed onto the terminal.
		else if (strcmp (get, "help") == 0) {
			commandHelp(); //calling the method from utility.c
		}

		//If the user presses the pause the the shell would pause and stop.
		else if (strcmp (get, "pause") == 0) {
			commandPause(); //calling the method from utility.c
		}

		//This is the output redirection, searching for the '>' sign.
		else if ((redirectingPosition = strchr(duplicate, '>'))) {
			
			//This is looking for the second '>'.
			if (* (redirectingPosition + 1) == '>') {
				redirectOutput('a');
			} else {
				redirectOutput('w');
			}
		}
		
		//Running the shell.
		else {
			runningShell();
		}
	}
	
	return 0;
}





