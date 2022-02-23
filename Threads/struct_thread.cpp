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


#define FILE_COUNT 2                            // INPUT FILES
#define DICTOINARY_INDEX 0                      // DICT INDEX
#define SAMPLE_INDEX 1                          // SAMPLE INDEX
#define DEFAULT_NUMOF_MARKS 50                  // PROGRESS MARKS
#define NUMOF_MARKS_CIELING 10                  // CIELING OF MARKS 
#define DEFAULT_HASH_INTERVAL 10                // HASH EVERY N MARKS
#define HASH_INTERVAL_CIELING 10                // HASH MARK CEILING
#define DEFAULT_PREFIX_COUNT 1                  // STD OUT MIN COUNT
#define FLOOR 0                                 // ARGUMENT FLOOR

using namespace std;

void *insert();
void *search();

// bool inserting = true;
// bool searching = true;

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

void* insert(void* arg){
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
    

    // end insertion
    // inserting = false;
    EXEC_STATUS.task_done[DICTOINARY_INDEX]=true;

    // return value in second parameter of join
    pthread_exit(0);
}

void* search(void* arg){

    // waiting for insertion
    // while(inserting){ }
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

    // searching = false;
    EXEC_STATUS.task_done[SAMPLE_INDEX]=true;

    pthread_exit(0);
}
void process_flag(char flag[], char arg[]){
    const int num = atoi(arg);
    char progress[] = "-p";
    char hashes[]   = "-h";
    char count[]    = "-n";
    
    if(strcmp(flag,progress) == 0){
        if(num > NUMOF_MARKS_CIELING)
            throw invalid_argument("Number of progress marks must be a "
            "number and at least 10");
        EXEC_STATUS.progress_marks = num;
    }        
    
    if(strcmp(flag,hashes) == 0){
        if(FLOOR <= num && num < HASH_INTERVAL_CIELING)
            throw invalid_argument("Hash mark interval for progress must be "
                "a number, greater than 0, and less than or equal to 10");
        EXEC_STATUS.hash_interval = num;
    }        
    
    if(strcmp(flag,count) == 0){
        if(FLOOR <= num && num < INT32_MAX)
            throw invalid_argument("Word count constraint must be positive "
                "and within the range of LONG");
        EXEC_STATUS.min_count = num;
    }
}

void process_args(int argc, char* argv[]){
    if(argc < 3){
        printf("ERROR: You need to supply a Dictionary file and "
               "Sample text.\n");
        throw invalid_argument("invalid arguments");
        exit(1);
    } else if(argc > 9){
        printf("ERROR: You passed too many arguments.");
        throw invalid_argument("invalid arguments");
        exit(1);
    } else {

        /* START INDEX AT 1 TO PASS EXECUTABLE FILE  ARG*/
        for(int i = 1; i < argc; i++){
            bool text = false;
            int  file_index = 0;
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
                    printf("ERROR: You need to supply a Dictionary file and "
                           "Sample text.\n");
                    throw invalid_argument("passed too many arguments");
                }
            }
        }
    }
    if(EXEC_STATUS.file_path[DICTOINARY_INDEX]==NULL
        || EXEC_STATUS.file_path[SAMPLE_INDEX]==NULL){
        throw invalid_argument("mandatory parameters not supplied");
        exit(1);
    }
    if(EXEC_STATUS.progress_marks == 0)
        EXEC_STATUS.progress_marks = DEFAULT_NUMOF_MARKS;
    if(EXEC_STATUS.hash_interval == 0)
        EXEC_STATUS.hash_interval = DEFAULT_HASH_INTERVAL;
}

int main(int argc, char* argv[]){
    const string err = "\n\nExiting program...\n";
    try{
        // create thread id
        pthread_t thread1, thread2;

        // STACK DATA
        dicttree root;
        EXEC_STATUS.root = &root;

        process_args(argc,argv);
        
        // pthread_create(&thread1, &attr, insert, (void*)&list);
        pthread_create(&thread1, NULL, insert, &EXEC_STATUS);
        pthread_create(&thread2, NULL, search, &EXEC_STATUS);

        // waiting on threads
        //while(inserting || searching){ }
        while(!EXEC_STATUS.task_done[DICTOINARY_INDEX]
            ||!EXEC_STATUS.task_done[SAMPLE_INDEX]){ }
        
    } catch(const char* msg){
        cout << msg << 
        "\n\nPlease supply 2 exceptions:" <<
        "\n  - Path to dictionary"  <<
        "\n  - Path to sample text" <<
        err << endl;
    } catch ( const exception& e ) {
        cerr << "ERROR: " << e.what() << err << endl;
    } catch (...) {
        cout << "Exception occurred";
    }
}
