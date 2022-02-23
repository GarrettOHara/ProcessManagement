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
#include "inserting.h"
#include "searching.h"
#include "threadargs.h"
#include "arguments.h"


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


Thread_Args EXEC_STATUS;


int main(int argc, char* argv[]){
    const string err = "\n\nExiting program...\n";
    try{
        // create thread id
        pthread_t thread1, thread2;

        dicttree *root = new dicttree;
        EXEC_STATUS.root = root;

        arguments::process_args(argc,argv);
        
        pthread_create(&thread1, NULL, inserting::insert, &EXEC_STATUS);
        pthread_create(&thread2, NULL, searching::search, &EXEC_STATUS);

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
