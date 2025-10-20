/*
 * run_to_snap.c
 *
 * (C) Copyright 2025 AtlantisOS Project
 * by @NachtsternBuild
 *
 * License: GNU GENERAL PUBLIC LICENSE Version 3
 *
 * Run a esnap command to snap
 */
 
#include "esnap.h"

// run a command from esnap to snap
void run_to_snap(int number, char *arguments[])
{
	if (number > 1)
	{
		#define PREFIX_LEN 10 
        
        char snap_cmd[MAX_CMD_LEN];
        
        // use 'snap' at the start of all commands
        strncpy(snap_cmd, "snap", MAX_CMD_LEN - 1);
        snap_cmd[MAX_CMD_LEN - 1] = '\0'; // ensure that the string is terminated.

        // adding all arguments
        for (int i = 1; i < number; i++)
        {
            // add free space for more arguments
            // check for possible buffer overflow
            if (strlen(snap_cmd) + 1 + strlen(arguments[i]) >= MAX_CMD_LEN)
            {
                fprintf(stderr, "Error: Command too long, argument ‘%s’ truncated.\n", arguments[i]);
                break; // Break the loop to prevent overflow
            }
            
            strcat(snap_cmd, " "); // add free space
            strcat(snap_cmd, arguments[i]); // add arguments
        }
        
        char snap_cmd_text[PREFIX_LEN + MAX_CMD_LEN]; 
        
        snprintf(snap_cmd_text, sizeof(snap_cmd_text), "Running: %s", snap_cmd);
        
        // run the command
        run_with_spinner(snap_cmd, snap_cmd_text);	
	}
	
	else
	{
		fprintf(stderr, "Not enough arguments can be passed to Snap.\n");
        return;
    }
}

