#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include<stdint.h>
#define TH 1000
uint64_t edge ;

// void *make_coffee(void *name)
// {
//     // static int i=1;
//     printf("process  is making coffe !!!\n");
//     sleep(3);
//     printf("coffe  is ready\n");
//     // i++;
//     return NULL;
// }
void *update_ledger(void *name)
{
    edge = edge +1;
    return NULL;
}
int main()
{
   pthread_t waiter[TH];
   int i = 0;
   while (i < TH)
   {
        
        if (pthread_create(waiter + i, NULL , update_ledger, NULL))
            exit(1);
        i++;
   }
   i = 0;
   while (i < TH)
   {
        
        pthread_join(waiter[i], NULL);
        i++;
   }
   printf("\t%llu\n", i);
}
