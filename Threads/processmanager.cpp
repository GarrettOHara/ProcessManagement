#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits.h>
#include <pthread.h>
#include "processhelper.h"

#define DICTIONARY_INDEX 0
#define SAMPLE_INDEX 1

using namespace std;

void *insert();
void *search();

void* insert(void* arg){
    struct Thread_Args *tmp = (struct Thread_Args*)arg;    
    dicttree* root = tmp->root;
    ifstream file(tmp->file_path[DICTIONARY_INDEX]);
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
    EXEC_STATUS.task_done[DICTIONARY_INDEX]=true;
    pthread_exit(0);
}

void* search(void* arg){

    // waiting for insertion
    while(!EXEC_STATUS.task_done[DICTIONARY_INDEX]){ }

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

int main(int argc, char* argv[]){
    const string err = "\n\nExiting program...\n";
    try{
        // create thread id
        pthread_t thread1, thread2;

        // STACK DATA
        dicttree root;
        EXEC_STATUS.root = &root;

        proceshelper ph;
        ph.process_args(argc,argv);
        
        pthread_create(&thread1, NULL, insert, &EXEC_STATUS);
        pthread_create(&thread2, NULL, search, &EXEC_STATUS);

        // waiting on threads
        while(!EXEC_STATUS.task_done[DICTIONARY_INDEX]
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
