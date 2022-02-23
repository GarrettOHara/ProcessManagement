#ifndef PROCCESSHELPER_H_
#define PROCCESSHELPER_H_
#define FILE_COUNT 2
#include <iostream>
#include "dicttree.h"

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

} EXEC_STATUS;

class proceshelper{
    private:
        void process_flag(char[],char[]);
    public:
        void process_args(int,char*[]);
};
#endif