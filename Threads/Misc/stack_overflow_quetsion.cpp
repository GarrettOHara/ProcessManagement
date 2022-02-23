#include <vector>
#include <iostream>
#include <pthread.h>

using namespace std;

void *insert();
void *search();

bool inserting = true;
bool searching = true;

void* insert(void* arg){
    
    vector<int>* vect = (vector<int>*)arg;
    cout << vect->at(0) << endl;
    vect->push_back(10);
    cout << vect->at(1) << endl;

    inserting = false;

    pthread_exit(0);
}

void* search(void* arg){
    while(inserting){ }
    
    searching = false;
    pthread_exit(0);
}

int main(int argc, char** argv){

    pthread_t thread1, thread2;

    vector<int> *list = new vector<int>();
    list->push_back(1);

    pthread_create(&thread1, NULL, insert, &list);
    pthread_create(&thread2, NULL, search, &list);

    // waiting on threads
    while(inserting || searching){ }
    
    cout << "FINISHED" << endl;
}
