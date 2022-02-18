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
    // int *arg_ptr = (int*) arg;
    // int ptr = *arg_ptr;
    // cout << "PARAMETER: " << ptr << endl;

    vector<int> *list = (vector<int>*)arg;
    vector<int> vect = *list;

    for(int i = 0; i < vect.size(); i++){
        cout << vect[i] << endl;
    }

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

    int val = atoi(argv[1]);

    // create thread id
    pthread_t thread1, thread2;

    // create heap data
    vector<int> *list = new vector<int>();
    list->push_back(1);
    list->push_back(2);
    
    // create attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&thread1, &attr, insert, &list);
    pthread_create(&thread2, &attr, search, NULL);

    // waiting on threads
    while(inserting || searching){ }
    
    cout << "FINISHED" << endl;
    //pthread_join(thread_id, NULL);
}
