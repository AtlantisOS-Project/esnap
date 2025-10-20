/*
 * process_file.c
 *
 * (C) Copyright 2025 AtlantisOS Project
 * by @NachtsternBuild
 *
 * License: GNU GENERAL PUBLIC LICENSE Version 3
 *
 * process a single config file
 */
 
#include "esnap.h"
#include "config_tools.h"

// process a single config file
void process_file(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        fprintf(stderr, "Could not open file: %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int line_count = 0;

    printf("--- Processing file: %s ---\n", filename);

    while (fgets(line, sizeof(line), file)) 
    {
        line_count++;
        
        // remove trailing newline character
        line[strcspn(line, "\n")] = 0;

        // skip empty lines or lines starting with '#'
        if (line[0] == '\0' || line[0] == '#') 
        {
            continue;
        }

        // check for the '=' separator
        char *separator = strchr(line, '=');

        if (separator == NULL || separator == line || *(separator + 1) == '\0') 
        {
            // structure does not match 'key=value'
            fprintf(stderr, "WARNING in file %s at line %d: Line structure invalid. Expected 'key=value', got: '%s'\n", filename, line_count, line);
            continue;
        }
        
        // separate key and value
        *separator = '\0'; // Null-terminate
        char *key = line;
        char *value = separator + 1;

        // insert into the unique configurations set
        if (insert_config(key, value)) 
        {
            printf("New entry: %s=%s\n", key, value); // successfully inserted
        } 
        
        else 
        {
            // duplicate skipped
            printf("SKIPPED DUPLICATE in file %s at line %d: Key '%s' already exists.\n", filename, line_count, key);
        }
    }

    fclose(file);
}
