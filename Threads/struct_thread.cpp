#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <limits.h>

#include <typeinfo>

#define NUMOFFILES 2
#define DICTSRCFILEINDEX 0
#define TESTFILEINDEX 1
/* default number of progress marks for representing 100% progress */
#define DEFAULT_NUMOF_MARKS 50
/* minimum number of progress marks for representing 100% progress */
#define MIN_NUMOF_MARKS 10
/* place hash marks in the progress bar every N marks */
#define DEFAULT_HASHMARKINTERVAL 10
/* default minimum number of dictionary words starting from a prefix for printing or
writing to the output */
#define DEFAULT_MINNUM_OFWORDS_WITHAPREFIX 1

using namespace std;

void *insert();
void *search();

bool inserting = true;
bool searching = true;

struct Thread_Args {
    vector<int>* root;
    int progress_marks;
    int hash_interval;
    int min_count;
    const char* file_path[NUMOFFILES];
    long chars_in_file[NUMOFFILES];
    long chars_processed[NUMOFFILES];
    long word_count[NUMOFFILES];
    bool task_done[NUMOFFILES];

    Thread_Args(){};

} EXEC_STATUS;

void* insert(void* arg){
	cout << "--------INSERT-------- " << endl;
    struct Thread_Args *tmp = (struct Thread_Args*)arg;
	cout << "FILE PATH: " << tmp->file_path[DICTSRCFILEINDEX] << endl;
    vector<int>* vect = tmp->root;

    for(int i = 0; i < 10; i++){
        vect->push_back(i);
    }

    // end insertion
    inserting = false;

    // return value in second parameter of join
    pthread_exit(0);
}

void* search(void* arg){

    // waiting for insertion
    while(inserting){ }
	cout << "--------SEARCH-------- " << endl;
    struct Thread_Args *tmp = (struct Thread_Args*)arg;
    vector<int> vect = *tmp->root;
    cout << "FILE PATH: " << tmp->file_path[TESTFILEINDEX] << endl;

    for(int i = 0; i < vect.size(); i++){
        cout << vect.at(i) << endl;
    }

    searching = false;

    pthread_exit(0);
}
void process_flag(char flag[], char arg[]){
    char progress[] = "-p";
    char hashes[]   = "-h";
    char count[]    = "-n";
    int  num = atoi(arg);

    if(num >= 0 && num < 10)
        cout << "YES" << endl;

    if(strcmp(flag,progress) == 0){
        if(num > 10)
            throw invalid_argument("Number of progress marks must be a number and "
                "at least 10");
        EXEC_STATUS.progress_marks = num;
    }        
    
    if(strcmp(flag,hashes) == 0){
        if(num >= 0 && num < 10)
            throw invalid_argument("Hash mark interval for progress must be a "
                "number, greater than 0, and less than or equal to 10");
        EXEC_STATUS.hash_interval = num;
    }        
    
    if(strcmp(flag,count) == 0){
        if(num<0 && num<LLONG_MAX)
            throw invalid_argument("Word count constraint must be positive "
                "and within the range of LONG");
        EXEC_STATUS.min_count = num;
    }
    
}

void process_args(int argc, char** argv){
    if(argc < 3){
        printf("ERROR: You need to supply a Dictionary file and Sample text.\n");
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
                }
                else 
                    text = true;
            }

            /* CURRENT ARGUMENT IS A TEXT FILE 
               STORE RELATIVE PATH IN file_path */
            if(text){
                if(EXEC_STATUS.file_path[DICTSRCFILEINDEX]==NULL)
                    EXEC_STATUS.file_path[DICTSRCFILEINDEX]=argv[i];
                else if(EXEC_STATUS.file_path[TESTFILEINDEX]==NULL)
                    EXEC_STATUS.file_path[TESTFILEINDEX]=argv[i];
                else{
                    printf("ERROR: You need to supply a Dictionary file and Sample text.\n");
                    throw invalid_argument("passed too many arguments");
                }
            }
        }
    }
    if(EXEC_STATUS.file_path[DICTSRCFILEINDEX]==NULL
        || EXEC_STATUS.file_path[TESTFILEINDEX]==NULL){
        throw invalid_argument("mandatory parameters not supplied");
        exit(1);
    }
    if(EXEC_STATUS.progress_marks == 0)
        EXEC_STATUS.progress_marks = DEFAULT_NUMOF_MARKS;
    if(EXEC_STATUS.hash_interval == 0)
        EXEC_STATUS.hash_interval = DEFAULT_HASHMARKINTERVAL;
}

int main(int argc, char* argv[]){
    const string err = "\n\nExiting program...\n";
    try{
        // create thread id
        pthread_t thread1, thread2;

        // HEAP DATA
        vector<int> *heap = new vector<int>();
        heap->push_back(1);
        heap->push_back(2);
        
        // STACK DATA
        vector<int> list;

        // create attributes
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        EXEC_STATUS.root = &list;

        process_args(argc,argv);
        

        // pthread_create(&thread1, &attr, insert, (void*)&list);
        pthread_create(&thread1, &attr, insert, &EXEC_STATUS);
        pthread_create(&thread2, &attr, search, &EXEC_STATUS);

        //while(inserting){}
        // waiting on threads
        while(inserting || searching){ }
        
        cout << "FINISHED" << endl;
        // pthread_join(thread1, NULL);
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
