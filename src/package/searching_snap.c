/*
 * searching_snap.c
 *
 * (C) Copyright 2025 AtlantisOS Project
 * by @NachtsternBuild
 *
 * License: GNU GENERAL PUBLIC LICENSE Version 3
 *
 * Searching for snaps with/without snap store
 */
 
#include "esnap.h"

// searching for a snap package
void search_package(const char *name)
{
    if (use_repo && package_count > 0)
    {
        for (int i=0;i<package_count; i++)
        {
            if (strcasestr(packages[i].name, name))
            {
                printf("%s (repo: %s)\n", packages[i].name, packages[i].source);
            }
        }
    }
    
    if (!no_fallback)
    {
        char cmd[MAX_CMD_LEN];
        char cmd_text[MAX_CMD_LEN];
        snprintf(cmd, sizeof(cmd), "snap find %s", name);
        snprintf(cmd_text, sizeof(cmd_text), "Finding %s snap...", name);
        run_with_spinner(cmd, cmd_text);
    }
}
