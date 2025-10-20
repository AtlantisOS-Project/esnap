/*
 * package.c
 *
 * (C) Copyright 2025 AtlantisOS Project
 * by @NachtsternBuild
 *
 * License: GNU GENERAL PUBLIC LICENSE Version 3
 *
 * Parsing config files and searching for packages
 */
 
#include "esnap.h"

Package packages[MAX_PACKAGES];

// loading package details from the config file
int load_packages_from_conf(const char *filename)
{
    FILE *fh = fopen(filename, "r");
    if (!fh)
    {
        fprintf(stderr, "Cannot open repo conf: %s\n", filename);
        return 0;
    }

    char line[512];
    package_count = 0;

    while (fgets(line, sizeof(line), fh))
    {
        trim_trailing_whitespace(line);
        if (line[0] == '#' || line[0] == ';' || strlen(line) < 3)
        {
            continue;
		}
		
        char *eq = strchr(line, '=');
        if (!eq)
        {
            continue;
        }

        *eq = '\0';
        char pkgname[MAX_NAME_LEN];
        char conf_url[256];
        strncpy(pkgname, line, MAX_NAME_LEN - 1);
        pkgname[MAX_NAME_LEN - 1] = '\0';
        strncpy(conf_url, eq + 1, sizeof(conf_url) - 1);
        conf_url[sizeof(conf_url) - 1] = '\0';

        trim_trailing_whitespace(pkgname);
        trim_trailing_whitespace(conf_url);

        printf("Loading package definition for %s...\n", pkgname);

        char tmp_conf[256];
        snprintf(tmp_conf, sizeof(tmp_conf), "/tmp/%s.conf", pkgname);

        char cmd[MAX_CMD_LEN];
        snprintf(cmd, sizeof(cmd), "curl -fsSL -o %s %s", tmp_conf, conf_url);
        if (system(cmd) != 0)
        {
            fprintf(stderr, "Failed to download package conf for %s\n", pkgname);
            continue;
        }

        FILE *pf = fopen(tmp_conf, "r");
        if (!pf)
        {
            fprintf(stderr, "Failed to open %s\n", tmp_conf);
            continue;
        }

        Package pkg = {0};
        strncpy(pkg.name, pkgname, sizeof(pkg.name) - 1);

        char pline[512];
        while (fgets(pline, sizeof(pline), pf))
        {
            trim_trailing_whitespace(pline);
            if (pline[0] == '#' || pline[0] == ';' || strlen(pline) < 3)
            {
                continue;
			}
			
            char *peq = strchr(pline, '=');
            if (!peq)
            {
                continue;
			}
			
            *peq = '\0';
            char key[128], val[384];
            strncpy(key, pline, sizeof(key) - 1);
            strncpy(val, peq + 1, sizeof(val) - 1);
            key[sizeof(key) - 1] = '\0';
            val[sizeof(val) - 1] = '\0';
            trim_trailing_whitespace(key);
            trim_trailing_whitespace(val);

            /* 
            * option for debugging:
            */
            // printf("Parsed key=%s val=%s\n", key, val);

            // all lowercase for reliable comparability
            for (char *p = key; *p; ++p)
            {
                *p = tolower(*p);
			}
			
			// compare details
            if (strcmp(key, "version") == 0)
            {
                strncpy(pkg.version, val, sizeof(pkg.version) - 1);
            }
            else if (strcmp(key, "packageurl") == 0)
            {
                strncpy(pkg.source, val, sizeof(pkg.source) - 1);
            }
            else if (strcmp(key, "sourcecode") == 0)
            {
                strncpy(pkg.source_code, val, sizeof(pkg.source_code) - 1);
            }
            else if (strcmp(key, "snapinfo") == 0)
            {
                strncpy(pkg.snap_info, val, sizeof(pkg.snap_info) - 1);
            }
            else if (strcmp(key, "signature") == 0)
            {
                strncpy(pkg.signature, val, sizeof(pkg.signature) - 1);
            }
            else if (strcmp(key, "checksum") == 0)
            {
                strncpy(pkg.checksum, val, sizeof(pkg.checksum) - 1);
            }
            else if (strcmp(key, "classic") == 0)
            {
                pkg.classic = (strcasecmp(val, "true") == 0);
            }
        }

        fclose(pf);
        unlink(tmp_conf);

        if (pkg.source[0])
        {
            printf("✔ Added package %s (%s)\n", pkg.name, pkg.source);
            packages[package_count++] = pkg;
        }
        
        else
        {
            fprintf(stderr, "⚠ Skipped %s: no packageurl found\n", pkg.name);
        }
    }

    fclose(fh);
    printf("Loaded %d packages from repo.conf\n", package_count);
    return package_count > 0;
}


// searching for the package
Package* find_package(const char *name) 
{
    printf("Get package count.");
    for (int i = 0; i < package_count; i++)
    {
        printf("Count: %d", package_count);
        if (strcasecmp(name, packages[i].name) == 0)
        {
        	printf("Package: %s, %s", name, packages[i].name);
        	return &packages[i];
        }
    }
    return NULL;
}

