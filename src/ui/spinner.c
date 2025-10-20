/*
 * spinner.c
 *
 * (C) Copyright 2025 AtlantisOS Project
 * by @NachtsternBuild
 *
 * License: GNU GENERAL PUBLIC LICENSE Version 3
 *
 * little spinner in the terminal for esnap 
 */
 
#include "esnap.h"
 
// define colors and spinner details
const char *cols[] = {
    "\x1b[38;5;159m",
    "\x1b[38;5;175m",
    "\x1b[38;5;180m",
    "\x1b[38;5;216m",
    "\x1b[38;5;157m"
};

const char *RESET = "\x1b[0m";
const char *frames[] = { "⠁","⠂","⠄","⡀","⢀","⠠","⠐","⠈" };
const int NFRAMES = sizeof(frames)/sizeof(frames[0]);
const int NCOLS   = sizeof(cols)/sizeof(cols[0]);

// function to run the spinner
void run_with_spinner(const char *cmd, const char *message) 
{
    // create tmp file
    char tmpfile[] = "/tmp/esnap_outXXXXXX";
    int fd = mkstemp(tmpfile);
    
    if (fd == -1) 
    {
        perror("mkstemp");
        return;
    }

    pid_t pid = fork();
    if (pid == 0) 
    {
        // childprocess → output to the file
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);
        execl("/bin/sh", "sh", "-c", cmd, (char *)NULL);
        _exit(127);
    }

    // parent process → show spinner
    close(fd);
    printf("\x1b[?25l"); // disable cursor
    int phase = 0;
    int status;
	
	// draw the spinner
    while (waitpid(pid, &status, WNOHANG) == 0) 
    {
        printf("\r%s %s%s%s", message, "\x1b[36m", frames[phase % NFRAMES], RESET);
        fflush(stdout);
        usleep(120000);
        phase++;
    }
    
    printf("\r%s [done]      \n", message);
    printf("\x1b[?25h"); // enable cursor

    // shwo output at the end
    FILE *fp = fopen(tmpfile, "r");
    if (fp) 
    {
        char buffer[512];
        printf("\n--- Snap Output ---\n");
        
        while (fgets(buffer, sizeof(buffer), fp)) 
        {
            fputs(buffer, stdout);
        }
        
        fclose(fp);
    }
    
    unlink(tmpfile);
}
