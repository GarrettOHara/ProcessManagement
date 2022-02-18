#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

bool threading = false;

void* print_hello(void* arg){
    long long *arg_ptr = (long long*) arg;
    long long ptr = *arg_ptr;
    long long val = 0;

    for(long long i = 0; i < ptr; ++i){
        val+=i;
        cout << "Sum is now: " << val << endl;
    }

    threading = true;

    // return value in second parameter of join
    pthread_exit(0);
}

int main(int argc, char** argv){

    long long val = atoll(argv[1]);

    // create thread id
    pthread_t thread_id;

    // create attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&thread_id, NULL, print_hello, &val);

    while(threading){
        // wait for thread to execute
    }
    pthread_join(thread_id, NULL);
}