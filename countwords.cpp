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


#define DICTOINARY_INDEX 0                      // DICT INDEX
#define SAMPLE_INDEX 1                          // SAMPLE INDEX


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

        cout << EXEC_STATUS.hash_interval << endl;
        cout << EXEC_STATUS.min_count << endl;
        cout << EXEC_STATUS.progress_marks << endl;
        
        pthread_create(&thread1, NULL, inserting::insert, &EXEC_STATUS);
        pthread_create(&thread2, NULL, searching::search, &EXEC_STATUS);

        // waiting on threads
        while(!EXEC_STATUS.task_done[DICTOINARY_INDEX]
          ||!EXEC_STATUS.task_done[SAMPLE_INDEX]){

            /* WAIT UNTIL FILE SIZE IS INITIALIZED */
            while(EXEC_STATUS.chars_in_file[DICTOINARY_INDEX]==0){}
            
            while(EXEC_STATUS.chars_in_file[DICTOINARY_INDEX]!=0 && !EXEC_STATUS.task_done[DICTOINARY_INDEX]){ 
                const long divider = EXEC_STATUS.chars_in_file[DICTOINARY_INDEX] / (long)EXEC_STATUS.progress_marks;
                long hash_index = 1;
                if(EXEC_STATUS.chars_processed[DICTOINARY_INDEX]>=divider*hash_index){
                    if(hash_index%EXEC_STATUS.hash_interval)
                        cout << '-';
                    else
                        cout << '#';
                    hash_index++;
                }
            }
            cout << "\nThere are "
            << EXEC_STATUS.word_count[DICTOINARY_INDEX]
            << " words in "
            << EXEC_STATUS.file_path[DICTOINARY_INDEX]
            << "."
            << endl;

            while(EXEC_STATUS.chars_in_file[SAMPLE_INDEX]==0){}

            while(EXEC_STATUS.chars_in_file[SAMPLE_INDEX]!=0 && !EXEC_STATUS.task_done[SAMPLE_INDEX]){
            
            }
        }
        
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
