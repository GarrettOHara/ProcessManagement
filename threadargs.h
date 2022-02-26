/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | January 2022
 **/
#ifndef THREADARGS_H_                            // INCLUDE GUARD
#define THREADARGS_H_
#include <iostream>
#include "dicttree.h"

#define FILE_COUNT 2                             // INPUT FILES

using namespace std;

struct Thread_Args {
    dicttree* root;                              // POINTER TO DICTTREE
    int progress_marks;                          // NUMBER OF MARKS IN BAR
    int hash_interval;                           // NUMBER OF HASHES IN BAR
    int min_count;                               // MIN COUNT TO OUTPUT FILE
    const char* file_path[FILE_COUNT];           // RELATIVE FILE PATH 
    long chars_in_file[FILE_COUNT];              // NUMBER OF WORDS IN FILE
    long chars_processed[FILE_COUNT];            // NUMBER OF WORDS PROCESSED
    long word_count[FILE_COUNT];                 // FILE ARGUMENTS
    bool task_done[FILE_COUNT];                  // THREAD PROGRESS
    bool good_file[FILE_COUNT];                  // MARKING FILE ARGUMENTS AS READABLE

    Thread_Args() { };                           // CONSTRUCTOR
    ~Thread_Args() { };                          // DECONSTRUCTOR

};
#endif                                           // THREADARGS_H_