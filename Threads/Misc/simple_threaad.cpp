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

    vector<int>* vect = (vector<int>*)arg;
    
    // insert
    for(int i = 0; i < 30; i++){
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

    vector<int>* vect = (vector<int>*)arg;

    // read vector
    for(int i = 0; i < vect->size(); i++){
        cout << vect->at(i) << endl;
    }

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
    // vector<int> *heap = new vector<int>();
    // heap->push_back(1);
    // heap->push_back(2);
    
    // CREATES SEGMENTATION FAULT
    vector<int> list;

    // create attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // pthread_create(&thread1, &attr, insert, (void*)&list);
    pthread_create(&thread1, &attr, insert, &list);
    pthread_create(&thread2, &attr, search, &list);

    // waiting on threads
    while(inserting || searching){ }
    
    cout << "FINISHED" << endl;
}
