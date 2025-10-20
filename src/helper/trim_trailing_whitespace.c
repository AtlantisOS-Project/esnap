/*
 * trim_trailing_whitespace.c
 *
 * (C) Copyright 2025 AtlantisOS Project
 * by @NachtsternBuild
 *
 * License: GNU GENERAL PUBLIC LICENSE Version 3
 *
 * Removes all subsequent spaces, tabs, and line breaks
 */
 
#include "esnap.h"

// Removes all subsequent spaces, tabs, and line breaks
void trim_trailing_whitespace(char *s) 
{
    if (!s) 
    {
    	return;
    }
    int i = strlen(s) - 1; // start at the last symbol
    
    // condition: i >= 0 and the character is a whitespace character
    while (i >= 0 && (s[i] == ' ' || s[i] == '\n' || s[i] == '\r' || s[i] == '\t')) 
    {
        s[i] = '\0'; // Null-Terminator
        i--;
    }
}
