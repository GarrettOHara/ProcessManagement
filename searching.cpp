/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | January 2022
 **/

/* IMPORTS */
#include <fstream>
#include <string.h>
#include "searching.h"
#include "dicttree.h"
#include "threadargs.h"

/* STATIC VARIABLES */
#define DICTOINARY_INDEX 0                      // DICT INDEX
#define SAMPLE_INDEX 1                          // SAMPLE INDEX

/* SET REFERENCE TO STRUCT DECLARED IN countwords.cpp */
extern struct Thread_Args EXEC_STATUS;

/**
 * @brief READ ALL BYTES WITHIN A FILE
 * 
 * @param filename:     CHAR ARRAY OF RELATIVE FILE PATH
 * @return long pos:    FILE SIZE
 * 
 */
static long read_all_bytes(char const* filename){
    ifstream ifs(filename, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();
    return pos;
}

/**
 * @brief SEARCH DICTTREE AND UPDATE SHARED STRUCT
 * 
 * @param arg:      POINTER TO SHARED STRUCT 
 * @return NULL:    NO RETURN FROM THREAD
 */
void* searching::search(void* arg){
    /* WAIT FOR INSERTING THREAD TO FINISH */
    while(!EXEC_STATUS.task_done[DICTOINARY_INDEX]){ }
    
    /* INSTANTIATE FILE READER AND FILE WRITER */
    ifstream in_file;
    ofstream out_file;
    in_file.exceptions(ifstream::badbit);
    out_file.exceptions(ofstream::badbit);

    /* CREATE FILE DELIMITERS */
    const char delimiters[] = 
        " \n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    try{

        /* CAST THREAD ARGUMENT TO SHARED DATA STRUCTURE */
        struct Thread_Args *tmp = (struct Thread_Args*)arg;
        
        /* SET REALTIVE PATH FOR FILE READER */
        const char* PATH = tmp->file_path[SAMPLE_INDEX];
        
        /* SET POINTER TO DICCTREE */
        dicttree* root = tmp->root;
        
        /* UTILITIES FOR FILE READING */
        string line;
        string temp = "";

        /* SET VALUES OR I/O OBJECTS */
        in_file.open(PATH);
        out_file.open("countwords_output.txt");

        /* ITERATE THROUGH EACH LINE OF FILE */
        if(in_file.is_open()){

            /* FILE IS VALID */
            EXEC_STATUS.good_file[SAMPLE_INDEX] = true;

            /* PREPROCESS TOTAL BYTES OF INCOMING FILE */
            EXEC_STATUS.chars_in_file[SAMPLE_INDEX] = 
                (long)read_all_bytes(PATH);
            
            while (getline(in_file,line)){

                /* CHARACTERS IN STRING + 1 FOR NEWLINE CHARACTER */
                long length = line.length()+1;
                
                /* UPDATE PROGRESS IN FILE READING */
                EXEC_STATUS.chars_processed[SAMPLE_INDEX]+=length;
                
                /* TOKENIZE AND ITERATE LINE */
                char* token = strtok (&line[0], delimiters);
                while(token != NULL){

                    /* UPDATE GLOBAL WORDCOUNT, SEARCH EACH TOKEN */
                    EXEC_STATUS.word_count[SAMPLE_INDEX]++;
                    int count = root->searchme(token);

                    /* WRITE TO OUT FILE IF SATISFYING ARGUEMNT */
                    if(count >= EXEC_STATUS.min_count)
                        out_file << token << " " << count << endl;
                    
                    token = strtok (NULL, delimiters);
                }
            }
            in_file.close();
        } else {
            in_file.close();
            out_file.close();
            EXEC_STATUS.task_done[SAMPLE_INDEX]=true;
            pthread_exit(NULL);
        }
        out_file.close();
    } catch (const ifstream::failure& e){
        in_file.close();
        out_file.close();
        throw("Exception opening/reading file");
        
    }
    
    /* MARK SEARCHING THREAD AS COMPLETED*/
    EXEC_STATUS.task_done[SAMPLE_INDEX]=true;
    pthread_exit(0);
}