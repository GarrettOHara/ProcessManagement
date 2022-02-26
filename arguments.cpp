/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | January 2022
 **/

/* IMPORTS */
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <limits.h>
#include "dicttree.h"
#include "inserting.h"
#include "searching.h"
#include "threadargs.h"
#include "arguments.h"


/* STATIC VARIABLES */
#define FILE_COUNT 2                            // INPUT FILES
#define DICTOINARY_INDEX 0                      // DICT INDEX
#define SAMPLE_INDEX 1                          // SAMPLE INDEX
#define DEFAULT_NUMOF_MARKS 50                  // PROGRESS MARKS
#define NUMOF_MARKS_FLOOR 10                    // CIELING OF MARKS 
#define DEFAULT_HASH_INTERVAL 10                // HASH EVERY N MARKS
#define HASH_INTERVAL_CIELING 10                // HASH MARK CEILING
#define DEFAULT_PREFIX_COUNT 1                  // STD OUT MIN COUNT
#define FLOOR 0                                 // ARGUMENT FLOOR


/* NAMESPACE*/
using namespace std;


/* SET REFERENCE TO STRUCT DECLARED IN countwords.cpp */
extern struct Thread_Args EXEC_STATUS;


/**
 * @brief PROCESS CLI ARGUMENT FLAGS AND UPDATE SHARED
 * DATA STRUCT
 * 
 * @param flag: FLAG TYPE
 * @param arg:  FLAG ARGUMENT
 */
void arguments::process_flag(char flag[], char arg[]){

    /* CAST CHAR ARRAY TO INT */
    const int num = atoi(arg);
    
    /* SET FLAGS */
    char progress[] = "-p";
    char hashes[]   = "-h";
    char count[]    = "-n";
    
    /* PROGRESS MARKS PARSSER */
    if(strcmp(flag,progress) == 0){
        if(num < NUMOF_MARKS_FLOOR)
            throw invalid_argument("Number of progress marks must be a "
            "number and at least 10");
        EXEC_STATUS.progress_marks = num;
    }        
    
    /* HASH MARK PARSSER */
    if(strcmp(flag,hashes) == 0){
        if(FLOOR > num || num >= HASH_INTERVAL_CIELING)
            throw invalid_argument("Hash mark interval for progress must be "
                "a number, greater than 0, and less than or equal to 10");
        EXEC_STATUS.hash_interval = num;
    }        
    
    /* WORD COUNT PARSSER */
    if(strcmp(flag,count) == 0){
        if(FLOOR >= num || num > INT32_MAX)
            throw invalid_argument("Word count constraint must be positive "
                "and within the range of LONG");
        EXEC_STATUS.min_count = num;
    }
}
/**
 * @brief PROCESS ALL CLI ARGUMENTS
 * 
 * @param argc: CLI ARGUMENT COUNT
 * @param argv: ARRAY OF CLI ARGUMENTS 
 * (EACH ARGUMENT IS ARRAY OF CHARACTERS)
 */
void arguments::process_args(int argc, char* argv[]){

    /* CHECK IF INPUT FILES PASSED */
    if(argc < 3){
        throw invalid_argument("You need to supply a Dictionary file and "
            "Sample text.\n");

    /* CHECK ARGUMENT CIELING */
    } else if(argc > 9){
        throw invalid_argument("You passed too many arguments.");
    
    /* GOOD INPUT: PROCESS ARGUMENTS */
    } else {

        /* START INDEX AT 1 TO PASS EXECUTABLE FILE  ARG*/
        for(int i = 1; i < argc; i++){
            bool text = false;
            int  file_index = 0;

            /* ITERATE ARGUMENTS */
            for(int j = 0; j < strlen(argv[i]); j++){

                /* ENCOUNTERED FLAG MAKE SURE ARGUMENT EXISTS */
                if(argv[i][j]=='-' && i+1 < argc){

                    /* SKIP FLAG ARGUMENT */
                    process_flag(argv[i], argv[i+1]);
                    i++;
                    break;
                } else 
                    text = true;
            }

            /* CURRENT ARGUMENT IS A TEXT FILE 
               STORE RELATIVE PATH IN file_path */
            if(text){
                if(EXEC_STATUS.file_path[DICTOINARY_INDEX]==NULL)
                    EXEC_STATUS.file_path[DICTOINARY_INDEX]=argv[i];
                else if(EXEC_STATUS.file_path[SAMPLE_INDEX]==NULL)
                    EXEC_STATUS.file_path[SAMPLE_INDEX]=argv[i];
                else{
                    throw invalid_argument("passed too many file arguments");
                }
            }
        }
    }

    /* FILES NOT PASSED */
    if(EXEC_STATUS.file_path[DICTOINARY_INDEX]==NULL
        || EXEC_STATUS.file_path[SAMPLE_INDEX]==NULL){
        throw invalid_argument("mandatory arguments not supplied");
        exit(1);
    }

    /* SET DEFAULTS IF NO ARGUMENTS ARE PASSED */
    if(EXEC_STATUS.progress_marks == 0)
        EXEC_STATUS.progress_marks = DEFAULT_NUMOF_MARKS;
    if(EXEC_STATUS.hash_interval == 0)
        EXEC_STATUS.hash_interval = DEFAULT_HASH_INTERVAL;
    if(EXEC_STATUS.min_count == 0)
        EXEC_STATUS.min_count = DEFAULT_PREFIX_COUNT;
}