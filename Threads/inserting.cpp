#include <fstream>
#include <string.h>
// #include <pthread.h>
#include "inserting.h"
#include "dicttree.h"
#include "threadargs.h"

#define DICTOINARY_INDEX 0                      // DICT INDEX

extern struct Thread_Args EXEC_STATUS;

void *inserting::insert(void* arg){
    cout << "J" << endl;

    struct Thread_Args *tmp = (struct Thread_Args*)arg;
    cout << "CAST" << endl;
    cout << (void *)tmp;
    dicttree* root = tmp->root;
    cout << "MIDDLE" << endl;
    cout << tmp->file_path[DICTOINARY_INDEX] << endl;
    ifstream file(tmp->file_path[DICTOINARY_INDEX]);
    string line;
    string temp = "";

    cout << "K" << endl;


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