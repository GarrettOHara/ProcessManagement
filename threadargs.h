#ifndef THREADARGS_H_
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
    long chars_processed[FILE_COUNT];           // NUMBER OF WORDS PROCESSED
    long word_count[FILE_COUNT];                 // 
    bool task_done[FILE_COUNT];

    Thread_Args() { };                           // CONSTRUCTOR
    ~Thread_Args() { };                          // DECONSTRUCTOR

};
#endif                                           // THREADARGS_H_