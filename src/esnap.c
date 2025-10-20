/*
 * esnap.c
 *
 * (C) Copyright 2025 AtlantisOS Project
 * by @NachtsternBuild
 *
 * License: GNU GENERAL PUBLIC LICENSE Version 3
 *
 * External Snap manager with repo.conf repos + verification
 */
 
#include "esnap.h"

int package_count = 0;
int no_fallback = 1;
int use_repo = 1;
int quiet_mode = 0;
int no_verify = 0;

// usage of esnap 
void print_usage()
{
    printf("Usage: esnap [options] <command> [package]\n");
    printf("Commands:\n");
    printf("  install <pkg>        Install package from repo or fallback\n");
    printf("  remove <pkg>         Remove installed snap\n");
    printf("  refresh [pkg|--all]  Refresh package(s)\n");
    printf("  search <pkg>         Search package in repo and fallback\n");
    printf("  enable <pkg>         Enable a snap\n");
    printf("  disable <pkg>        Disable a snap\n");
    printf("  merge-config <output_file> <input_file_1> [input_file_2] Add other config files\n");
    printf("Options:\n");
    printf("  --no-fallback        Disable Snap Store fallback\n");
    printf("  --repo               Force use of external repo\n");
    printf("  --quiet              Suppress spinner/output\n");
    printf("  --no-verify          Skip checksum/signature verification for repo snaps\n");
    printf("  --all                Apply command to all packages (refresh)\n");
}


/* main function */
int main(int argc, char *argv[]) 
{
    if (argc < 1) 
    {
        print_usage();
        return 1;
    }

    // Parse global flags
    int arg_idx = 1;
    while (arg_idx < argc && strncmp(argv[arg_idx], "--", 2) == 0) 
    {
        if (strcmp(argv[arg_idx], "--no-fallback") == 0) 
        {
            no_fallback = 1;
        }
        else if (strcmp(argv[arg_idx], "--repo") == 0) 
        {
            use_repo = 1;
        }
        else if (strcmp(argv[arg_idx], "--quiet") == 0) 
        {
            quiet_mode = 1;
        }
        else if (strcmp(argv[arg_idx], "--no-verify") == 0) 
        {
            no_verify = 1;
        }
        arg_idx++;
    }

    // Load repo packages if available
    //const char *repo_file = "/etc/esnap/repo.conf";
    const char *repo_file = "./repo.conf"; // for testing
    if (!load_packages_from_conf(repo_file)) 
    {
        if (!no_fallback) 
        {
            fprintf(stderr, "No repo.conf found, using Snap Store only\n");
            use_repo = 0;
        }
    }

    if (arg_idx >= argc) 
    {
        print_usage();
        return 1;
    }

    const char *cmd = argv[arg_idx++];
    
    // logic for config merge
    // TODO: static repo.conf as input_file_1 and output_file → user input only second input file
    if (strcmp(cmd, "merge-config") == 0)
    {
        // The arguments passed to the merge function are:
        // argv[arg_idx] = output_file
        // argv[arg_idx + 1] = input_file_1
        // argc - arg_idx is the number of remaining arguments
        return run_config_merge(argc - arg_idx, argv + arg_idx);
    }
    // ------------------------------------
    
    const char *pkg = (arg_idx < argc) ? argv[arg_idx] : NULL;

    if (strcmp(cmd, "install") == 0 && pkg) 
    {
        install_package(pkg);
    }
    
    else if (strcmp(cmd, "refresh") == 0) 
    {
        refresh_package(pkg, pkg && strcmp(pkg, "--all") == 0);
    }

    else if (strcmp(cmd, "search") == 0 && pkg || strcmp(cmd, "find") == 0 && pkg) 
    {
        search_package(pkg);
    }
    
    else if (!strcmp(cmd, "help") || !strcmp(cmd, "-h") || !strcmp(cmd, "--h") || !strcmp(cmd, "--help") || !strcmp(cmd, "h") || !strcmp(cmd, "-help")) 
    {
        print_usage();
    }
    
    else 
    {
        run_to_snap(argc, argv);
    }

    return 0;
}

