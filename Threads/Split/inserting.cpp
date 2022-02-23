#include <fstream>
#include <string.h>
#include "inserting.h"
#include "threadargs.h"
#include "dicttree.h"

#define DICTOINARY_INDEX 0                      // DICT INDEX

using namespace std;

extern struct Thread_Args EXEC_STATUS;

void *inserting::insert(void* arg){
    struct Thread_Args *tmp = (struct Thread_Args*)arg;
    dicttree* root = tmp->root;
    ifstream file(tmp->file_path[DICTOINARY_INDEX]);
    string line;
    string temp = "";

    if(file.is_open()){
        while (getline(file,line)){
            char delimiters[] = " \n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
            char* token = strtok (&line[0], delimiters);
            while(token != NULL){
                root->insertme(token);
                token = strtok (NULL, delimiters);
            }
        }
        file.close();
    }

    EXEC_STATUS.task_done[DICTOINARY_INDEX]=true;

    // return value in second parameter of join
    pthread_exit(0);
}