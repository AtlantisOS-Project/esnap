/*
* condif_tools.h
*
* (C) Copyright 2025 AtlantisOS Project
* by @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
* Usage:
* #include "config_tools.h"
*/

#ifndef CONFIG_TOOLS_H
#define CONFIG_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <strings.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
* Simple array to act as a hash table
*/
extern ConfigEntry unique_configs[HASH_TABLE_SIZE];

/*
* Helper functions for hashs
*/
// simple hash function (DJB2 algorithm)
unsigned long hash(const char *str);
// function to initialize the hash table
void initialize_hash_table();

/*
* insert a key-value pair, checking for duplicates
*/
bool insert_config(const char *key, const char *value);

/*
* process a single config file
*/
void process_file(const char *filename);

/*
* write the unique configurations to the output file
*/
void write_output(const char *output_filename);



#ifdef __cplusplus
}
#endif

#endif // CONFIG_TOOLS_H
