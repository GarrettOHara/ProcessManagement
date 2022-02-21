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

struct Thread_Args {
    string file_path;
    vector<int>* root;
};

void* insert(void* arg){
    struct Thread_Args *tmp = (struct Thread_Args*)arg;

    vector<int>* vect = tmp->root;

    for(int i = 0; i < 10; i++){
        vect->push_back(i);
    }
    

    // end insertion
    inserting = false;

    // return value in second parameter of join
    pthread_exit(0);
}

void* search(void* arg){
	cout << "SEARCH: " << endl;

    // waiting for insertion
    while(inserting){ }

    struct Thread_Args *tmp = (struct Thread_Args*)arg;
    vector<int> vect = *tmp->root;
    cout << "FILE PATH: " << tmp->file_path << endl;

    for(int i = 0; i < vect.size(); i++){
        cout << vect.at(i) << endl;
    }

    searching = false;

    pthread_exit(0);
}

int main(int argc, char** argv){
    
    int val;
    if(argc > 1) 
        val = atoi(argv[1]);

    // create thread id
    pthread_t thread1, thread2;

    // HEAP DATA
    vector<int> *heap = new vector<int>();
    heap->push_back(1);
    heap->push_back(2);
    
    // STACK DATA
    vector<int> list;

    // create attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    Thread_Args insert_thread = {"", &list};
    

    // pthread_create(&thread1, &attr, insert, (void*)&list);
    pthread_create(&thread1, &attr, insert, &insert_thread);
    insert_thread.file_path = "test";
    pthread_create(&thread2, &attr, search, &insert_thread);

    //while(inserting){}
    // waiting on threads
    while(inserting || searching){ }
    
    cout << "FINISHED" << endl;
    // pthread_join(thread1, NULL);
}
