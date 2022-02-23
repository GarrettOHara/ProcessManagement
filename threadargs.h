#ifndef THREADARGS_H_
#define THREADARGS_H_
#include <iostream>
#include "dicttree.h"

#define FILE_COUNT 2                            // INPUT FILES

using namespace std;

struct Thread_Args {
    dicttree* root;
    int progress_marks;
    int hash_interval;
    int min_count;
    const char* file_path[FILE_COUNT];
    long chars_in_file[FILE_COUNT];
    long chars_processed[FILE_COUNT];
    long word_count[FILE_COUNT];
    bool task_done[FILE_COUNT];

    Thread_Args() { };

};
#endif                                           // THREADARGS_H_