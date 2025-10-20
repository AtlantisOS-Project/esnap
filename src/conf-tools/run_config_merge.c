/*
 * run_config_merge.c
 *
 * (C) Copyright 2025 AtlantisOS Project
 * by @NachtsternBuild
 *
 * License: GNU GENERAL PUBLIC LICENSE Version 3
 *
 * start the merge of config files
 */
 
#include "esnap.h"
#include "config_tools.h"

/* main function to start the config file merge */
int run_config_merge(int argc, char *argv[]) 
{
    // Check for correct command-line arguments
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s <output_file> <input_file_1> [input_file_2] ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *output_file = argv[1];
    
    // Initialize the set of unique keys
    initialize_hash_table();

    // Process all input files starting from argv[2]
    for (int i = 2; i < argc; i++) 
    {
        process_file(argv[i]);
    }

    // Write the results to the output file
    write_output(output_file);

    return EXIT_SUCCESS;
}
