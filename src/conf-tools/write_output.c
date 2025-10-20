/*
 * write_output.c
 *
 * (C) Copyright 2025 AtlantisOS Project
 * by @NachtsternBuild
 *
 * License: GNU GENERAL PUBLIC LICENSE Version 3
 *
 * write the configurations to the output file
 */
 
#include "esnap.h"
#include "config_tools.h"

// simple array to act as a hash table
ConfigEntry unique_configs[HASH_TABLE_SIZE];

// write the unique configurations to the output file
void write_output(const char *output_filename)
{
    FILE *output = fopen(output_filename, "w");
    if (output == NULL) 
    {
        perror("Error creating output file");
        fprintf(stderr, "Could not create output file: %s\n", output_filename);
        return;
    }

    printf("\n--- Writing unique configurations to: %s ---\n", output_filename);
    
    int count = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) 
    {
        if (unique_configs[i].in_use) 
        {
            fprintf(output, "%s=%s\n", unique_configs[i].key, unique_configs[i].value);
            count++;
        }
    }

    printf("Successfully wrote %d unique configuration entries.\n", count);
    fclose(output);
}
