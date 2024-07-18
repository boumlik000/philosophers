#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>




void* print(void* arg) {
    // long sum = 0;
    // long *add_one = (long *) arg; 
    // long i = 0;
    // while (i < 10000000)
    // {
    //     sum = sum + *add_one;
    //     i++;
    // }

    printf("Hello from thread %ld\n", *((long *) arg));
    while (1)
    {
    }
    
    return NULL;
}

int main() {
    pthread_t a, b;
    long val1 = 1;
    long val2 = 2;
    // print((void *) &val1);
    // print((void *) &val2);
    printf("Hello from main thread\n");
    pthread_create(&a, NULL, print, (void *) &val1);
    pthread_create(&b, NULL, print, (void *) &val2);
    pthread_join(a, NULL);
    pthread_join(b, NULL);

    return 0;
}
