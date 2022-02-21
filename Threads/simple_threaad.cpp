#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

void *insert();
void *search();

bool inserting = true;
bool searching = true;

void* insert(void* arg){
    vector<int*>&v = *reinterpret_cast<vector<int*>*>(arg);
    cout << *v.at(0) << endl;
    v.push_back(3);
    

    for(int i = 0; i < 10; i++){
        cout << "INSERTING DICTTREE: " << i << endl;
    }

    // end insertion
    inserting = false;

    // return value in second parameter of join
    pthread_exit(0);
}

void* search(void* arg){
    // waiting for insertion
    while(inserting){ }


    cout << "SEARCH: " << endl;
    searching = false;

    pthread_exit(0);
}

int main(int argc, char** argv){
    
    int val;
    if(argc > 1) 
        val = atoi(argv[1]);

    // create thread id
    pthread_t thread1, thread2;

    // create heap data
    vector<int> *list = new vector<int>();
    list->push_back(1);
    list->push_back(2);
    
    // CREATES SEGMENTATION FAULT
    // vector<int> *list;
    // list->push_back(1);
    // list->push_back(2);

    // create attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&thread1, &attr, insert, (void*)&list);
    pthread_create(&thread2, &attr, search, NULL);

    // waiting on threads
    while(inserting || searching){ }
    
    cout << "FINISHED" << endl;
    //pthread_join(thread_id, NULL);
}
