#include <fstream>
#include <string.h>
#include <vector>
#include "inserting.h"
#include "threadargs.h"
#include "dicttree.h"

#define DICTOINARY_INDEX 0                      // DICT INDEX

using namespace std;

extern struct Thread_Args EXEC_STATUS;

void *inserting::insert(void* arg){
    char delimiters[] = 
        " \n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    struct Thread_Args *tmp = (struct Thread_Args*)arg;
    ifstream file(tmp->file_path[DICTOINARY_INDEX]);
    dicttree* root = tmp->root;
    string line;
    string temp = "";

    /**
     * MUST READ ENTIRE FILE TWICE, STORING IN VECTOR 
     * RESULTS IN AN ERROR FOR THE 'A' CHARACTER COUNT
     * 
     */
    if(file.is_open()){
        while (getline(file,line)){
            char* token = strtok (&line[0], delimiters);
            while(token != NULL){
                EXEC_STATUS.chars_in_file[DICTOINARY_INDEX]++;
                token = strtok (NULL, delimiters);
            }
        }
        /* CLEAR AND RESET FILE POINTER TO BEGINNING */
        file.clear();
        file.seekg(0);

        /* INTERVAL FOR PROGRESS MARKS */
        const long divider = 
            EXEC_STATUS.chars_in_file[DICTOINARY_INDEX]
            /(long)EXEC_STATUS.progress_marks;
        /* CURRENT WORDCOUNT */
        long index = 0;
        long hash_index = 0;

        while (getline(file,line)){
            char* token = strtok (&line[0], delimiters);
            while(token != NULL){
                root->insertme(token);
                long length = strlen(token);
                token = strtok (NULL, delimiters);
                index++;
                /* PLACE PROGRESS MARK */
                if(index%divider==0){
                    hash_index++;
                    if(hash_index%EXEC_STATUS.hash_interval)
                        cout << '-';
                    else
                        cout << '#';
                }
            }
        }
        file.close();
    }
    cout << "\nThere are "
    << EXEC_STATUS.chars_in_file[DICTOINARY_INDEX]
    << " words in "
    << EXEC_STATUS.file_path[DICTOINARY_INDEX]
    << "."
    << endl;

    EXEC_STATUS.task_done[DICTOINARY_INDEX]=true;

    // return value in second parameter of join
    pthread_exit(0);
}