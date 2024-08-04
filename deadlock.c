#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

typedef struct s_cowboy{
    char *name;
    pthread_t thread;
}t_cowboy;

pthread_mutex_t ugly_gun = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t bad_gun = PTHREAD_MUTEX_INITIALIZER;

void *action(void *data)
{
    t_cowboy cowboy;
    cowboy = *(t_cowboy *)data;
    if (!strcmp(cowboy.name,"ugly"))
        pthread_mutex_lock(&ugly_gun);
    else
        pthread_mutex_lock(&bad_gun);

    printf("%s has taken the gun\n",cowboy.name);
    //Deadlock
    //i wanna take the other gun
    if (!strcmp(cowboy.name,"ugly"))
        pthread_mutex_lock(&bad_gun);
    else
        pthread_mutex_lock(&ugly_gun);

    return NULL;
}

int main()
{
    // t_cowboy ugly;
    // t_cowboy bad;
    // ugly.name = "ugly";
    // bad.name = "bad";
    // pthread_create(&ugly.thread,NULL,action,&ugly);
    // pthread_create(&bad.thread,NULL,action,&bad);


    // pthread_join(ugly.thread,NULL);
    // pthread_join(bad.thread,NULL);
    printf("%d",gettimeofday());
    return 0;
}
