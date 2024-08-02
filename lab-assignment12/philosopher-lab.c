//Xiangying Sun
//sun.xiangyi@northeastern.edu
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t chopstick[5];//lock variable

// Thread to be executed
void *philosopher(void *x)
{
    //Treat variable x as a pointer to an int and then extract the value into n
    int* a=(int*)x;
    int n=*a;
    
    int left = n;
    int right = (n+1) % 5;
    n = n+1;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", n);
        sleep(1); // simulate thinking

        // Take right chopstick
        pthread_mutex_lock(&chopstick[right]);

        // Check if left chopstick is available
        if (pthread_mutex_trylock(&chopstick[left]) == 0) {
            // If left chopstick is available, take it and eat
            printf("Philosopher %d is eating using chopstick[%d] and chopstick[%d].\n", n, left, right);
            sleep(1); // simulate eating

            // Put down both chopsticks after eating
            pthread_mutex_unlock(&chopstick[right]);
            pthread_mutex_unlock(&chopstick[left]);
            printf("Philosopher %d finished eating. \n", n);
            return NULL; //return when finish eating to make sure each people only eat once
        } else {
            // If left chopstick is not available, put down the right chopstick and think
            pthread_mutex_unlock(&chopstick[right]);
            sleep(1); // simulate sleeping
        }
    }
}


/*------------ Main Program---------*/
int main()
{
    int i,val[5];
    pthread_t threads[5];
    //initializing the mutex (for chopsticks)
    for(i=0;i<5;i++){
        pthread_mutex_init(&chopstick[i],NULL);
    }   

    //create and run the thread
    for(i=0;i<5;i++){
        val[i]=i;
        pthread_create(&threads[i],NULL,(void *)philosopher,&val[i]);
    }
    
    //wait until all the threads are done
    for(i=0;i<5;i++){
        pthread_join(threads[i],NULL);
    }
    
    // Destroying the mutex
    for(i=0;i<5;i++){
        pthread_mutex_destroy(&chopstick[i]);
    }
    
    return 0;
}