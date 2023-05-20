#include "shell.h"

/**
 * void handle_exit(char *command)
{

	char *status_str = my_strtok(NULL, " ");
	int status = 0;
	
	if (command != NULL) {
		status = atoi(command);
	}
	else if (status_str != NULL)
	{
        	status = atoi(status_str);
        	exit(status);
	}
	else{
	exit(EXIT_SUCCESS);
    }
}
*/

void handle_exit(char *cmd) {
    // Trim leading and trailing whitespaces from the command
    char *trimmed_cmd = trim_whitespace(cmd);

    // Check if an exit status is provided
    if (strlen(trimmed_cmd) > 4) {
        int status = atoi(trimmed_cmd + 4);
        exit(status);
    } else {
        exit(0);
    }
}
