/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | January 2022
 **/

/* IMPORTS */
#include <fstream>
#include <iostream>
#include <string.h>
#include "inserting.h"
#include "threadargs.h"
#include "dicttree.h"

/* STATIC VARIABLES*/
#define DICTOINARY_INDEX 0                      // DICT INDEX

/* NAMESPACE */
using namespace std;

/* SET REFERENCE TO STRUCT DECLARED IN countwords.cpp */
extern struct Thread_Args EXEC_STATUS;

/**
 * @brief  PREPROCCESS ALL BYTES IN THE INPUT FILE
 * 
 * @param filename: CHAR ARRAY OF RELATIVE PATH
 * @return int:     FILE SIZE IN BYTES
 */
static int read_all_bytes(char const* filename){
    ifstream ifs(filename, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();
    return pos;
}

void *inserting::insert(void* arg){
    
    /* INITIALIZE FILE READER */
    ifstream file;
    file.exceptions(ifstream::badbit);
    
    /* SET FILE DELIMITERS */
    const char delimiters[] = 
        " \n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    
    try{
        /* CAST THREAD ARGUMENT TO SHARED DATA STRUCTURE */
        struct Thread_Args *tmp = (struct Thread_Args*)arg;
        
        /* SET REALTIVE PATH FOR FILE READER */
        const char* PATH = tmp->file_path[DICTOINARY_INDEX];
        
        /* SET POINTER TO DICCTREE */
        dicttree* root = tmp->root;

        /* UTILITIES FOR FILE READING */
        string line;
        string temp = "";

        /* SET VALUES OR I/O OBJECTS */
        file.open(PATH);

        
        
        /* ITERATE THROUGH EACH LINE OF FILE */
        if(file.is_open()){
            
            /* FILE IS VALID */
            EXEC_STATUS.good_file[DICTOINARY_INDEX] = true;

            /* PREPROCESS TOTAL BYTES OF INCOMING FILE */
            EXEC_STATUS.chars_in_file[DICTOINARY_INDEX] = 
                (long)read_all_bytes(PATH);
                        
            while (getline(file,line)){
                
                /* UPDATE TOTAL BYTES PROCESSED CHARACTERS IN STRING + 1 FOR NEWLINE CHARACTER */
                long length = line.length()+1;
                EXEC_STATUS.chars_processed[DICTOINARY_INDEX]+=length;
                
                /* TOKENIZE AND ITERATE LINE */
                char* token = strtok (&line[0], delimiters);
                while(token != NULL){

                    /* UPDATE GLOBAL WORDCOUNT, INSERT EACH TOKEN */
                    EXEC_STATUS.word_count[DICTOINARY_INDEX]++;
                    root->insertme(token);

                    token = strtok (NULL, delimiters);
                }
            }
            file.close();
        } else {
            file.close();
            EXEC_STATUS.task_done[DICTOINARY_INDEX]=true;
            pthread_exit(NULL);
        }
    } catch (const ifstream::failure& e){
        file.close();
        throw("Exception opening/reading file");
    }
    
    /* MARK INSERTING THREAD AS COMPLETED */
    EXEC_STATUS.task_done[DICTOINARY_INDEX]=true;
    pthread_exit(0);
}