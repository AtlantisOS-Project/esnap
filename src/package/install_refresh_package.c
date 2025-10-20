/*
 * install_refresh_packages.c
 *
 * (C) Copyright 2025 AtlantisOS Project
 * by @NachtsternBuild
 *
 * License: GNU GENERAL PUBLIC LICENSE Version 3
 *
 * Install/Update Snap packages with/without snap store
 */
 
#include "esnap.h"

// Installing packages
void install_package(const char *name) 
{
    Package *pkg = use_repo ? find_package(name) : NULL;
    char version[64];

    if (pkg) 
    {
    	install_repo_package(pkg);
    }
    
    else if (!no_fallback) 
    {
        char cmd[MAX_CMD_LEN];
        char cmd_text[MAX_CMD_LEN];
        snprintf(cmd, sizeof(cmd), "snap install %s", name);
        snprintf(cmd_text, sizeof(cmd_text), "Installing %s...", name);
        run_with_spinner(cmd, cmd_text);
        
    } 
    
    else 
    {
    	fprintf(stderr, "Package %s not found in repo and fallback disabled\n", name);
    }
}

// refresh packages
void refresh_package(const char *name, int all_flag) 
{
    if (use_repo && package_count > 0) 
    {
        for (int i = 0; i < package_count; i++)
        {
            if (all_flag || (name && strcasecmp(name, packages[i].name) == 0))
            {
                char installed_ver[64];
                int installed = is_snap_installed(packages[i].name, installed_ver, sizeof(installed_ver));
                
                if (installed && packages[i].version[0] && strcmp(installed_ver, packages[i].version) == 0)
                {
                    printf("%s is up-to-date (%s)\n", packages[i].name, installed_ver);
                }
                 
                else
                {
                	install_repo_package(&packages[i]);
                }
            }
        }
    }
    
    if (!no_fallback) 
    {
        char cmd[MAX_CMD_LEN];
        char cmd_text[MAX_CMD_LEN];
        if (all_flag || !name) 
        {
        	snprintf(cmd, sizeof(cmd), "snap refresh");
        	snprintf(cmd_text, sizeof(cmd_text), "Updating %s snap...", name);
        }
        
        else 
        {
        	snprintf(cmd, sizeof(cmd), "snap refresh %s", name);
        	snprintf(cmd_text, sizeof(cmd_text), "Updating all snaps...");
        }
        run_with_spinner(cmd, cmd_text);

    }
}
