#include <fstream>
#include <string.h>
#include "inserting.h"
#include "threadargs.h"
#include "dicttree.h"

#define DICTOINARY_INDEX 0                      // DICT INDEX

using namespace std;

extern struct Thread_Args EXEC_STATUS;

static int read_all_bytes(char const* filename){
    ifstream ifs(filename, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();
    return pos;
}

void *inserting::insert(void* arg){
    char delimiters[] = 
        " \n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    struct Thread_Args *tmp = (struct Thread_Args*)arg;
    const char* PATH = tmp->file_path[DICTOINARY_INDEX];
    ifstream file(PATH);
    dicttree* root = tmp->root;
    string line;
    string temp = "";

    EXEC_STATUS.chars_in_file[DICTOINARY_INDEX] = 
        (long)read_all_bytes(PATH);

    if(file.is_open()){
    
        while (getline(file,line)){
            /* CHARACTERS IN STRING + 1 FOR NEWLINE CHARACTER */
            long length = line.length()+1;
            char* token = strtok (&line[0], delimiters);
            while(token != NULL){
                root->insertme(token);
                EXEC_STATUS.chars_processed[DICTOINARY_INDEX]+=length;
                EXEC_STATUS.word_count[DICTOINARY_INDEX]++;
                token = strtok (NULL, delimiters);
            }
        }
        file.close();
    }
    
    
    
    EXEC_STATUS.task_done[DICTOINARY_INDEX]=true;
    cout << EXEC_STATUS.chars_in_file[DICTOINARY_INDEX] << endl;
    pthread_exit(0);
}