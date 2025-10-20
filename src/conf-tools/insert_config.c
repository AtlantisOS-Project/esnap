/*
 * insert_config.c
 *
 * (C) Copyright 2025 AtlantisOS Project
 * by @NachtsternBuild
 *
 * License: GNU GENERAL PUBLIC LICENSE Version 3
 *
 * insert something to the config file
 */
 
#include "esnap.h"
#include "config_tools.h"

// insert a key-value pair, checking for duplicates
bool insert_config(const char *key, const char *value) 
{
    unsigned long index = hash(key);
    
    // linear probing to find an empty slot or the key itself
    for (int i = 0; i < HASH_TABLE_SIZE; i++) 
    {
        unsigned long current_index = (index + i) % HASH_TABLE_SIZE;
        
        if (unique_configs[current_index].in_use) 
        {
            // check for duplicate key
            if (strcmp(unique_configs[current_index].key, key) == 0) 
            {
                // duplicate found, skip it
                return false;
            }
        } 
        
        else 
        {
            // found an empty slot, insert the new entry
            strncpy(unique_configs[current_index].key, key, MAX_KEY_LENGTH - 1);
            unique_configs[current_index].key[MAX_KEY_LENGTH - 1] = '\0';
            
            strncpy(unique_configs[current_index].value, value, MAX_LINE_LENGTH - 1);
            unique_configs[current_index].value[MAX_LINE_LENGTH - 1] = '\0';
            
            unique_configs[current_index].in_use = true;
            return true; // successfully inserted
        }
    }
    
    // hash table is full or probing failed to find a spot
    fprintf(stderr, "Error: Hash table is full or collision resolution failed for key: %s\n", key);
    return false;
}
