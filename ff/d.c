#include<sys/time.h>
#include<stdio.h>
typedef struct s_timeval {
    time_t      tv_sec;   // seconds
    suseconds_t tv_usec;  // microseconds
}t_timeval ;

int main()
{
    t_timeval tv;
    gettimeofday(&tv,NULL);
    long i = tv.tv_sec;
    printf("Seconds since Epoch: %ld\n", i);
    // gettimeofday(&tv,NULL);
    long j = tv.tv_usec;
    printf("Seconds since Epoch: %ld\n", j);
    sleep(3);
    gettimeofday(&tv,NULL);
     j = tv.tv_usec;
    printf("Seconds since Epoch: %ld\n", j);

    // printf("Microseconds: %ld\n", tv.tv_usec);
    return 0;
}
