/*
* esnap.h
*
* (C) Copyright 2025 AtlantisOS Project
* by @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
* Usage:
* #include "esnap.h"
*/

#ifndef ESNAP_H
#define ESNAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <strings.h>
#include <ctype.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/wait.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
* Define some maxima 
*/

// Define package details maximun
#define MAX_PACKAGES 256
#define MAX_NAME_LEN 128
#define MAX_CMD_LEN 512

// Define maximum length for a line and the key
#define MAX_LINE_LENGTH 512
#define MAX_KEY_LENGTH 256

// Define the size of our simple hash table
#define HASH_TABLE_SIZE 1024

/*
* Structure package infos
*/
typedef struct {
    char name[MAX_NAME_LEN];
    char source[MAX_NAME_LEN];     
    char source_code[MAX_NAME_LEN];
    char snap_info[256];
    char signature[256];
    char checksum[256];
    char version[64];
    int classic;
} Package;

/*
* Structure to hold a unique configuration entry (key=value) 
*/
typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_LINE_LENGTH]; // Value can be a URL, so use a larger size
    bool in_use;
} ConfigEntry;

/*
* Define configurations for esnap
*/
extern Package packages[MAX_PACKAGES];
extern int package_count;
extern int no_fallback;
extern int use_repo;
extern int quiet_mode;
extern int no_verify;

/*
* Running something with the little spinner
*/
void run_with_spinner(const char *cmd, const char *message);

/*
* Removes all subsequent spaces, tabs, and line breaks
*/
void trim_trailing_whitespace(char *s);

/*
* Load the package from the config file
*/
int load_packages_from_conf(const char *filename);

/*
* Find the package by name
*/
Package* find_package(const char *name);

/*
* Verify the snap package
*/
int verify_snap(Package *pkg);

/*
* Install the package from the repo
*/
void install_repo_package(Package *pkg);

/*
* Check for installed snaps and there versions
*/
int is_snap_installed(const char *name, char *version, size_t len);

/*
* Install snap package with/without snap store
*/
void install_package(const char *name);

/*
* Updating snap packages with/without snap store
*/
void refresh_package(const char *name, int all_flag);

/*
* Searching for snap package with/without snap store
*/
void search_package(const char *name);

/*
* Run a esnap command to snap
*/
void run_to_snap(int number, char *arguments[]);

/*
* Ouput of the usage
*/
void print_usage();

/**
 * @brief Führt mehrere Konfigurationsdateien zusammen, überspringt Duplikate
 * und gibt Warnungen für ungültige Zeilen aus.
 * * Erwartet, dass das erste Element in 'argv' der Name der Ausgabedatei ist,
 * gefolgt von den Namen der Eingabedateien.
 * * @param argc Die Anzahl der Argumente (output_file + input_files).
 * @param argv Ein Array von Strings, beginnend mit dem Namen der Ausgabedatei.
 * @return int 0 bei Erfolg, 1 bei Fehler (z.B. falsche Argumentanzahl).
 */
int run_config_merge(int argc, char *argv[]);

#ifdef __cplusplus
}
#endif

#endif // ESNAP_H
