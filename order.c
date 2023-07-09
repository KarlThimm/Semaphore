#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s1, s2, s3;

/*The code defines a function worker which takes a pointer to an integer a as an argument.
The integer is extracted from the pointer and stored in w.
The function then performs different operations based on the value of w.
If w is equal to 2, it prints "I am worker 2" and posts to the semaphore s2.
If w is not equal to 3, it waits on the s2 semaphore, prints "I am worker w",
posts to the s2 semaphore, and then either posts to the s1 or s3 semaphore 
based on whether w is equal to 1 or not.
If w is equal to 3, it waits on both the s1 and s3 semaphores,
prints "I am worker 3".*/

void* worker(void *a)
{
    //Order function
    int w = *(int*)a;
    if(w == 2)
    {
        printf("I am worker %d\n", w);
        sem_post(&s2);
    }
    else if(w != 3)
    {
        sem_wait(&s2);
        printf("I am worker %d\n", w);
        sem_post(&s2);
        if(w==1)
            sem_post(&s1);
        else
            sem_post(&s3);
    }
    else
    {
        sem_wait(&s1);
        sem_wait(&s3);
        printf("I am worker %d\n", w);
    }
}

int main()
{
    //semaphores
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);
    sem_init(&s3, 0, 0);

    //create workers thread
    int worker1 = 1, worker2 = 2, worker3 = 3, worker4 = 4;
    pthread_t p1, p2, p3, p4;
    pthread_create(&p1, NULL, worker, (void*)&worker1);
    pthread_create(&p2, NULL, worker, (void*)&worker2);
    pthread_create(&p3, NULL, worker, (void*)&worker3);
    pthread_create(&p4, NULL, worker, (void*)&worker4);

    //Join
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);

    return 0;
}

//When running, the order is always either 2, 1, 4, 3
//or order 2, 4, 1, 3
//No leaks after valgrind (Don't know if there can be any)