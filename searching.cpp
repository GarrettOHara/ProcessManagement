#include <fstream>
#include <string.h>
#include <vector>
#include "searching.h"
#include "dicttree.h"
#include "threadargs.h"

#define DICTOINARY_INDEX 0                      // DICT INDEX
#define SAMPLE_INDEX 1                          // SAMPLE INDEX

extern struct Thread_Args EXEC_STATUS;

void* searching::search(void* arg){
    
    while(!EXEC_STATUS.task_done[DICTOINARY_INDEX]){ }
    char delimiters[] = 
        " \n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    struct Thread_Args *tmp = (struct Thread_Args*)arg;    
    dicttree* root = tmp->root;
    ifstream in_file(tmp->file_path[SAMPLE_INDEX]);
    ofstream out_in_file;
    out_in_file.open("countwords_output.txt");
    vector<string> *tokens = new vector<string>;
    string line;
    string temp = "";


    if(in_file.is_open()){
        while (getline(in_file,line)){
            char* token = strtok (&line[0], delimiters);
            while(token != NULL){
                EXEC_STATUS.chars_in_file[SAMPLE_INDEX]++;
                token = strtok (NULL, delimiters);
            }
        }
        /* CLEAR AND RESET in_file POINTER TO BEGINNING */
        in_file.clear();
        in_file.seekg(0);

        /* INTERVAL FOR PROGRESS MARKS */
        const long divider = 
            EXEC_STATUS.chars_in_file[SAMPLE_INDEX]
            /(long)EXEC_STATUS.progress_marks;
        /* CURRENT WORDCOUNT */
        long index = 0;
        long hash_index = 0;

        while (getline(in_file,line)){
            char* token = strtok (&line[0], delimiters);
            while(token != NULL){
                int count = root->searchme(token);
                if(count >= EXEC_STATUS.min_count)
                    out_in_file << token << " " << count << endl;
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
        in_file.close();
    }
    out_in_file.close();
    cout << "\nThere are "
    << EXEC_STATUS.chars_in_file[SAMPLE_INDEX]
    << " words in "
    << EXEC_STATUS.file_path[SAMPLE_INDEX]
    << "."
    << endl;
    EXEC_STATUS.task_done[SAMPLE_INDEX]=true;




    // if(in_file.is_open()){
    //     while (getline(in_file,line)){
    //         char delimiters[] = " \n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    //         char* token = strtok (&line[0], delimiters);
    //         while(token != NULL){
    //             EXEC_STATUS.chars_in_file[SAMPLE_INDEX]++;
    //             tokens->push_back(token);
    //             token = strtok (NULL, delimiters);
    //         }
    //     }
    //     in_file.close();
    // }
    // cout << "There are "
    // << EXEC_STATUS.chars_in_file[SAMPLE_INDEX]
    // << " words in "
    // << EXEC_STATUS.file_path[SAMPLE_INDEX]
    // << "."
    // << endl;
    // for(int i = 0; i < tokens->size(); i++){
    //     int count = root->searchme(tokens->at(i));
    //     if(count >= EXEC_STATUS.min_count)
    //         out_in_file << tokens->at(i) << " " << count << endl;
    // }
    // out_in_file.close();
    
    // EXEC_STATUS.task_done[SAMPLE_INDEX]=true;

    pthread_exit(0);
}