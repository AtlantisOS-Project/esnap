/*
 * install_repo_package.c
 *
 * (C) Copyright 2025 AtlantisOS Project
 * by @NachtsternBuild
 *
 * License: GNU GENERAL PUBLIC LICENSE Version 3
 *
 * Install the package from the repo annd check for installed packages
 */
 
#include "esnap.h"

// install repo package
void install_repo_package(Package *pkg) 
{
    char cmd[MAX_CMD_LEN];
    char cmd_text[MAX_CMD_LEN];

    if (strstr(pkg->source, ".snap")) 
    {
        snprintf(cmd, sizeof(cmd), "curl -L -o /tmp/%s.snap %s", pkg->name, pkg->source);
        snprintf(cmd_text, sizeof(cmd_text), "Downloading %s from repo...", pkg->name);
        run_with_spinner(cmd, cmd_text);

        if (!verify_snap(pkg)) 
        {
            fprintf(stderr, "Verification failed. Use --no-verify to skip.\n");
            return;
        }

        snprintf(cmd, sizeof(cmd), "snap install /tmp/%s.snap --dangerous %s", pkg->name, pkg->classic ? "--classic" : "");
        snprintf(cmd_text, sizeof(cmd_text), "Installing %s...", pkg->name);
        run_with_spinner(cmd, cmd_text);
    } 
    
    // TODO: rework this for repo list or remove it
    /*
    else 
    {
        snprintf(cmd, sizeof(cmd), "snap install %s --channel=%s", pkg->name, pkg->source);
        snprintf(cmd_text, sizeof(cmd_text), "Installing %s from repo channel...", pkg->name);
        run_with_spinner(cmd, cmd_text);
    }
    */
}

// check if the snap is installed and get the version
int is_snap_installed(const char *name, char *version, size_t len)
{
    char cmd[MAX_CMD_LEN];
    snprintf(cmd, sizeof(cmd), "snap list %s | awk 'NR==2{print $2}'", name);
    
    FILE *fp = popen(cmd, "r");
    if (!fp) 
    {
    	return 0;
    }
    
    if (!fgets(version, len, fp))
    { 
    	pclose(fp); 
    	return 0; 
    }
    
    version[strcspn(version, "\n")] = 0;
    pclose(fp);
    return 1;
}

