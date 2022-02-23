#include <fstream>
#include <string.h>
#include "searching.h"
#include "dicttree.h"
#include "threadargs.h"

#define DICTOINARY_INDEX 0                      // DICT INDEX
#define SAMPLE_INDEX 1                          // SAMPLE INDEX

extern struct Thread_Args EXEC_STATUS;

void* searching::search(void* arg){

    while(!EXEC_STATUS.task_done[DICTOINARY_INDEX]){ }

    struct Thread_Args *tmp = (struct Thread_Args*)arg;    
    dicttree* root = tmp->root;
    ifstream file(tmp->file_path[SAMPLE_INDEX]);
    string line;
    string temp = "";

    if(file.is_open()){
        while (getline(file,line)){
            char delimiters[] = " \n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
            char* token = strtok (&line[0], delimiters);
            while(token != NULL){
                int count = root->searchme(token);
                cout << token << " " << count << endl;
                token = strtok (NULL, delimiters);
            }
        }
        file.close();
    } 
    EXEC_STATUS.task_done[SAMPLE_INDEX]=true;

    pthread_exit(0);
}