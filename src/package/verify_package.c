/*
 * verify_package.c
 *
 * (C) Copyright 2025 AtlantisOS Project
 * by @NachtsternBuild
 *
 * License: GNU GENERAL PUBLIC LICENSE Version 3
 *
 * Verify the snap package
 */
 
#include "esnap.h"

// verify the snap package
int verify_snap(Package *pkg) 
{
    if (no_verify) 
    {
    	return 1;
    }
	
	// sha256 checksum
    if (pkg->checksum[0]) 
    {
        char cmd[MAX_CMD_LEN];
        snprintf(cmd, sizeof(cmd), "sha256sum /tmp/%s.snap | grep -q '%s'", pkg->name, pkg->checksum);
        
        if (system(cmd) != 0)
        {
            fprintf(stderr,"Checksum verification failed for %s\n",pkg->name);
            return 0;
        }
    }
    
    // gpg signature
    if (pkg->signature[0]) 
    {
        char cmd[MAX_CMD_LEN];
        snprintf(cmd, sizeof(cmd), "gpg --verify %s /tmp/%s.snap", pkg->signature, pkg->name);
        
        if (system(cmd) != 0)
        {
            fprintf(stderr,"Signature verification failed for %s\n", pkg->name);
            return 0;
        }
    }
    return 1;
}

