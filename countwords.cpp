/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | January 2022
 **/

/* IMPORTS */
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

/* STATIC VARIABLES */
#define DICTOINARY_INDEX 0                      // DICT INDEX
#define SAMPLE_INDEX 1                          // SAMPLE INDEX

/* NAMESPACE */
using namespace std;


/* INITIALIZE GLOBALLY FOR EXTERN CALLS */
Thread_Args EXEC_STATUS;

/**
 * @brief MAIN THREAD, SPAWN WORKER THREADS
 * MANAGE THREAD EXECUTION AND HANDLE PROGRAM I/O
 * 
 * @param argc: CLI ARGUMENT CONT
 * @param argv: CLI ARGUMENT LIST
 * @return int: PROGRAM EXECUTION COMPLETE
 */
int main(int argc, char* argv[]){
    const string err = "\n\nExiting program...\n";
    try{
        /* INSTANTIATE THREADS */
        pthread_t insert, search;

        /* IMPLICIT DECLARATION OF ROOT NODE ON HEAP */
        dicttree *root = new dicttree;

        /* SET POINTER TO ROOT IN SHARED STRUCT */
        EXEC_STATUS.root = root;

        /* PROCESS CLI ARGUMENTS */
        arguments::process_args(argc,argv);

        /* CREATE WORKER THREADS */
        pthread_create(&insert, NULL, inserting::insert, &EXEC_STATUS);
        pthread_create(&search, NULL, searching::search, &EXEC_STATUS);
        
        /* WAIT UNTIL FILE SIZE IS INITIALIZED OR THREAD WORK DONE */
        while(EXEC_STATUS.chars_in_file[DICTOINARY_INDEX]==0 
            && !EXEC_STATUS.task_done[DICTOINARY_INDEX]){ }
        
        /* PROGRESS BAR UTILITY VARIABLE */
        long hash_index = 1;

        /* WAIT FOR INSERTING THREAD TO FINISH EXECUTION */
        while(!EXEC_STATUS.task_done[DICTOINARY_INDEX]){

            /* CHECK TO SEE IF FILE WAS OPENED */
            if(EXEC_STATUS.good_file[DICTOINARY_INDEX]){

                /* SET DIVISOR AS DIVIDENT OF TOTAL CHARS AND DESIRED PROGRESS MARKS */
                /* FOR EVEN INCREMENTATIONS */
                const long divider = EXEC_STATUS.chars_in_file[DICTOINARY_INDEX] 
                    / (long)EXEC_STATUS.progress_marks;

                /* CHECK TO SEE IF NEXT PROGRESS INCREMENT HAS BEEN MET */
                if(EXEC_STATUS.chars_processed[DICTOINARY_INDEX]>=(divider*hash_index)){
                    if(hash_index%EXEC_STATUS.hash_interval)
                        cout << '-' << flush;
                    else
                        cout << '#' << flush;
                    hash_index++;
                }
            }
        }
        /* DISPLAY FILE DATA */
        if(EXEC_STATUS.good_file[DICTOINARY_INDEX]){
            cout << "\nThere are "
            << EXEC_STATUS.word_count[DICTOINARY_INDEX]
            << " words in "
            << EXEC_STATUS.file_path[DICTOINARY_INDEX]
            << "."
            << endl;
        } else {
            pthread_cancel(insert);
            throw ios_base::failure(EXEC_STATUS.file_path[DICTOINARY_INDEX]);
        }

        /*  WAIT UNTIL FILE SIZE IS INITIALIZED OR THREAD WORK DONE */
        while(EXEC_STATUS.chars_in_file[SAMPLE_INDEX]==0 
            && !EXEC_STATUS.task_done[SAMPLE_INDEX]){}

        /* RESET PROGRESS BAR UTILITY VARIABLE */
        hash_index = 1;
        while(!EXEC_STATUS.task_done[SAMPLE_INDEX]){
            
            /* CHECK TO SEE IF FILES WERE OPENED */
            if(EXEC_STATUS.good_file[SAMPLE_INDEX]){
                
                /* SET DIVISOR AS DIVIDENT OF TOTAL CHARS AND DESIRED PROGRESS MARKS 
                   FOR EVEN INCREMENTATIONS */
                const long divider = EXEC_STATUS.chars_in_file[SAMPLE_INDEX] 
                    / (long)EXEC_STATUS.progress_marks;
                
                /* CHECK TO SEE IF NEXT PROGRESS INCREMENT HAS BEEN MET */
                if(EXEC_STATUS.chars_processed[SAMPLE_INDEX]>=(divider*hash_index)){
                    if(hash_index%EXEC_STATUS.hash_interval)
                        cout << '-' << flush;
                    else
                        cout << '#' << flush;
                    hash_index++;
                }
            }
        }

        /* DISPLAY FILE DATA */
        if(EXEC_STATUS.good_file[SAMPLE_INDEX]){
            cout << "\nThere are "
            << EXEC_STATUS.word_count[SAMPLE_INDEX]
            << " words in "
            << EXEC_STATUS.file_path[SAMPLE_INDEX]
            << "."
            << endl;
        }

        /* SUCCESS */
        return 0;
        
    } catch(const char* msg){
        cout << msg << err << endl;
    } catch (const ios_base::failure& e){
        cout << "Unable to open <<" << e.what() << ">>" << endl;
    } catch ( const exception& e ) {
        cerr << "ERROR: " << e.what() << err << endl;
    } catch (...) {
        cout << "Exception occurred";
    }
}
