#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <string>

void *print_message_function( void *ptr );

main() {
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                       void *(*start_routine) (void *), void *arg);

}
void * threadFunc(void * arg)
{
    std::cout << "Thread Function :: Start" << std::endl;
    std::cout << "Thread Function :: End" << std::endl;
    return NULL;
}