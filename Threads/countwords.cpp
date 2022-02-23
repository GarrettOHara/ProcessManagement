#include <iostream>
#include <pthread.h>
#include <stdexcept>
#include "searching.h"
#include "inserting.h"
#include "dicttree.h"
#include "threadargs.h"
#include "threadmanager.h"

#define DICTOINARY_INDEX 0                      // DICT INDEX
#define SAMPLE_INDEX 1                          // SAMPLE INDEX

// extern struct Thread_Args EXEC_STATUS;
Thread_Args EXEC_STATUS;

int main(int argc, char* argv[]){
    const string err = "\n\nExiting program...\n";
    try{

        cout << "A" << endl;

        // Thread_Args EXEC_STATUS;

        // threadmanager manager;

        // create thread id
        pthread_t insert_thread, search_thread;

        //dicttree root;
        // EXEC_STATUS.root = &root;
        dicttree *root = new dicttree;
        EXEC_STATUS.root = root;
        
        cout << "B" << endl;


        // manager.process_args(argc,argv);
        threadmanager::process_args(argc,argv);

        cout << "I" << endl;
        
        pthread_create(&insert_thread, NULL, inserting::insert, NULL);
        pthread_create(&search_thread, NULL, searching::search, NULL);

        // waiting on threads
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
