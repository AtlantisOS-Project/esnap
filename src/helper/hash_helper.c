/*
 * hash_helper.c
 *
 * (C) Copyright 2025 AtlantisOS Project
 * by @NachtsternBuild
 *
 * License: GNU GENERAL PUBLIC LICENSE Version 3
 *
 * helper functions with hash 
 */
 
#include "esnap.h"
#include "config_tools.h"

// simple hash function (DJB2 algorithm)
unsigned long hash(const char *str) 
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) 
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % HASH_TABLE_SIZE;
}

// function to initialize the hash table
void initialize_hash_table() 
{
    for (int i = 0; i < HASH_TABLE_SIZE; i++) 
    {
        unique_configs[i].in_use = false;
    }
}
